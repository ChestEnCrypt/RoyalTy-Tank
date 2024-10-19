#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
using namespace sf;

const float PI = 3.14159f;

float resolution[] = {
    256.f,
    512.f,
    1024.f,
    2048.f
};

class MainWindow{
public:
    RenderWindow& window;
    RenderTexture renderTexture;
    Vector2u windowSize;
    VideoMode displayMode;
    float& res = resolution[1];
    struct _size {
        int x = 0;
        int y = 0;

        _size(int x = 0, int y = 0) : x(x), y(y) {}
    };

    struct Button : RenderTexture {
        Texture texture;
        _size pos;
        _size size;
        _size texSize;

        Button(const string& path, _size pos, _size size) : pos(pos), size(size) {
            if (!create(size.x, size.y)) {};
            if (!texture.loadFromFile(path)) {}
            texSize.x = texture.getSize().x / 3;
            texSize.y = texture.getSize().y / 3;

            Sprite peace;
            peace.setTexture(texture);

            for (int i = 0; i <= 1; i++) {
                for (int j = 0; j <= 1; j++) {
                    peace.setTextureRect(IntRect((texSize.x * 3 - texSize.x) * i, (texSize.y * 3 - texSize.y) * j, texSize.x, texSize.y));
                    peace.setPosition((size.x - texSize.x) * i, (size.y - texSize.y) * j);
                    draw(peace);
                }
            }

            for (int i = 0; i <= 1; i++) {
                peace.setTextureRect(IntRect(texSize.x, texSize.y * 2 * i, texSize.x, texSize.y));
                for (int j = texSize.x; j < size.x - texSize.x; j += texSize.x) {
                    peace.setPosition(j, (size.y - texSize.y) * i);
                    draw(peace);
                }
            }
            for (int i = 0; i <= 1; i++) {
                peace.setTextureRect(IntRect(texSize.x * 2 * i, texSize.y, texSize.x, texSize.y));
                for (int j = texSize.y; j < size.y - texSize.y; j += texSize.y) {
                    peace.setPosition((size.x - texSize.x) * i, j);
                    draw(peace);
                }
            }

            for (int i = texSize.x; i < size.x - texSize.x; i += texSize.x) {
                for (int j = texSize.y; j < size.y - texSize.y; j += texSize.y) {
                    peace.setTextureRect(IntRect(texSize.x, texSize.y, texSize.x, texSize.y));
                    peace.setPosition(i, j);
                    draw(peace);
                }
            }
            display();
        }
    };

    MainWindow(RenderWindow& window) : window(window)
    {
        windowSize = window.getSize();
        displayMode = VideoMode();

        if (!renderTexture.create(res, res)) {
            cerr << "Can't create renderTexture" << endl;
        }
    }

    MainWindow(const MainWindow& mainWindow)
        : window(mainWindow.window),
        windowSize(mainWindow.windowSize),
        displayMode(mainWindow.displayMode),
        res(mainWindow.res)
    {
        if (!renderTexture.create(res, res)) {
            cerr << "Can't create renderTexture" << endl;
        }
    }

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
                    windowSize = window.getSize();

                    if (windowSize.x < windowSize.y) {
                        windowSize.x = windowSize.y;
                        window.setSize(windowSize);
                    }

                    FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    window.setView(View(visibleArea));
                }
            }

            if (SceneLogic()) {
                break;
            }

            window.clear();
            SceneDraw();
            window.display();
        }
    }
    int num = 0;
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

        Sprite textureSprite(renderTexture.getTexture());
        textureSprite.setScale(windowSize.x / res, windowSize.x / res);

        window.draw(textureSprite);

        return 0;
    }
};

class GameWindow : public MainWindow {
public:
    Texture grassFloorTex;
    Texture tankTex;

    Sprite tank;
    int tankСoor[3] = {256, 256, 0};
    Sprite grassFloor;

    GameWindow(MainWindow& mainWindow) : MainWindow(mainWindow) {
        if (!grassFloorTex.loadFromFile("assets/images/floor/grass.png"));
        grassFloor.setTexture(grassFloorTex);

        if (!tankTex.loadFromFile("assets/images/entity/tank.png"));
        tank.setTexture(tankTex);
        tank.setOrigin(32, 32);
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
        renderTexture.draw(grassFloor);

        tank.setPosition(32, res * windowSize.y / windowSize.x - 32);
        renderTexture.draw(tank);

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
    RenderWindow window(VideoMode(960, 600), "RoyalTy-Tank");
    window.setFramerateLimit(60);

    SceneManager sceneManager;

    MainWindow mainWindow(window);
    //sceneManager.RunScene(mainWindow);

    MenuWindow menu(mainWindow);
    sceneManager.RunScene(menu);

    GameWindow game(mainWindow);
    sceneManager.RunScene(game);

    return 0;
}