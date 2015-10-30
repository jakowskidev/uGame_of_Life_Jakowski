#include "Map.h"
#include "CFG.h"
#include "stdlib.h"
#include "time.h"
#include <math.h>

Map::Map(void) {
	srand((unsigned)time(NULL));

	for(int i = 0; i < CCFG::GAME_WIDTH/2; i++) {
		std::vector<bool> temp;

		for(int j = 0; j < CCFG::GAME_HEIGHT/2; j++) {
			temp.push_back(false);
		}

		vLive.push_back(temp);
		nLive.push_back(temp);
	}
}

Map::~Map(void) {

}

void Map::Update() {
	for(int i = 0, iNum = 0; i < CCFG::GAME_WIDTH/2; i++) {
		for(int j = 0; j < CCFG::GAME_HEIGHT/2; j++) {
			
			for(int k = std::max(i - 1, 0); k < i + 2 && k < CCFG::GAME_WIDTH/2; k++) {
				for(int l = std::max(j - 1, 0); l < j + 2 && l < CCFG::GAME_HEIGHT/2; l++) {
					if(!(k == i && l == j)) {
						if(vLive[k][l]) ++iNum;
					}
				}
			}

			if(vLive[i][j]) {
				if(iNum == 2 || iNum == 3) {
					nLive[i][j] = true;
				} else {
					nLive[i][j] = false;
				}
			} else {
				if(iNum == 3) {
					nLive[i][j] = true;
				} else {
					nLive[i][j] = false;
				}
			}

			iNum = 0;
		}
	}

	for(int i = 0, iNum = 0; i < CCFG::GAME_WIDTH/2; i++) {
		for(int j = 0; j < CCFG::GAME_HEIGHT/2; j++) {
			vLive[i][j] = nLive[i][j];
		}
	}
}

bool Map::getLive(int X, int Y) {
	return vLive[X][Y];
}

void Map::setLive(int X, int Y, bool live) {
	vLive[X][Y] = live;
}