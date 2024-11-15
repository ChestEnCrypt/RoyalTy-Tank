#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <array>

#include <map>
#include <utility>

using namespace std;
using namespace sf;

class Place : public RenderTexture {
public:
	string mapId;
	vector<string> mapIds = {
		"place1"
	};
	vector<string> mapPaths = {
		"assets/maps/map1.png"
	};

	float& res; // resolution of widow
	int rendering[2] = {0, 0};

	Sprite& stalk;

	Texture mapTexture;
	Sprite mapSprite;

	map<pair<int, int>, const Texture*> loadedTiles;
	map<pair<int, int>, Sprite> mapTiles;
	vector<Sprite> dravable;

	Place(float& res);

	void setMap(string mapId);
	void setStalk(Sprite& _stalk);

	//void update(int x, int y, int X, int Y);
	void update();
	void _draw(Sprite& sprite);

	Sprite getPlace(int x, int y, int X, int Y, float R);

	Sprite getPlaceNew(int x, int y, int X, int Y, float R);
};