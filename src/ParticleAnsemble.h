#pragma once

#include <vector>
#include "Eigen/Eigen"

#include "Particle.h"


class ParticleAnsemble
{
public:
	ParticleAnsemble();

	std::vector<Particle*>& getParticles();
	Particle* getParticle(int particleNo);
	int getParticlesNumber();

	void addParticle(double particleSize, double particleMass, Eigen::Vector3d position, Eigen::Vector3d velocity);
	void updatePositions(double timeInterval);

private:
	std::vector<Particle*> _particles;
	int _nParticles;
};