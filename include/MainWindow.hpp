#pragma once
#include <SFML/Graphics.hpp>
#include "Place.hpp"
#include <string>

using namespace std;
using namespace sf;

class MainWindow {
public:
	RenderWindow& window;
	RenderTexture& renderTexture;
	Place& place;
	Vector2u windowSize;
	VideoMode displayMode;
	float& res;

	MainWindow(RenderWindow& _window, RenderTexture& _renderTexture, Place& place, float& res);
	MainWindow(const MainWindow& mainWindow);

	virtual int SceneLogic();
	virtual int SceneDraw();

	void SceneRun();
};