#pragma once

#include <cmath>
#include "Eigen/Eigen"


namespace Math
{
	double getAreaOfTriangleHeron(double a, double b, double c);

	double getDistanceToLine(Eigen::Vector3d v1, Eigen::Vector3d v2, Eigen::Vector3d r);
}