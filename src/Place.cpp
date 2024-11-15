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

	for (int i = 0; i < mapTexture.getSize().x; i += 512) {
		for (int j = 0; j < mapTexture.getSize().y; j += 512) {
			mapSprite.setTextureRect(IntRect(i, j, 512, 512));
			loadedTiles[{ i, j }] = mapSprite.getTexture();
			mapTiles[{ i, j }] = Sprite(*loadedTiles[{ i, j }]);
		}
	}

	if (!create(2 * res, 2 * res)) {}
}

void Place::setStalk(Sprite& _stalk) {
	stalk = _stalk;
}

void Place::update() {
	int x = stalk.getPosition().x - res / 2;
	int y = stalk.getPosition().y - res / 2;
	int X = stalk.getPosition().x + res / 2;
	int Y = stalk.getPosition().y + res / 2;
	clear();

	for (int i = x / 512 * 512; i < X; i += 512) {
		for (int j = y / 512 * 512; j < Y; j += 512) {

			Sprite s_draw = mapTiles[{ i, j }];

			Vector2f s_pos = s_draw.getPosition();
			s_pos.x -= stalk.getPosition().x - res;
			s_pos.y -= stalk.getPosition().y - res;
			s_draw.setPosition(s_pos);

			draw(s_draw);
		}
	}

	size_t d_size = dravable.size();

	for (int i = 0; i < d_size; i++) {
		Vector2f pos = dravable[i].getPosition();
		
		if (x < pos.x && pos.x < X) {
			if (y < pos.y && pos.y < Y) {
				Sprite s_draw = dravable[i];

				Vector2f s_pos = s_draw.getPosition();
				s_pos.x -= stalk.getPosition().x - res;
				s_pos.y -= stalk.getPosition().y - res;
				s_draw.setPosition(s_pos);

				draw(s_draw);
			}
		}
	}

	dravable.clear();
}

void Place::_draw(Sprite& sprite) {
	dravable.emplace_back(sprite);
}

Sprite Place::getPlaceNew(int x, int y, int X, int Y, float R) {
	Sprite place;

	return Sprite();
}

Sprite Place::getPlace(int x, int y, int X, int Y, float R) {

	const Texture& peaceOfTexture = getTexture();

	Sprite peaceOfSprite;
	peaceOfSprite.setTexture(peaceOfTexture);

	peaceOfSprite.setOrigin(2 * res, 2 * res);
	peaceOfSprite.setPosition(res / 2.f, res / 1.5f);
	peaceOfSprite.setRotation(R);

	peaceOfSprite.setTextureRect(IntRect(x, y, X, Y));
	
	return peaceOfSprite;
}