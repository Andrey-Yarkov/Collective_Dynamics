#pragma once

#include <string>

#include <Eigen/Eigen>

class Medium
{
public:
	Medium(std::string name);

	Eigen::Vector3d getViscousForce(Eigen::Vector3d velocity);

private:
	std::string _name;
	double _viscosityCoef;
};