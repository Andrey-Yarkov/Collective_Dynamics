#pragma once

#include <vector>
#include "Eigen/Eigen"

#include "ParticleAnsemble.h"
#include "SolidBody.h"


class Domain
{
public:
	Domain(int nDimentions, std::vector<double> sizes);

	int getDimentionsNumber();
	std::vector<double>& getSizes();
	std::vector<double>& getBoundaries(int dimention);
	//ParticleAnsemble* getParticleAnsemble();
	std::vector<SolidBody*>& getSolidBodies();
	int getSolidBodiesNumber();
	//Medium* getMedium();

	int checkOutOfBounds(Eigen::Vector3d position);
	//void createParticle(double particleSize, double particleMass, Eigen::Vector3d position, Eigen::Vector3d velocity);
	void createSolidBody(std::vector<Eigen::Vector3d> vertisies, int type);

private:
	int _nDimentions;
	std::vector<double> _sizes;
	std::vector<double> _center;
	std::vector<std::vector<double>> _boundaries;
	//ParticleAnsemble* _particleAnsemble;
	std::vector<SolidBody*> _solidBodies;
	int _solidBodiesNumber;
	//Medium* _medium;
};