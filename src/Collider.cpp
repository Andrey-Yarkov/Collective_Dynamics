#include "Collider.h"


Collider::Collider(std::vector<Eigen::Vector3d> vertisies) :
	_vertisies(vertisies)
{
	_versitiesNumber = _vertisies.size();
	_maximalSize = 0.0;
	_facesNumber = 0;

	_center = Eigen::Vector3d(0.0, 0.0, 0.0);
	for (auto& iVersitle : vertisies)
	{
		_center += iVersitle;
	}
	_center /= _versitiesNumber;
}



LinePrimitive* Collider::getFace(int faceNo)
{
	return _faces.at(faceNo);
}



std::vector<LinePrimitive*>& Collider::getFaces()
{
	return _faces;
}



std::vector<Eigen::Vector3d>& Collider::getVertisies()
{
	return _vertisies;
}



int Collider::getVertisiesNumber()
{
	return _versitiesNumber;
}



Eigen::Vector3d Collider::getCenter()
{
	return _center;
}



bool Collider::nearby(Eigen::Vector3d centerPosition, double objectSize)
{
	return true;
}



Eigen::Vector3d Collider::getNearestPoint(Eigen::Vector3d position, int* faceNo, int* vertexNo)
{
	Eigen::Vector3d nearestPoint;
	Eigen::Vector3d facialNearestPoint;
	int counter;
	int nearestVertex;

	nearestPoint = _faces.at(0)->getNearestPoint(position, vertexNo);
	*faceNo = 0;

	counter = 0;
	for (auto& iFace : _faces)
	{
		facialNearestPoint = iFace->getNearestPoint(position, &nearestVertex);
		if ((facialNearestPoint - position).norm() < (nearestPoint - position).norm())
		{
			nearestPoint = facialNearestPoint;
			*faceNo = counter;
			*vertexNo = nearestVertex;
		}
		counter++;
	}

	return nearestPoint;
}



void Collider::move(Eigen::Vector3d translation)
{
	for (auto& iFace : _faces)
	{
		iFace->shift(translation);
	}
}



void Collider::rotate(double angle, Eigen::Vector3d center)
{
	for (auto& iFace : _faces)
	{
		iFace->turn(angle, center);
	}
}





LinearCollider::LinearCollider(std::vector<Eigen::Vector3d> vertisies) :
	Collider(vertisies)
{
	for (int i = 0; i < vertisies.size() - 1; i++)
	{
		_faces.push_back(new LinePrimitive(_vertisies.at(i), _vertisies.at(i + 1)));
	}
	_faces.push_back(new LinePrimitive(_vertisies.back(), _vertisies.front()));

	_facesNumber = _faces.size();
}


/*
int LinearCollider::collisionCheck(Eigen::Vector3d centerPosition, double objectSize)
{
	int faceNo  = -1;
	int behindCounter = 0;

	Eigen::Vector3d position;

	for (auto& iFace : _faces)
	{
		position = centerPosition - iFace->getNormal() * objectSize / 2.0;

		if (iFace->behind(position) == true)
		{
			behindCounter++;
		}
	}

	//std::cout << behindCounter << std::endl;


	bool inside = behindCounter == _faces.size();

	if (inside)
	{
		double distance;
		double minDistance = objectSize * 1e6;
		int counter = 0;

		for (auto& iFace : _faces)
		{
			position = centerPosition - iFace->getNormal() * objectSize / 2.0;

			distance = Math::getDistanceToLine(iFace->getVertex(0), iFace->getVertex(1), position);

			if (distance < minDistance)
			{
				minDistance = distance;
				faceNo = counter;
			}

			counter++;
		}
	}

	return faceNo;
}
*/

void LinearCollider::collisionCheck(Eigen::Vector3d centerPosition, double objectSize, int* collidedFaceNo, int* collidedVertexNo)
{
	Eigen::Vector3d position;
	Eigen::Vector3d normal;

	*collidedFaceNo = -1;
	*collidedVertexNo = -1;
	Eigen::Vector3d nearestPoint = getNearestPoint(centerPosition, collidedFaceNo, collidedVertexNo);

	if (*collidedVertexNo == -1)
	{
		normal = _faces.at(*collidedFaceNo)->getNormal();
	}
	else if (*collidedVertexNo == 0)
	{
		normal = _faces.at(*collidedFaceNo)->getNormal() / 2.0;

		if (*collidedFaceNo - 1 < 0)
			normal += _faces.back()->getNormal() / 2.0;
		else
			normal += _faces.at(*collidedFaceNo - 1)->getNormal() / 2.0;

		normal /= normal.norm();
	}
	else if (*collidedVertexNo == 1)
	{
		normal = _faces.at(*collidedFaceNo)->getNormal() / 2.0;

		if (*collidedFaceNo + 1 > _facesNumber - 1)
			normal += _faces.front()->getNormal() / 2.0;
		else
			normal += _faces.at(*collidedFaceNo + 1)->getNormal() / 2.0;

		normal /= normal.norm();
	}

	position = centerPosition - normal * objectSize / 2.0;

	bool outside = (position - nearestPoint).dot(normal) > 0.0;

	if (outside)
	{
		*collidedFaceNo = -1;
	}
	else
	{
		//std::cout << *collidedFaceNo << " " << *collidedVertexNo << std::endl;
	}

	//std::cout << outside << "\n" << std::endl;
}



Eigen::Vector3d LinearCollider::velocityAfterBounce(Eigen::Vector3d velocity, int faceNo, int vertexNo)
{
	Eigen::Vector3d normal;
	Eigen::Vector3d resultedVelocity;
	double normalVelocityValue;

	if (vertexNo == -1)
	{
		normal = _faces.at(faceNo)->getNormal();
	}
	else if (vertexNo == 0)
	{
		normal = _faces.at(faceNo)->getNormal() / 2.0;

		if (faceNo - 1 < 0)
			normal += _faces.back()->getNormal() / 2.0;
		else
			normal += _faces.at(faceNo - 1)->getNormal() / 2.0;

		normal /= normal.norm();
	}
	else if (vertexNo == 1)
	{
		normal = _faces.at(faceNo)->getNormal() / 2.0;

		if (faceNo + 1 > _facesNumber - 1)
			normal += _faces.front()->getNormal() / 2.0;
		else
			normal += _faces.at(faceNo + 1)->getNormal() / 2.0;

		normal /= normal.norm();
	}

	normalVelocityValue = velocity.dot(normal);

	if (normalVelocityValue > 0.0)
	{
		resultedVelocity = velocity;
	}
	else
	{
		resultedVelocity = velocity - 2.0 * normalVelocityValue * normal;
	}

	//std::cout << resultedVelocity << "\n" << std::endl;
	//std::cout << faceNo << vertexNo << "\n" << std::endl;


	return resultedVelocity;
}