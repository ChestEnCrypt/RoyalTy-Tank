#pragma once
#include <SFML/Graphics.hpp>
#include "Place.hpp"
#include <string>

using namespace std;
using namespace sf;

class MainWindow {
public:
	Event event;

	RenderWindow& window;
	RenderTexture& renderTexture;
	Sprite textureSprite;
	Place& place;
	Vector2u windowSize;
	VideoMode displayMode;
	Vector2i mousePos;

	FloatRect visibleArea;

	bool& mouseVisible;
	float& res;

	MainWindow(RenderWindow& _window, RenderTexture& _renderTexture, Place& place, float& res, bool& mouseVisible);
	MainWindow(const MainWindow& mainWindow);

	virtual int SceneLogic();
	virtual int SceneDraw();

	void SceneRun();
};