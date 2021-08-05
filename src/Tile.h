#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;
class Tile
{
public:
	sf::Vector2i pos;
	int x;
	int y;
	int height = 0;
	int width = 0;
	int flag = 0;
	int mine = 0;
	bool hidden = true;
	vector<Tile*> neighbors;

	Tile();
	Tile(sf::Vector2i pos);
};

