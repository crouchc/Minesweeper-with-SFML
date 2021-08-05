#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName) {
	string path = "../../images/";
	path += fileName + ".png";
	textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string texturename) {
	if (textures.find(texturename) == textures.end()) {
		LoadTexture(texturename);
	}

	return textures[texturename];
}

void TextureManager::Clear() {
	textures.clear();
}
