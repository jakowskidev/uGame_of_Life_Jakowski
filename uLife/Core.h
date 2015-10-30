#pragma once

#ifndef CCORE_H
#define CCORE_H

#include <SDL.h>
#include "Map.h"

class CCore
{
private:
	SDL_Window* window;
	SDL_Renderer* rR;
	SDL_Event* mainEvent;

	// ----- FPS -----
	long frameTime;
	static const int MIN_FRAME_TIME = 16;

	SDL_Rect currentRect;
	Map* oMap;

	long nextUpdate;

	bool mouseLeftPressed, mouseRightPressed;

	int mouseX, mouseY;
public:
	CCore(void);
	~CCore(void);

	static bool quitGame;

	void mainLoop();

	void Update();
	void Draw();

	void mouseInput();
};

#endif