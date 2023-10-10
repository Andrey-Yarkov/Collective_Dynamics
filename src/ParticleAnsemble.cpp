#include "ParticleAnsemble.h"


ParticleAnsemble::ParticleAnsemble()
{
	_nParticles = 0;
}



std::vector<Particle*>& ParticleAnsemble::getParticles()
{
	return _particles;
}



Particle* ParticleAnsemble::getParticle(int particleNo)
{
	return _particles.at(particleNo);
}



int ParticleAnsemble::getParticlesNumber()
{
	return _nParticles;
}



void ParticleAnsemble::addParticle(double particleSize, double particleMass, Eigen::Vector3d position, Eigen::Vector3d velocity)
{
	_particles.push_back(new Particle(_nParticles++, particleSize, particleMass, position, velocity));
}



void ParticleAnsemble::updatePositions(double timeInterval)
{
	for (auto& iParticle : _particles)
	{
		iParticle->updatePosition(timeInterval);
	}
}