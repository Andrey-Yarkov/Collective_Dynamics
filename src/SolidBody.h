#pragma once

#include "Collider.h"
#include "Particle.h"


class SolidBody
{
public:
	SolidBody(std::vector<Eigen::Vector3d> vertisies, int type);

	Collider* getCollider();
	Eigen::Vector3d getVelocity();
	bool freezed();

	void setVelocity(Eigen::Vector3d velocity);

	void setTrajectory(Eigen::Vector3d destination, double movingTime, bool repeat = false);
	void move(double timeInterval);
	void rotate(double angle, Eigen::Vector3d center);
	void freeze();
	void checkParticleCollision(Particle* particle, bool& collision);

private:
	Collider* _collider;
	Eigen::Vector3d _velocity;
	Eigen::Vector3d _startingPoint;
	bool _freezed;
	double _movingTime;
	double _timeLeft;
	bool repetativeMotion;
};