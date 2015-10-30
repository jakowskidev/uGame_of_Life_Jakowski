#include "Core.h"
#include "CFG.h"

bool CCore::quitGame = false;

CCore::CCore(void) {
	this->quitGame = false;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
	
	window = SDL_CreateWindow("The game of life - www.LukaszJakowski.pl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CCFG::GAME_WIDTH, CCFG::GAME_HEIGHT, SDL_WINDOW_SHOWN);

	if(window == NULL) {
		quitGame = true;
	}

	rR = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	mainEvent = new SDL_Event();

	oMap = new Map();

	currentRect.h = currentRect.w = 2;

	nextUpdate = 100;
}

CCore::~CCore(void) {

}

void CCore::mainLoop() {
	while(!quitGame && mainEvent->type != SDL_QUIT) {
		frameTime = SDL_GetTicks();
		SDL_PollEvent(mainEvent);
		SDL_RenderClear(rR);

		SDL_SetRenderDrawColor(rR, 55, 55, 55, 255);
		SDL_RenderFillRect(rR, NULL);

		mouseInput();

		Update();
		Draw();

		SDL_RenderPresent(rR);
		
		if(SDL_GetTicks() - frameTime < MIN_FRAME_TIME) {
			SDL_Delay(MIN_FRAME_TIME - (SDL_GetTicks () - frameTime));
		}
	}
}

void CCore::Draw() {
	SDL_SetRenderDrawColor(rR, 200, 200, 200, 255);
	for(int i = 0; i < CCFG::GAME_WIDTH/2; i++) {
		for(int j = 0; j < CCFG::GAME_HEIGHT/2; j++) {
			if(oMap->getLive(i, j)) {
				currentRect.x = i*2;
				currentRect.y = j*2;
				SDL_RenderFillRect(rR, &currentRect);
			}
		}
	}
}

void CCore::Update() {
	if(SDL_GetTicks() > nextUpdate) {
		oMap->Update();
		nextUpdate = SDL_GetTicks() + 75;
	}
}

void CCore::mouseInput() {
	switch(mainEvent->type) {
		case SDL_MOUSEMOTION: {
			SDL_GetMouseState(&mouseX, &mouseY);
			if(mouseLeftPressed) {
				
						oMap->setLive(mouseX/2, mouseY/2, true);
						oMap->setLive(mouseX/2+1, mouseY/2, true);
						oMap->setLive(mouseX/2-1, mouseY/2, true);
						oMap->setLive(mouseX/2-2, mouseY/2, true);
					}
			break;
		}
		case SDL_MOUSEBUTTONDOWN: {
			switch (mainEvent->button.button) {
				case SDL_BUTTON_LEFT:
					if(!mouseLeftPressed) {
						mouseLeftPressed = true;
						oMap->setLive(mouseX/2, mouseY/2, true);
						oMap->setLive(mouseX/2+1, mouseY/2, true);
						oMap->setLive(mouseX/2-1, mouseY/2, true);
						oMap->setLive(mouseX/2-2, mouseY/2, true);
					}
					break;
				case SDL_BUTTON_RIGHT:
					if(!mouseRightPressed) {
						mouseRightPressed = true;
					}
					break;
			}
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			switch (mainEvent->button.button) {
				case SDL_BUTTON_LEFT:
					if(mouseLeftPressed) {
						mouseLeftPressed = false;
						
					}
					break;
				case SDL_BUTTON_RIGHT:
					if(mouseRightPressed) {
						mouseRightPressed = false;
					}
					break;
			}
			break;
		}
		/*case SDL_MOUSEWHEEL:
			if(mainEvent->wheel.timestamp > SDL_GetTicks() - 2) {
				CCFG::getMM()->getLE()->mouseWheel(mainEvent->wheel.y);
			}
			break;*/
	}
}