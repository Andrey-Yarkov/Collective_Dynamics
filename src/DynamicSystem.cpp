#include "DynamicSystem.h"


DynamicSystem::DynamicSystem(Domain* domain, ParticleAnsemble* particleAnsemble, Medium* medium) :
	_domain(domain), _particleAnsemble(particleAnsemble), _medium(medium)
{
	_timeInterval = 0.0;
	_activeForces.resize(_particleAnsemble->getParticlesNumber());
	
	for (int i = 0; i < _particleAnsemble->getParticlesNumber(); i++)
	{
		_activeForces.at(i) = Eigen::Vector3d(0.0, 0.0, 0.0);
	}
}



Domain* DynamicSystem::getDomain()
{
	return _domain;
}



ParticleAnsemble* DynamicSystem::getParticleAnsemble()
{
	return _particleAnsemble;
}



void DynamicSystem::setTimeInterval(double timeInterval)
{
	_timeInterval = timeInterval;
}

double DynamicSystem::getTimeInterval()
{
	return _timeInterval;
}



void DynamicSystem::moveParticles()
{
	int crossedBoundaryNo = -1;
	bool collision = false;

	for (auto& iParticle : _particleAnsemble->getParticles())
	{
		crossedBoundaryNo = _domain->checkOutOfBounds(iParticle->getPosition());

		if (crossedBoundaryNo == 0 || crossedBoundaryNo == 2)
			iParticle->changeDirection(0);
		else if (crossedBoundaryNo == 1 || crossedBoundaryNo == 3)
			iParticle->changeDirection(1);

		collision = false;

		if (_domain->getSolidBodiesNumber() > 0)
		{
			for (auto& iSolidBody : _domain->getSolidBodies())
			{
				iSolidBody->checkParticleCollision(iParticle, collision);

				if (collision)
					break;
			}
		}
	}

	for (auto& iParticle : _particleAnsemble->getParticles())
	{
		iParticle->updatePosition(_timeInterval);
	}
	calculateForces();

	for (auto& iParticle : _particleAnsemble->getParticles())
	{
		iParticle->updateVelocity(_timeInterval, _activeForces.at(iParticle->getParticleNo()));
	}
}



void DynamicSystem::calculateForces()
{
	Eigen::Vector3d activeForce;
	Eigen::Vector3d r;
	double distance;
	double sigm;
	double amplitude = 1.0;

	for (auto& iParticle : _particleAnsemble->getParticles())
	{
		activeForce = Eigen::Vector3d(0.0, 0.0, 0.0);
		
		for (auto& jParticle : _particleAnsemble->getParticles())
		{
			if (iParticle->getParticleNo() != jParticle->getParticleNo())
			{
				r = iParticle->getPosition() - jParticle->getPosition();
				distance = r.norm();
				sigm = iParticle->getSize() / 2.0 + jParticle->getSize() / 2.0;

				activeForce += amplitude * ((12.0 / pow(distance / sigm, 14) - 6.0 / pow(distance / sigm, 8)) * r);
			}
		}

		activeForce += -_medium->getViscousForce(iParticle->getVelocity());

		_activeForces.at(iParticle->getParticleNo()) = activeForce;
	}
}



void DynamicSystem::moveBodies()
{
	for (auto& iSolidBody : _domain->getSolidBodies())
	{
		iSolidBody->move(_timeInterval);
	}
}