#include "MathNamespace.h"


namespace Math
{
	double getAreaOfTriangleHeron(double a, double b, double c)
	{
		double p = (a + b + c) / 2.0;

		return pow(p * (p - a) * (p - b) * (p - c), 0.5);
	}



	double getDistanceToLine(Eigen::Vector3d v1, Eigen::Vector3d v2, Eigen::Vector3d r)
	{
		double a = (v1 - r).norm();
		double b = (v2 - r).norm();
		double c = (v1 - v2).norm();

		return 2.0 * getAreaOfTriangleHeron(a, b, c) / c;
	}
}