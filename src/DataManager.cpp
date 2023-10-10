#include "DataManager.h"

DataManager::DataManager(Visualizer* visualizer, double visualizerTimeConstant) :
	_visualizer(visualizer), _visualizerTimeConstant(visualizerTimeConstant)
{

}


void DataManager::manageData(bool& run, double& timeCounter)
{
    if (timeCounter >= _visualizerTimeConstant)
    {
        _visualizer->updateFrame(run);
        timeCounter = 0.0;
    }
}

void DataManager::deleteStream()
{
    _visualizer->closeWindow();
}