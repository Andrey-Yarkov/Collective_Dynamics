#pragma once

#include "matplot/matplot.h"
#include "SDL.h"

#include "DynamicSystem.h"


class Visualizer
{
public:
	Visualizer(DynamicSystem* dynamicSystem);

	void pressEnter();
	virtual void createWindow(int windowNo, int xPosition, int yPosition, int width, int height) = 0;
	virtual void updateFrame(bool& run) = 0;
	virtual void closeWindow() = 0;

protected:
	DynamicSystem* _dynamicSystem;
	int _windowWidth;
	int _windowHeight;
	double _scale;
	std::string _type;
};





class MatplotVisualizer : public Visualizer
{
public:
	MatplotVisualizer(DynamicSystem* dynamicSystem);

	void createWindow(int windowNo, int xPosition, int yPosition, int width, int height);
	void updateFrame(bool& run);
	void closeWindow();

private:
	matplot::figure_handle h;
};





class SdlVisualizer : public Visualizer
{
public:
	SdlVisualizer(DynamicSystem* dynamicSystem);

	void createWindow(int windowNo, int xPosition, int yPosition, int width, int height);
	void updateFrame(bool& run);
	void closeWindow();

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	std::vector<SDL_Texture*> _particles;
};