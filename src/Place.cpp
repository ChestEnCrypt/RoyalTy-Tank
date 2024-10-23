#include "Place.hpp"

Place::Place(string mapId) : mapId(mapId){
	string mapPath;

	for (int i = 0; i < mapIds.size(); i++) {
		if (mapIds[i] == mapId) {
			mapPath = mapPaths[i];
		}
	}

	if (!MapTexture.loadFromFile(mapPath)) {};
	MapSprite.setTexture(MapTexture);
	
	if (!create(MapTexture.getSize().x, MapTexture.getSize().y)) {}
	draw(MapSprite);
}

void Place::update() {
	clear();
	draw(MapSprite);
}

Sprite Place::getPlace(int x, int y, int X, int Y) {
	const Texture& peaceOfTexture = getTexture();

	Sprite peaceOfSprite;
	peaceOfSprite.setTexture(peaceOfTexture);

	peaceOfSprite.setTextureRect(IntRect(x, y, X, Y));

	return peaceOfSprite;
}