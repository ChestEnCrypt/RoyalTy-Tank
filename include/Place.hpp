#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

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

	Sprite Map;
	Texture MapTexture;
	Sprite MapSprite;

	Place(string mapId);

	void update();

	Sprite getPlace(int x, int y, int X, int Y);
};