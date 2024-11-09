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

class angle {
private:
	float value = 0;

	float onAccess() {

		while (value < -181) {
			value += 360;
		}
		while (value > 180) {
			value -= 360;
		}

		return value;
	}

public:
	angle(float v = 0.f) : value(v) {}

	operator float() {
		return onAccess();
	}

	angle& operator+=(float rhs) {
		value += rhs;
		return *this;
	}
	angle& operator-=(float rhs) {
		value -= rhs;
		return *this;
	}
	angle& operator*=(float rhs) {
		value *= rhs;
		return *this;
	}
	angle& operator/=(float rhs) {
		value /= rhs;
		return *this;
	}
};

class MenuWindow : public MainWindow {
public:
	Font consolas;
	Text press;

	MenuWindow(MainWindow& mainWindow)
		: MainWindow(mainWindow)
	{
		if (!consolas.loadFromFile("assets/fonts/Consolas.ttf")) {}
		press.setFont(consolas);
		press.setString("PRESS SPACE TO CONTINUE");
		press.setCharacterSize(16);
		press.setStyle(1);
		press.setPosition(145, res / 2);

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
		renderTexture.draw(press);
		renderTexture.display();

		return 0;
	}
};

class GameWindow : public MainWindow {
public:
	Button button;
	Sprite buttonSprite;

	Sprite tankBody;
	Sprite tankTurret;

	Texture tankBodyTex;
	Texture tankTurretTex;

	float tankCoor[3] = {512.f, 512.f, 0.f};
	angle tankTurretAngle = 0.f;
	angle cameraManAngle = 0.f;

	Vector2i mousePos = Mouse::getPosition();
	
	GameWindow(MainWindow& mainWindow)
		: MainWindow(mainWindow),
		button("assets/images/buttons/button2.png", _size(0, 0), _size(48, 24)),
		buttonSprite(button.getTexture())
	{
		if (!tankBodyTex.loadFromFile("assets/images/entity/tankBody.png"));
		tankBody.setTexture(tankBodyTex);
		tankBody.setOrigin(32, 32);

		if (!tankTurretTex.loadFromFile("assets/images/entity/tankTurret.png"));
		tankTurret.setTexture(tankTurretTex);
		tankTurret.setOrigin(20, 20);
	}

	int SceneLogic() override {

		int rotate = static_cast<int>(tankCoor[2]) % 360;
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			tankCoor[0] += 2.f * sin(rotate * PI / 180.f);
			tankCoor[1] -= 2.f * cos(rotate * PI / 180.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			tankCoor[0] -= 2.f * sin(rotate * PI / 180.f);
			tankCoor[1] += 2.f * cos(rotate * PI / 180.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			tankCoor[2] -= 1.5f;
			tankTurretAngle -= 1.5f;
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			tankCoor[2] += 1.5f;
			tankTurretAngle += 1.5f;
		}

		if (!mouseVisible) {
			mousePos = Mouse::getPosition();

			mousePos.x = window.getPosition().x + window.getSize().x / 2.f;
			mousePos.y = window.getPosition().y + window.getSize().y / 2.f;

			if (!Keyboard::isKeyPressed(Keyboard::Tab)) {
				cameraManAngle += (window.getPosition().x + window.getSize().x / 2.f - Mouse::getPosition().x) / -10.f;
			}

			Mouse::setPosition(mousePos);
		}

		angle rotation = cameraManAngle - tankTurretAngle;
		float turn = 2.f;

		if (Mouse::isButtonPressed(Mouse::Right)) {
			turn /= 2.f;
		}

		if (rotation < 0) {
			tankTurretAngle -= turn;
		}
		else if (0 < rotation) {
			tankTurretAngle += turn;
		}
		if (-turn < rotation && rotation < turn) {
			tankTurretAngle = cameraManAngle;
		}

		return 0;
	}

	int SceneDraw() override {

		renderTexture.clear();


		//.setPosition(32, res * windowSize.y / windowSize.x - 32);
		//tank.setPosition(tankCoor[0], tankCoor[1]);
		//tank.setRotation(tankCoor[2]);

		//cout << tankCoor[0] << '\t' << tankCoor[1] << endl;

		tankBody.setPosition(tankCoor[0], tankCoor[1]);
		tankBody.setRotation(tankCoor[2]);
		
		tankTurret.setPosition(tankCoor[0], tankCoor[1]);
		tankTurret.setRotation(tankTurretAngle);

		place.setStalk(tankBody);
		place.update(
			-res,
			-res,
			res * 4,
			res * 4
		);
		place.draw(tankBody);
		place.draw(tankTurret);
		place.display();

		renderTexture.draw(place.getPlace(
			-res,
			-res,
			res * 4,
			res * 4,
			-cameraManAngle)
		);

		//renderTexture.draw(buttonSprite);

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

	float& res = resolution[2];
	bool mouseVisible = true;

	Place place(res);
	place.setMap("place1");

	RenderWindow window(VideoMode(960, 600), "RoyalTy-Tank");
	window.setFramerateLimit(60);

	SceneManager sceneManager;

	RenderTexture renderTexture;
	MainWindow mainWindow(window, renderTexture, place, res, mouseVisible);

	MenuWindow menu(mainWindow);
	sceneManager.RunScene(menu);

	GameWindow game(mainWindow);
	sceneManager.RunScene(game);

	return 0;
}
