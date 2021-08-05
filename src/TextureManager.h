#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include<unordered_map>
using namespace std;

class TextureManager
{
	static void LoadTexture(string filename);
public:
	static sf::Texture& GetTexture(string ftexturename);
	static void Clear();
	static unordered_map<string, sf::Texture> textures;
};

