#pragma once
#include <iostream>

#include "Primitive.h"
#include "MathNamespace.h"


class Collider
{
public:
	Collider(std::vector<Eigen::Vector3d> vertisies);

	LinePrimitive* getFace(int faceNo);
	std::vector<LinePrimitive*>& getFaces();
	std::vector<Eigen::Vector3d>& getVertisies();
	int getVertisiesNumber();
	Eigen::Vector3d getCenter();

	bool nearby(Eigen::Vector3d centerPosition, double objectSize);
	Eigen::Vector3d getNearestPoint(Eigen::Vector3d position, int* faceNo, int* vertexNo);

	void move(Eigen::Vector3d translation);
	void rotate(double angle, Eigen::Vector3d center);

	virtual void collisionCheck(Eigen::Vector3d centerPosition, double objectSize, int* collidedFaceNo, int* collidedVertexNo) = 0;
	virtual Eigen::Vector3d velocityAfterBounce(Eigen::Vector3d velocity, int faceNo, int vertexNo) = 0;

protected:
	std::vector<Eigen::Vector3d> _vertisies;
	int _versitiesNumber;
	std::vector<LinePrimitive*> _faces;
	int _facesNumber;
	double _maximalSize;
	Eigen::Vector3d _center;
};


class LinearCollider : public Collider
{
public:
	LinearCollider(std::vector<Eigen::Vector3d> vertisies);

	void collisionCheck(Eigen::Vector3d centerPosition, double objectSize, int* collidedFaceNo, int* collidedVertexNo);
	Eigen::Vector3d velocityAfterBounce(Eigen::Vector3d velocity, int faceNo, int vertexNo);
};