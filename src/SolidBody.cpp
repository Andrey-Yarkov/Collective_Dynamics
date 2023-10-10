#include "SolidBody.h"


SolidBody::SolidBody(std::vector<Eigen::Vector3d> vertisies, int type)
{
	if (type == 0)
		_collider = new LinearCollider(vertisies);

	_velocity = Eigen::Vector3d(0.0, 0.0, 0.0);
	_startingPoint = _collider->getCenter();
	_movingTime = 0.0;
	_timeLeft = 0.0;
	repetativeMotion = false;
}



Collider* SolidBody::getCollider()
{
	return _collider;
}



bool SolidBody::freezed()
{
	return _freezed;
}



void SolidBody::setVelocity(Eigen::Vector3d velocity)
{
	_velocity = velocity;
	_freezed = false;
}



void SolidBody::setTrajectory(Eigen::Vector3d destination, double movingTime, bool repeat)
{
	setVelocity((destination - _startingPoint) / movingTime);
	_movingTime = movingTime;
	_timeLeft = movingTime;
	repetativeMotion = repeat;
}



void SolidBody::move(double timeInterval)
{
	_collider->move(_velocity * timeInterval);
	_timeLeft -= timeInterval;
	if (_timeLeft <= 0.0)
	{
		if (repetativeMotion)
		{
			setVelocity(-1.0 * _velocity);
			_timeLeft = _movingTime;
		}
		else
		{
			freeze();
		}
	}
}



void SolidBody::rotate(double angle, Eigen::Vector3d center)
{
	_collider->rotate(angle, center);
}



void SolidBody::freeze()
{
	_velocity = Eigen::Vector3d(0.0, 0.0, 0.0);
	_freezed = true;
}



void SolidBody::checkParticleCollision(Particle* particle, bool& collision)
{
	int collidedFaceNo = -1;
	int collidedVertexNo = -1;

	_collider->collisionCheck(particle->getPosition(), particle->getSize(), &collidedFaceNo, &collidedVertexNo);

	if (collidedFaceNo != -1)
	{
		particle->setVelocity(_collider->velocityAfterBounce(particle->getVelocity() - _velocity, collidedFaceNo, collidedVertexNo));
	}
}