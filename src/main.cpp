#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "MainWindow.hpp"
#include "Button.hpp"
#include "Place.hpp"

using namespace std;
using namespace sf;
using json = nlohmann::json;

const float PI = 3.14159f;

float resolution[] = {
	256.f,
	512.f,
	1024.f,
	2048.f
};

class MenuWindow : public MainWindow {
public:
	Font consolas;
	Text press;
	Button button;
	Sprite buttonSprite;

	MenuWindow(MainWindow& mainWindow)
		: MainWindow(mainWindow),
		button("assets/images/buttons/button8.png", _size(0, 0), _size(48, 24)),
		buttonSprite(button.getTexture())
	{
		if (!consolas.loadFromFile("assets/fonts/Consolas.ttf")) {}
		press.setFont(consolas);
		press.setString("PRESS SPACE TO CONTINUE");
		press.setCharacterSize(64);
		press.setStyle(1);
		press.setPosition(0, 500);

		cout << "MenuWindow : The necessary assets are included" << endl;
	}

	int SceneLogic() override {

		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			return 1;
		}

		return 0;
	}

	int SceneDraw() override {

		renderTexture.clear();
		renderTexture.draw(buttonSprite);
		renderTexture.display();

		return 0;
	}
};

class GameWindow : public MainWindow {
public:
	Texture grassFloorTex;
	Texture tankTex;

	Sprite tank;
	float tankСoor[3] = {256, 256, 90};
	Sprite grassFloor;

	GameWindow(MainWindow& mainWindow) : MainWindow(mainWindow) {
		if (!grassFloorTex.loadFromFile("assets/images/floor/grass.png"));
		grassFloor.setTexture(grassFloorTex);

		if (!tankTex.loadFromFile("assets/images/entity/tank.png"));
		tank.setTexture(tankTex);
		tank.setOrigin(32, 32);

		cout << windowSize.x << endl;
		cout << windowSize.y << endl;
	}

	int SceneLogic() override {

		int rotate = static_cast<int>(tankСoor[2]) % 360;
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			tankСoor[0] += 2.f * sin(rotate * PI / 180);
			tankСoor[1] -= 2.f * cos(rotate * PI / 180);
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			tankСoor[0] -= 2.f * sin(rotate * PI / 180);
			tankСoor[1] += 2.f * cos(rotate * PI / 180);
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			tankСoor[2] -= 1.5f;
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			tankСoor[2] += 1.5f;
		}

		return 0;
	}

	int SceneDraw() override {

		renderTexture.clear();

		//.setPosition(32, res * windowSize.y / windowSize.x - 32);
		tank.setPosition(tankСoor[0], tankСoor[1]);
		tank.setRotation(tankСoor[2]);
		place.update();
		place.draw(tank);
		place.display();

		renderTexture.draw(place.getPlace(tankСoor[0] - res / 2, tankСoor[1] - res / 2, res, res));

		renderTexture.display();

		Sprite textureSprite(renderTexture.getTexture());
		textureSprite.setScale(windowSize.x / res, windowSize.x / res);

		window.draw(textureSprite);

		return 0;
	}
};

class SceneManager {
public:
	void RunScene(MainWindow& scene) {
		scene.SceneRun();
	}
};

int main() {
	//ifstream configFile("config/config.json");
	//json config;

	//if (!configFile.is_open()) {
	//	cerr << "can't open file!" << endl;
	//	return 1;
	//}

	//configFile >> config;

	//string hello = config["hello"];

	Place place("place1");

	float& res = resolution[1];

	RenderWindow window(VideoMode(960, 600), "RoyalTy-Tank");
	window.setFramerateLimit(60);

	SceneManager sceneManager;

	RenderTexture renderTexture;
	MainWindow mainWindow(window, renderTexture, place, res);

	MenuWindow menu(mainWindow);
	sceneManager.RunScene(menu);

	GameWindow game(mainWindow);
	sceneManager.RunScene(game);

	return 0;
}