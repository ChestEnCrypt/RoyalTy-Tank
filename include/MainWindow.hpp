#pragma once
#include <SFML/Graphics.hpp>
//#include <iostream>
#include <string>

using namespace std;
using namespace sf;

class MainWindow {
public:
	RenderWindow& window;
	RenderTexture& renderTexture;
	Vector2u windowSize;
	VideoMode displayMode;
	float& res;

	MainWindow(RenderWindow& _window, RenderTexture& _renderTexture, float& res);
	MainWindow(const MainWindow& mainWindow);

	virtual int SceneLogic();
	virtual int SceneDraw();

	void SceneRun();
};