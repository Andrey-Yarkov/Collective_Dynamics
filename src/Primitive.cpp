#include "Primitive.h"


LinePrimitive::LinePrimitive(Eigen::Vector3d vertexFirst, Eigen::Vector3d vertexSecond) :
	_vertexFirst(vertexFirst), _vertexSecond(vertexSecond)
{
	_leftOriented = true;

	_tangent = _vertexSecond - _vertexFirst;
	_tangent /= _tangent.norm();

	if (_leftOriented)
		_normal = Eigen::Vector3d(0.0, 0.0, 1.0).cross(_tangent);
	else
		_normal = - Eigen::Vector3d(0.0, 0.0, 1.0).cross(_tangent);

	_length = (_vertexSecond - _vertexFirst).norm();
}



Eigen::Vector3d LinePrimitive::getVertex(int vertexNo)
{
	if (vertexNo == 0)
		return _vertexFirst;
	else
		return _vertexSecond;
}



Eigen::Vector3d LinePrimitive::getTangent()
{
	return _tangent;
}



Eigen::Vector3d LinePrimitive::getNormal()
{
	return _normal;
}



double LinePrimitive::getLength()
{
	return _length;
}





double LinePrimitive::getDistance(Eigen::Vector3d position)
{
	Eigen::Vector3d a = position - _vertexFirst;

	return abs(a.dot(_normal));
}



Eigen::Vector3d LinePrimitive::getNearestPoint(Eigen::Vector3d position, int* nearestVertexIdx)
{
	Eigen::Vector3d a = position - _vertexFirst;
	Eigen::Vector3d b = position - _vertexSecond;

	*nearestVertexIdx = -1;
	
	double h = abs(a.dot(_normal));

	Eigen::Vector3d shorter, longer;

	if (a.norm() > b.norm())
	{
		shorter = b;
		longer = a;
		*nearestVertexIdx = 1;
	}
	else
	{
		shorter = a;
		longer = b;
		*nearestVertexIdx = 0;
	}

	bool outsideLine = (Math::getAreaOfTriangleHeron(a.norm(), b.norm(), _length) <= 0.5 * h * (sqrt(longer.norm() * longer.norm() - h * h)));

	if (outsideLine)
	{
		return position - shorter;
	}
	else
	{
		*nearestVertexIdx = -1;
		return position - h * _normal;
	}
}



bool LinePrimitive::behind(Eigen::Vector3d position)
{
	/*
	if (position.dot(_normal) >= 0.0)
	{
		if (position.norm() < (_vertexFirst + _vertexSecond).norm() / 2.0)
			behind = true;
		else
			behind = false;
	}
	else
	{
		if (position.norm() > (_vertexFirst + _vertexSecond).norm() / 2.0)
			behind = true;
		else
			behind = false;
	}
	*/

	Eigen::Vector3d a = position - _vertexFirst;
	Eigen::Vector3d b = position - _vertexSecond;

	if ((a + b).dot(_normal) < 0.0)
		return true;
	else
		return false;
}



void LinePrimitive::shift(Eigen::Vector3d translation)
{
	_vertexFirst += translation;
	_vertexSecond += translation;
}



void LinePrimitive::turn(double angle, Eigen::Vector3d center)
{
	Eigen::Vector3d radialFirst = _vertexFirst - center;
	Eigen::Vector3d radialSecond = _vertexSecond - center;
}