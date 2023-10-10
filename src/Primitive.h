#pragma once

#include "Eigen/Eigen"
#include <iostream>

#include "MathNamespace.h"


class LinePrimitive
{
public:
	LinePrimitive(Eigen::Vector3d vertexFirst, Eigen::Vector3d vertexSecond);

	Eigen::Vector3d getVertex(int vertexNo);
	Eigen::Vector3d getTangent();
	Eigen::Vector3d getNormal();
	double getLength();

	double getDistance(Eigen::Vector3d position);
	Eigen::Vector3d getNearestPoint(Eigen::Vector3d position, int* nearestVertexIdx);
	bool behind(Eigen::Vector3d position);

	void shift(Eigen::Vector3d translation);
	void turn(double angle, Eigen::Vector3d center);

protected:
	bool _leftOriented;
	Eigen::Vector3d _vertexFirst;
	Eigen::Vector3d _vertexSecond;
	Eigen::Vector3d _tangent;
	Eigen::Vector3d _normal;
	double _length;
};