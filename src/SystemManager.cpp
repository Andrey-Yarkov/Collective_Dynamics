#include "SystemManager.h"

SystemManager::SystemManager()
{
    runningSystemsCount = 0;
}



int SystemManager::getRunningSystemsCount()
{
    return runningSystemsCount;
}



void SystemManager::createSystem1()
{
    std::srand(std::time(nullptr));

    double lU = m();
    double tU = s();

    double domainWidth = 100.0 * lU;
    double domainHeight = 50.0 * lU;

    double scale = WINDOW_W / domainWidth;

    Domain* domain = new Domain(2, { domainWidth, domainHeight });
    domain->createSolidBody({ Eigen::Vector3d(0.0, -5.0 * lU, 0.0), Eigen::Vector3d(0.0, 5.0 * lU, 0.0), Eigen::Vector3d(1.0 * lU, 5.0 * lU, 0.0), Eigen::Vector3d(1.0 * lU, -5.0 * lU, 0.0) }, 0);
    domain->getSolidBodies().back()->setTrajectory(Eigen::Vector3d(-25.0 * lU, 0.0 * lU, 0.0), 25.0, true);

    /*
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            domain->createSolidBody({ Eigen::Vector3d(-domainWidth / 2.0 + i * 10.0, -domainHeight / 2.0 + j * 10.0, 0.0),
                                      Eigen::Vector3d(-domainWidth / 2.0 + i * 10.0, -domainHeight / 2.0 + j * 10.0 + 2.5, 0.0),
                                      Eigen::Vector3d(-domainWidth / 2.0 + i * 10.0 + 2.5, -domainHeight / 2.0 + j * 10.0 + 2.5, 0.0),
                                      Eigen::Vector3d(-domainWidth / 2.0 + i * 10.0 + 2.5, -domainHeight / 2.0 + j * 10.0, 0.0) }, 0);
        }
    }
    */



    ParticleAnsemble* particleAnsemble = new ParticleAnsemble();

    double particleSize = 1.0 * lU;
    //double density = 2.0 * g() / pow(cm(), 3);
    double density = 1.0;
    double particleMass = density * M_PI * pow(particleSize, 3) / 6.0;

    double randVelX = 0.0;
    double randVelY = 0.0;

    //randVelX = (-40.0 + 80.0 * std::rand() / RAND_MAX) * lU / tU;
    //randVelY = (-40.0 + 80.0 * std::rand() / RAND_MAX) * lU / tU;
    randVelX = 0.1 * lU / tU;
    randVelY = 0;

    particleAnsemble->addParticle(particleSize, particleMass, Eigen::Vector3d(-2.5 * lU, 0.0, 0.0), Eigen::Vector3d(1.1, 0.0, 0.0));
    //particleAnsemble->addParticle(particleSize, particleMass, Eigen::Vector3d(0, 5, 0.0), Eigen::Vector3d(0.0, 0.0, 0.0));
    /*
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            randVelX = -10.0 + 20.0 * std::rand() / RAND_MAX;
            randVelY = -10.0 + 20.0 * std::rand() / RAND_MAX;

            particleAnsemble->addParticle(particleSize, particleMass, Eigen::Vector3d(-domainWidth / 2.0 + 7.5 + i * 10.0, -domainHeight / 2.0 + 7.5 + j * 10.0, 0.0),
                Eigen::Vector3d(randVelX, randVelY, 0.0));
        }
    }
    */

    /*
    for (int i = 0; i < 9; i++)
    {
        randVelX = -5.0 + 10.0 * std::rand() / RAND_MAX;
        randVelY = -5.0 + 10.0 * std::rand() / RAND_MAX;
        //randVelX = 0;
        //randVelY = 0;

        particleAnsemble->addParticle(particleSize, particleMass, Eigen::Vector3d(10.0, i * 2.0 - 16.0, 0.0), Eigen::Vector3d(randVelX, randVelY, 0.0));
    }
    */

    Medium* medium = new Medium("water");


    DynamicSystem* dynamicSystem = new DynamicSystem(domain, particleAnsemble, medium);
    dynamicSystem->setTimeInterval(1e-4 * tU);


    Visualizer* visualizer = new SdlVisualizer(dynamicSystem);
    visualizer->createWindow(1, 50, 50, WINDOW_W, WINDOW_H);
    bool run = true;
    visualizer->updateFrame(run);

    DataManager* dataManager = new DataManager(visualizer, 0.1);

    _systems.push_back(dynamicSystem);
    _dataManagers.push_back(dataManager);

    runningSystemsCount++;
}



void SystemManager::createSystem2()
{
    std::srand(std::time(nullptr));

    double lU = m();
    double tU = s();

    double domainWidth = 100.0 * lU;
    double domainHeight = 50.0 * lU;

    double scale = WINDOW_W / domainWidth;

    Domain* domain = new Domain(2, { domainWidth, domainHeight });
    domain->createSolidBody({ Eigen::Vector3d(-40.0 * lU, -20.0 * lU, 0.0), Eigen::Vector3d(-40.0 * lU, -15.0 * lU, 0.0), Eigen::Vector3d(-35.0 * lU, -15.0 * lU, 0.0), Eigen::Vector3d(-35.0 * lU, -20.0 * lU, 0.0) }, 0);
    domain->getSolidBodies().back()->setTrajectory(Eigen::Vector3d(-35.0 * lU, -17.5 * lU, 0.0), 10.0, true);
    domain->createSolidBody({ Eigen::Vector3d(-40.0 * lU, 15.0 * lU, 0.0), Eigen::Vector3d(-40.0 * lU, 20.0 * lU, 0.0), Eigen::Vector3d(-35.0 * lU, 20.0 * lU, 0.0), Eigen::Vector3d(-35.0 * lU, 15.0 * lU, 0.0) }, 0);
    domain->getSolidBodies().back()->setTrajectory(Eigen::Vector3d(-35.0 * lU, 17.5 * lU, 0.0), 10.0, true);
    domain->createSolidBody({ Eigen::Vector3d(35.0 * lU, 15.0 * lU, 0.0), Eigen::Vector3d(35.0 * lU, 20.0 * lU, 0.0), Eigen::Vector3d(40.0 * lU, 20.0 * lU, 0.0), Eigen::Vector3d(40.0 * lU, 15.0 * lU, 0.0) }, 0);
    domain->getSolidBodies().back()->setTrajectory(Eigen::Vector3d(35.0 * lU, 17.5 * lU, 0.0), 10.0, true);
    domain->createSolidBody({ Eigen::Vector3d(35.0 * lU, -20.0 * lU, 0.0), Eigen::Vector3d(35.0 * lU, -15.0 * lU, 0.0), Eigen::Vector3d(40.0 * lU, -15.0 * lU, 0.0), Eigen::Vector3d(40.0 * lU, -20.0 * lU, 0.0) }, 0);
    domain->getSolidBodies().back()->setTrajectory(Eigen::Vector3d(35.0 * lU, -17.5 * lU, 0.0), 10.0, true);


    ParticleAnsemble* particleAnsemble = new ParticleAnsemble();

    double particleSize = 1.0 * lU;
    //double density = 2.0 * g() / pow(cm(), 3);
    double density = 1.0;
    double particleMass = density * M_PI * pow(particleSize, 3) / 6.0;

    double randVelX = 0.0;
    double randVelY = 0.0;

    //randVelX = (-40.0 + 80.0 * std::rand() / RAND_MAX) * lU / tU;
    //randVelY = (-40.0 + 80.0 * std::rand() / RAND_MAX) * lU / tU;
    randVelX = 0.1 * lU / tU;
    randVelY = 0;

    particleAnsemble->addParticle(particleSize, particleMass, Eigen::Vector3d(-37.5 * lU, 0.0, 0.0), Eigen::Vector3d(0.0, 5.0, 0.0));


    Medium* medium = new Medium("water");


    DynamicSystem* dynamicSystem = new DynamicSystem(domain, particleAnsemble, medium);
    dynamicSystem->setTimeInterval(1e-4 * tU);


    Visualizer* visualizer = new SdlVisualizer(dynamicSystem);
    visualizer->createWindow(1, 50, 50, WINDOW_W, WINDOW_H);
    bool run = true;
    visualizer->updateFrame(run);

    DataManager* dataManager = new DataManager(visualizer, 0.1);

    _systems.push_back(dynamicSystem);
    _dataManagers.push_back(dataManager);

    runningSystemsCount++;
}



void SystemManager::updateSystem(double& timeCounter, double& time, bool& run, int systemNo)
{
    timeCounter += _systems.at(systemNo)->getTimeInterval();
    time += _systems.at(systemNo)->getTimeInterval();

    _systems.at(systemNo)->moveParticles();
    _systems.at(systemNo)->moveBodies();
    _dataManagers.at(systemNo)->manageData(run, timeCounter);

    if (!run)
    {
        _dataManagers.at(systemNo)->deleteStream();

        runningSystemsCount--;
    }
}