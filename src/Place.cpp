#include "Place.hpp"

Place::Place(float& res)
	: res(res),
	stalk(Sprite())
{}

void Place::setMap(string mapId) {
	string mapPath;

	for (int i = 0; i < mapIds.size(); i++) {
		if (mapIds[i] == mapId) {
			mapPath = mapPaths[i];
		}
	}

	if (!mapTexture.loadFromFile(mapPath)) {};
	mapSprite.setTexture(mapTexture);

	if (!create(res, res)) {}
	draw(mapSprite);
}

void Place::setStalk(Sprite& _stalk) {
	stalk = _stalk;
}

void Place::update(int x, int y, int X, int Y) {
	clear();

	rendering[0] = x;
	rendering[1] = y;

	mapSprite.setTextureRect(IntRect(x, y, X, Y));
	mapSprite.setPosition(x, y);

	draw(mapSprite);
}

void Place::_draw(Sprite sprite) {
	Vector2f pos = sprite.getPosition();
	pos.x -= rendering[0];
	pos.y -= rendering[1];
	sprite.setPosition(pos);

	draw(sprite);
}

Sprite Place::getPlaceNew(int x, int y, int X, int Y, float R) {
	Sprite place;

	return Sprite();
}

Sprite Place::getPlace(int x, int y, int X, int Y, float R) {

	const Texture& peaceOfTexture = getTexture();

	Sprite peaceOfSprite;
	peaceOfSprite.setTexture(peaceOfTexture);

	peaceOfSprite.setOrigin(stalk.getPosition().x + res, stalk.getPosition().y + res);
	peaceOfSprite.setPosition(res / 2.f, res / 1.5f);
	peaceOfSprite.setRotation(R);

	peaceOfSprite.setTextureRect(IntRect(x, y, X, Y));
	
	return peaceOfSprite;
}