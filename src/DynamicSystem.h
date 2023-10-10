#pragma once

#include <iostream>

#include "Domain.h"
#include "ParticleAnsemble.h"
#include "Medium.h"


class DynamicSystem
{
public:
	DynamicSystem(Domain* domain, ParticleAnsemble* particleAnsemble, Medium* medium);

	Domain* getDomain();
	ParticleAnsemble* getParticleAnsemble();
	void setTimeInterval(double timeInterval);
	double getTimeInterval();

	void moveParticles();
	void calculateForces();
	void moveBodies();

private:
	Domain* _domain;
	ParticleAnsemble* _particleAnsemble;
	Medium* _medium;
	double _timeInterval;
	std::vector<Eigen::Vector3d> _activeForces;
};