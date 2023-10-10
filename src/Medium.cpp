#include "Medium.h"

Medium::Medium(std::string name) :
	_name(name)
{
	_viscosityCoef = 0.0;

	if (name == "water" || name == "H2O")
	{
		_viscosityCoef = 0.01;
	}
}


Eigen::Vector3d Medium::getViscousForce(Eigen::Vector3d velocity)
{
	return velocity * _viscosityCoef;
}