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

struct TextureHeap {
    string path = "assets/images/notFound.png";
    Texture texture;

    TextureHeap(const string& newPath) {
        if (!texture.loadFromFile(newPath)) {
            cerr << "Failed to load texture from " << newPath << endl;
            if (!texture.loadFromFile(path)) {
                cerr << "Failed to load texture from " << path << endl;
            }
            else {
                cerr << "Loaded texture from " << path << endl;
            }
        }
        else {
            path = newPath;
        }
    }
};

struct SpriteHeap {
    string Id;
    Sprite sprite;

    SpriteHeap(const string& Id, const Texture& texture) : Id(Id) {
        sprite.setTexture(texture);
    }
};

struct FontHeap {
    // "D:\Projects\RoyalTy-Tank\build\Debug\assets\fonts\Consolas.ttf"
    string path = "Consolas.ttf";
    Font font;

    FontHeap(const string& newPath) {
        if (!font.loadFromFile("assets/fonts/" + newPath)) {
            cerr << "Failed to load font from " << newPath << endl;
            if (!font.loadFromFile("assets/fonts/" + path)) {
                cerr << "Failed to load font from " << newPath << endl;
            }
            cerr << "Loaded texture from " << path << endl;
        }
        else {
            path = newPath;
        }
    }
};

struct TextHeap {
    string Id;
    string message;
    Font font;
    int size = 24;
    Color color = Color::White;

    Text text;

    TextHeap(const string& Id, const Font& font, const string& message = "Default Text") : Id(Id), font(font), message(message) {
        text.setFont(font);
        text.setCharacterSize(size);
        text.setFillColor(color);
        text.setString(message);
    }
};

class AssetManager {
public:
    vector<TextureHeap> textures;
    vector<SpriteHeap> sprites;
    vector<FontHeap> fonts;
    vector<TextHeap> texts;
                                                                            // FIND
    Texture& myTexture(const string& path) {

        for (TextureHeap& texHeap : textures) {
            if (texHeap.path == path) {
                return texHeap.texture; // if texture is found
            }
        }

        textures.push_back(TextureHeap(path));

        return textures.back().texture;
    }

    Sprite& mySprite(const string& Id, Texture& texture = Texture()) {

        for (SpriteHeap& sprHeap : sprites) {
            if (sprHeap.Id == Id) {
                return sprHeap.sprite; // if sprite is found
            }
        }
        sprites.push_back(SpriteHeap(Id, texture));

        return sprites.back().sprite;
    }

    Font& myFont(const string& path) {

        for (FontHeap& fntHeap : fonts) {
            if (fntHeap.path == path) {
                return fntHeap.font;
            }
        }

        fonts.push_back(FontHeap(path));

        return fonts.back().font;
    }

    Text& myText(const string Id, Font& font = Font()) {

        for (TextHeap& txtHeap : texts) {
            if (txtHeap.Id == Id) {
                return txtHeap.text;
            }
        }

        texts.push_back(TextHeap(Id, font));

        return texts.back().text;
    }

                                                                            // INCLUDE

    //Texture& includeTexture(const string& path) {
    //    textures.push_back(TextureHeap(path));

    //    // texture from path created
    //    return textures.back().texture;
    //}

    //Sprite& includeSprite(const string& Id, const Texture& texture) {
    //    sprites.push_back(SpriteHeap(Id, texture));

    //    // sprite from Id & texture created
    //    return sprites.back().sprite;
    //}

    //Font& includeFont(const string& path) {
    //    fonts.push_back(FontHeap(path));

    //    return fonts.back().font;
    //}

    //Text& includeText(const string& Id, const Font& font) {
    //    texts.push_back(TextHeap(Id, font));

    //    return texts.back().text;
    //}
};

class MainWindow{
public:
    AssetManager& asset;
    RenderWindow& window;
    RenderTexture renderTexture;
    Vector2u windowSize;

    MainWindow(RenderWindow& window, AssetManager& asset) : window(window), asset(asset) {

        windowSize = window.getSize();

        if (!renderTexture.create(1920, 1920)) {
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
    MenuWindow(MainWindow& mainWindow) : MainWindow(mainWindow.window, mainWindow.asset) {

        asset.mySprite("myTank", asset.myTexture("assets/images/entity/tank.png"));
        asset.mySprite("myTank").setOrigin(32, 32);
        asset.mySprite("myTank").setRotation(90);

        asset.myText("1", asset.myFont("Consolas.ttf")).setString("PRESS SPACE TO CONTINUE");
        asset.myText("1").setCharacterSize(32);
        asset.myText("1").setPosition(300, 540);

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

        window.draw(asset.myText("1"));

        return 0;
    }
};

class GameWindow : public MainWindow {
public:
    struct MyTank {
        float mySpriteCoor[3] = { 256, 256, 0 };
    };

    MyTank myTank;

    GameWindow(MainWindow& mainWindow) : MainWindow(mainWindow.window, mainWindow.asset) {

        asset.mySprite("GrassFloor", asset.myTexture("assets/images/floor/grass.png"));
        asset.mySprite("MyTank", asset.myTexture("assets/images/entity/tank.png"));

        asset.mySprite("GrassFloor").setOrigin(128, 128);
        asset.mySprite("MyTank").setOrigin(32, 32);

        RenderTexture renderTexture;
        if (!renderTexture.create(1920, 1920)) {
            cerr << "can't create renderTexture" << endl;
        }
    }

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
                asset.mySprite("GrassFloor").setPosition(i, j);
                window.draw(asset.mySprite("GrassFloor"));
            }
        }

        asset.mySprite("MyTank").setPosition(myTank.mySpriteCoor[0], myTank.mySpriteCoor[1]);
        asset.mySprite("MyTank").setRotation(myTank.mySpriteCoor[2]);
        window.draw(asset.mySprite("MyTank"));

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

    AssetManager asset;

    RenderWindow window(VideoMode(960, 600), "RoyalTy-Tank");
    window.setFramerateLimit(60);

    MainWindow mainWindow(window, asset);
    SceneManager sceneManager;

    MenuWindow menu(mainWindow);
    sceneManager.RunScene(menu);

    GameWindow game(mainWindow);
    sceneManager.RunScene(game);

    return 0;
}