#include <iostream>
#include <cmath>
#include <ctime>

#include "SystemManager.h"


int main()
{
    SystemManager* systemManager = new SystemManager();

    systemManager->createSystem2();

    double time = 0.0;
    double timeCounter = 0.0;
    bool run = true;

    while (true)
    {
        systemManager->updateSystem(timeCounter, time, run, 0);

        if (systemManager->getRunningSystemsCount() < 1)
        {
            break;
        }
    }
}
