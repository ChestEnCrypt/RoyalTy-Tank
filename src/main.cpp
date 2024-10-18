#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <math.h>

using namespace std;
using namespace sf;

float PI = 3.14159f;

class MainWindow{
public:
    RenderWindow& window;
    RenderTexture renderTexture;
    Vector2u windowSize;
    VideoMode displayMode;
    int a = 0;

    MainWindow(RenderWindow& window) : window(window) {

        windowSize = window.getSize();
        displayMode = VideoMode();

        if (!renderTexture.create(1080, 1080)) {
            cerr << "Can't create renderTexture" << endl;
        }
    }

    MainWindow(const MainWindow& mainWindow)
        : window(mainWindow.window),
        windowSize(mainWindow.windowSize),
        displayMode(mainWindow.displayMode) {}

    virtual int SceneLogic() { return 0; }
    virtual int SceneDraw() { return 0; }

    void SceneRun() {
        cout << "SceneRun" << endl;
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                else if (event.type == Event::Resized) {
                    FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    window.setView(View(visibleArea));
                }
            }
            window.clear();

            if (SceneLogic()) {
                break;
            }

            SceneDraw();

            window.display();
        }
    }
    int num = 0;
};

class MenuWindow : public MainWindow {
public:
    Text press;
    Font consolas;

    MenuWindow(MainWindow& mainWindow) : MainWindow(mainWindow) {
        if (!consolas.loadFromFile("assets/fonts/Consolas.ttf")) {}
        press.setFont(consolas);
        press.setString("PRESS SPACE TO CONTINUE");
        press.setCharacterSize(32);
        press.setStyle(1);
        press.setPosition(300, 540);

        cout << "The necessary assets are included" << endl;
    }

    int SceneLogic() override {
        num++;

        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            return 1;
        }

        return 0;
    }

    int SceneDraw() override {

        window.draw(press);

        return 0;
    }
};

class GameWindow : public MainWindow {
public:
    struct MyTank : Sprite {
        float mySpriteCoor[3] = { 256, 256, 0 };
        Texture texture;

        MyTank() {
            if (!texture.loadFromFile("assets/images/entity/tank.png")) {}
            setTexture(texture);
            setOrigin(32, 32);
        }
    };

    struct GrassFloor : Sprite {
        Texture texture;
        Sprite sprite;

        GrassFloor() {
            if (!texture.loadFromFile("assets/images/floor/grass.png")) {}
            setTexture(texture);
        }
    };

    MyTank myTank;
    GrassFloor grassFloor;

    GameWindow(MainWindow& mainWindow) : MainWindow(mainWindow) {}

    int SceneLogic() override {

        int rotate = static_cast<int>(myTank.mySpriteCoor[2]) % 360;
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            myTank.mySpriteCoor[0] += 2.f * sin(rotate * PI / 180);
            myTank.mySpriteCoor[1] -= 2.f * cos(rotate * PI / 180);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            myTank.mySpriteCoor[0] -= 2.f * sin(rotate * PI / 180);
            myTank.mySpriteCoor[1] += 2.f * cos(rotate * PI / 180);
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            myTank.mySpriteCoor[2] -= 1.5f;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            myTank.mySpriteCoor[2] += 1.5f;
        }

        return 0;
    }

    int SceneDraw() override {

        for (int i = 0; i < 960 + 256; i+=256) {
            for (int j = 0; j < 600 + 256; j+=256) {
                grassFloor.setPosition(i, j);
                window.draw(grassFloor);
            }
        }

        myTank.setPosition(myTank.mySpriteCoor[0], myTank.mySpriteCoor[1]);
        myTank.setRotation(myTank.mySpriteCoor[2]);
        window.draw(myTank);

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
    filesystem::path currentPath = filesystem::current_path();
    cout << "Directory: " << currentPath << endl;

    RenderWindow window(VideoMode(960, 600), "RoyalTy-Tank");
    window.setFramerateLimit(60);

    MainWindow mainWindow(window);
    SceneManager sceneManager;

    MenuWindow menu(mainWindow);
    sceneManager.RunScene(menu);

    GameWindow game(mainWindow);
    sceneManager.RunScene(game);

    return 0;
}