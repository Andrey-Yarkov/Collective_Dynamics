#pragma once
#include <iostream>
#include <cmath>
#include <ctime>
#include "Eigen/Eigen"
#include "matplot/matplot.h"
#include "SDL.h"
#undef main

#include "PhysNamespase.h"

#include "DynamicSystem.h"
#include "Domain.h"
#include "Medium.h"
#include "ParticleAnsemble.h"
#include "SolidBody.h"
#include "DynamicSystem.h"
#include "DataManager.h"

#define WINDOW_W 1500
#define WINDOW_H 750

using namespace phys;

class SystemManager
{
public:
	SystemManager();

	int getRunningSystemsCount();

	void createSystem1();
	void createSystem2();
	void updateSystem(double& timeCounter, double& time, bool& run, int systemNo = 0);

private:
	std::vector<DynamicSystem*> _systems;
	std::vector<DataManager*> _dataManagers;

	int runningSystemsCount;
};