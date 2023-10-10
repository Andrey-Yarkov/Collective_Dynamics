#include "Domain.h"


Domain::Domain(int nDimentions, std::vector<double> sizes) :
	_nDimentions(nDimentions), _sizes(sizes)
{
	_center = { 0.0, 0.0, 0.0 };

	_boundaries.resize(_nDimentions);
	for (int i = 0; i < _nDimentions; i++)
	{
		_boundaries.at(i).resize(2);
		_boundaries.at(i).at(0) = _center.at(i) - _sizes.at(i) / 2.0;
		_boundaries.at(i).at(1) = _center.at(i) + _sizes.at(i) / 2.0;
	}

	_solidBodiesNumber = 0;

	//_particleAnsemble = new ParticleAnsemble();
}



int Domain::getDimentionsNumber()
{
	return _nDimentions;
}



std::vector<double>& Domain::getSizes()
{
	return _sizes;
}



std::vector<double>& Domain::getBoundaries(int dimention)
{
	return _boundaries.at(dimention);
}


/*
ParticleAnsemble* Domain::getParticleAnsemble()
{
	return _particleAnsemble;
}
*/


std::vector<SolidBody*>& Domain::getSolidBodies()
{
	return _solidBodies;
}



int Domain::getSolidBodiesNumber()
{
	return _solidBodiesNumber;
}


/*
Medium* Domain::getMedium()
{
	return _medium;
}
*/




int Domain::checkOutOfBounds(Eigen::Vector3d position)
{
	int result;

	if (position(0) <= _boundaries.at(0).at(0))
		result = 0;
	else if (position(0) >= _boundaries.at(0).at(1))
		result = 2;
	else if (position(1) <= _boundaries.at(1).at(0))
		result = 1;
	else if (position(1) >= _boundaries.at(1).at(1))
		result = 3;
	else
		result = -1;

	return result;
}



void Domain::createSolidBody(std::vector<Eigen::Vector3d> vertisies, int type)
{
	_solidBodies.push_back(new SolidBody(vertisies, type));
	_solidBodiesNumber++;
}

/*
void Domain::createParticle(double particleSize, double particleMass, Eigen::Vector3d position, Eigen::Vector3d velocity)
{
	_particleAnsemble->addParticle(particleSize, particleMass, position, velocity);
}
*/