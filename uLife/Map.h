#pragma once

#ifndef MAP_H
#define MAP_H

#include <vector>

class Map
{
private:
	std::vector<std::vector<bool>> vLive;
	std::vector<std::vector<bool>> nLive;
public:
	Map(void);
	~Map(void);

	void Update();

	bool getLive(int X, int Y);
	void setLive(int X, int Y, bool live);
};

#endif