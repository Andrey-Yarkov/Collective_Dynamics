#pragma once

#include "Eigen/Eigen"


class Particle
{
public:
	Particle(int number, double size, double mass, Eigen::Vector3d position, Eigen::Vector3d velocity);

	int getParticleNo();
	double getSize();
	Eigen::Vector3d getPosition();
	Eigen::Vector3d getVelocity();
	Eigen::Vector3d getAcceleration();

	void setVelocity(Eigen::Vector3d velocity);

	void updatePosition(double timeInterval);
	void updateVelocity(double timeInterval, Eigen::Vector3d activeForce);
	void changeDirection(int direction);

private:
	int _number;
	double _size;
	double _mass;
	Eigen::Vector3d _position;
	Eigen::Vector3d _velocity;
	Eigen::Vector3d _acceleration;
};