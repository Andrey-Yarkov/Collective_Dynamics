#include "Visualizer.h"


Visualizer::Visualizer(DynamicSystem* dynamicSystem) :
	_dynamicSystem(dynamicSystem)
{
    _windowWidth = 0;
    _windowHeight = 0;
    _scale = 1.0;
}



void Visualizer::pressEnter()
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = VK_RETURN;
    ip.ki.dwFlags = 0; // 0 for key press

    SendInput(1, &ip, sizeof(INPUT));
}





MatplotVisualizer::MatplotVisualizer(DynamicSystem* dynamicSystem) :
    Visualizer(dynamicSystem)
{
    _type = "matplot";
}



void MatplotVisualizer::createWindow(int windowNo, int xPosition, int yPosition, int width, int height)
{
    h = matplot::figure(windowNo);
    h->x_position(xPosition);
    h->y_position(yPosition);
    h->width(width);
    h->height(height);

    matplot::xlim({ _dynamicSystem->getDomain()->getBoundaries(0).at(0), _dynamicSystem->getDomain()->getBoundaries(0).at(1) });
    matplot::ylim({ _dynamicSystem->getDomain()->getBoundaries(1).at(0), _dynamicSystem->getDomain()->getBoundaries(1).at(1) });

    matplot::grid(true);

    _windowWidth = width;
    _windowHeight = height;

    _scale = width / _dynamicSystem->getDomain()->getSizes().at(0) / 1.25;
}



void MatplotVisualizer::updateFrame(bool& run)
{
    std::vector<double> x;
    x.resize(_dynamicSystem->getParticleAnsemble()->getParticlesNumber());

    std::vector<double> y;
    y.resize(_dynamicSystem->getParticleAnsemble()->getParticlesNumber());

    std::vector<double> sz;
    sz.resize(_dynamicSystem->getParticleAnsemble()->getParticlesNumber());

    for (int i = 0; i < _dynamicSystem->getParticleAnsemble()->getParticlesNumber(); i++)
    {
        x.at(i) = _dynamicSystem->getParticleAnsemble()->getParticle(i)->getPosition()(0);
        y.at(i) = _dynamicSystem->getParticleAnsemble()->getParticle(i)->getPosition()(1);
        sz.at(i) = _dynamicSystem->getParticleAnsemble()->getParticle(i)->getSize() * _scale;
    }

    matplot::figure(h);

    auto l = matplot::scatter(x, y, sz);
    l->marker_face(true);

    matplot::hold(true);


    for (auto& iSolidBody : _dynamicSystem->getDomain()->getSolidBodies())
    {
        std::vector<double> xSb;
        xSb.resize(iSolidBody->getCollider()->getVertisiesNumber() + 1);

        std::vector<double> ySb;
        ySb.resize(iSolidBody->getCollider()->getVertisiesNumber() + 1);

        for (int i = 0; i < iSolidBody->getCollider()->getVertisiesNumber(); i++)
        {
            xSb.at(i) = iSolidBody->getCollider()->getVertisies().at(i)(0);
            ySb.at(i) = iSolidBody->getCollider()->getVertisies().at(i)(1);
        }

        xSb.back() = iSolidBody->getCollider()->getVertisies().at(0)(0);
        ySb.back() = iSolidBody->getCollider()->getVertisies().at(0)(1);

        auto l = matplot::plot(xSb, ySb, "k");
    }

    matplot::hold(false);

    //if (pressEnterButton)
    //pressEnter();
    //matplot::show();

    h->draw();

    Sleep(50);
}



void MatplotVisualizer::closeWindow()
{

}





SdlVisualizer::SdlVisualizer(DynamicSystem* dynamicSystem) :
    Visualizer(dynamicSystem)
{
    _type = "sdl";
}



void SdlVisualizer::createWindow(int windowNo, int xPosition, int yPosition, int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO);

    _window = SDL_CreateWindow("Collective dynamics", xPosition, yPosition, width, height, SDL_WINDOW_SHOWN);
    SDL_Delay(100);

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);

    SDL_Surface* temp_surf = 0;

    for (auto& iParticle : _dynamicSystem->getParticleAnsemble()->getParticles())
    {
        temp_surf = SDL_LoadBMP("Images/red-circle.bmp");

        if (temp_surf == 0) {
            std::cout << "Can't load image: " << SDL_GetError() << std::endl;
            system("pause");
        }

        _particles.push_back(SDL_CreateTextureFromSurface(_renderer, temp_surf));
        SDL_FreeSurface(temp_surf);
    }

    _windowWidth = width;
    _windowHeight = height;

    _scale = width / _dynamicSystem->getDomain()->getSizes().at(0);
}



void SdlVisualizer::updateFrame(bool& run)
{
    //SDL_FillRect(_screen, 0, SDL_MapRGB(_screen->format, 255, 255, 255));

    /*
    SDL_Rect r;

    for (int i = 0; i < _dynamicSystem->getParticleAnsemble()->getParticlesNumber(); i++)
    {
        r.x = _dynamicSystem->getParticleAnsemble()->getParticle(i)->getPosition()(0) * _scale + _windowWidth / 2;
        r.y = -_dynamicSystem->getParticleAnsemble()->getParticle(i)->getPosition()(1) * _scale + _windowHeight / 2;

        r.w = _dynamicSystem->getParticleAnsemble()->getParticle(i)->getSize() * _scale;
        r.h = _dynamicSystem->getParticleAnsemble()->getParticle(i)->getSize() * _scale;

        SDL_BlitScaled(_particles.at(i), 0, _screen, &r);
    }
    */

    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT) {
            run = false;
        }
    }

    SDL_RenderClear(_renderer);

    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_Rect background = { 0, 0, _windowWidth, _windowHeight };
    SDL_RenderFillRect(_renderer, &background);


    SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 0);
    SDL_Rect particle;

    for (int i = 0; i < _dynamicSystem->getParticleAnsemble()->getParticlesNumber(); i++)
    {
        particle.w = _dynamicSystem->getParticleAnsemble()->getParticle(i)->getSize() * _scale;
        particle.h = _dynamicSystem->getParticleAnsemble()->getParticle(i)->getSize() * _scale;

        particle.x = _dynamicSystem->getParticleAnsemble()->getParticle(i)->getPosition()(0) * _scale + _windowWidth / 2;
        particle.y = -_dynamicSystem->getParticleAnsemble()->getParticle(i)->getPosition()(1) * _scale + _windowHeight / 2;

        particle.x -= particle.w / 2.0;
        particle.y -= particle.h / 2.0;

        SDL_RenderCopy(_renderer, _particles.at(i), 0, &particle);
    }


    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    int x1, y1, x2, y2;

    for (auto& iSolidBody : _dynamicSystem->getDomain()->getSolidBodies())
    {
        for (auto& iLine : iSolidBody->getCollider()->getFaces())
        {
            x1 = iLine->getVertex(0)(0) * _scale + _windowWidth / 2;
            y1 = -iLine->getVertex(0)(1) * _scale + _windowHeight / 2;
            x2 = iLine->getVertex(1)(0) * _scale + _windowWidth / 2;
            y2 = -iLine->getVertex(1)(1) * _scale + _windowHeight / 2;

            SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
        }
    }

    SDL_RenderPresent(_renderer);
    //SDL_UpdateWindowSurface(_window);
    SDL_Delay(16);
    //SDL_Delay(250);

    //Sleep(50);
}



void SdlVisualizer::closeWindow()
{
    for (int i = 0; i < _dynamicSystem->getParticleAnsemble()->getParticlesNumber(); i++)
    {
        SDL_DestroyTexture(_particles.at(i));
    }

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    SDL_Quit();
}