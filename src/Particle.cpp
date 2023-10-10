#include "Particle.h"


Particle::Particle(int number, double size, double mass, Eigen::Vector3d position, Eigen::Vector3d velocity) :
	_number(number), _size(size), _mass(mass), _position(position), _velocity(velocity)
{
	_acceleration = Eigen::Vector3d(0.0, 0.0, 0.0);
}



int Particle::getParticleNo()
{
	return _number;
}



double Particle::getSize()
{
	return _size;
}



Eigen::Vector3d Particle::getPosition()
{
	return _position;
}



Eigen::Vector3d Particle::getVelocity()
{
	return _velocity;
}



Eigen::Vector3d Particle::getAcceleration()
{
	return _acceleration;
}



void Particle::setVelocity(Eigen::Vector3d velocity)
{
	_velocity = velocity;
}



void Particle::updatePosition(double timeInterval)
{
	_position += _velocity * timeInterval + _acceleration * timeInterval * timeInterval / 2.0;
}



void Particle::updateVelocity(double timeInterval, Eigen::Vector3d activeForce)
{
	_velocity += (_acceleration + activeForce / _mass) * timeInterval / 2.0;
	_acceleration = activeForce / _mass;
}



void Particle::changeDirection(int direction)
{
	_velocity(direction) *= -1.0;
}