#pragma once

#include "Visualizer.h"

class DataManager
{
public:
	DataManager(Visualizer* visualizer, double visualizerTimeConstant);

	void manageData(bool& run, double& timeCounter);
	void deleteStream();

private:
	Visualizer* _visualizer;
	double _visualizerTimeConstant;
};