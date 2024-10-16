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
                                                                            // FIND
    Texture& findTexture(const string& path) {

        for (TextureHeap& texHeap : textures) {
            if (texHeap.path == path) {
                return texHeap.texture; // if texture is found
            }
        }

        // if texture is not found
        return includeTexture(path);
    }

    Sprite& findSprite(const string& Id, Texture& texture = Texture()) {

        for (SpriteHeap& sprHeap : sprites) {
            if (sprHeap.Id == Id) {
                return sprHeap.sprite; // if sprite is found
            }
        }

        // if sprite is not found
        return includeSprite(Id, textures[0].texture);
    }

    Font& findFont(const string& path) {

        for (FontHeap& fntHeap : fonts) {
            if (fntHeap.path == path) {
                return fntHeap.font;
            }
        }

        return includeFont(path);
    }

    Text& findText(const string Id) {

        for (TextHeap& txtHeap : texts) {
            if (txtHeap.Id == Id) {
                return txtHeap.text;
            }
        }

        return includeText(Id, findFont("Consolas.ttf"));
    }

                                                                            // INCLUDE

    Texture& includeTexture(const string& path) {
        textures.push_back(TextureHeap(path));

        // texture from path created
        return textures.back().texture;
    }

    Sprite& includeSprite(const string& Id, const Texture& texture) {
        sprites.push_back(SpriteHeap(Id, texture));

        // sprite from Id & texture created
        return sprites.back().sprite;
    }

    Font& includeFont(const string& path) {
        fonts.push_back(FontHeap(path));

        return fonts.back().font;
    }

    Text& includeText(const string& Id, const Font& font) {
        texts.push_back(TextHeap(Id, font));

        return texts.back().text;
    }

private:
    vector<TextureHeap> textures;

    vector<SpriteHeap> sprites;

    vector<FontHeap> fonts;

    vector<TextHeap> texts;
};

class MainWindow{
public:
    MainWindow(RenderWindow& window, AssetManager& asset) : window(window), asset(asset) {
        asset.findFont("Consolas.ttf");
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
            }
            window.clear();

            if (SceneLogic()) {
                break;
            }

            this_thread::sleep_for(chrono::milliseconds(8));

            SceneDraw();

            window.display();
        }
    }
    int num = 0;
private:
    AssetManager& asset;
protected:
    RenderWindow& window;
};

class MenuWindow : public MainWindow {
public:
    MenuWindow(RenderWindow& window, AssetManager& asset) : MainWindow(window, asset), asset(asset) {
        //asset.includeTexture("assets/images/entity/tank.png");
        asset.includeSprite("myTank", asset.findTexture("assets/images/entity/tank.png"));
        asset.findSprite("myTank").setOrigin(32, 32);
        asset.findSprite("myTank").setRotation(90);

        asset.includeText("1", asset.findFont("Consolas.ttf")).setString("PRESS SPACE TO CONTINUE");
        asset.findText("1").setCharacterSize(32);
        asset.findText("1").setPosition(300, 540);

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

        window.draw(asset.findText("1"));

        return 0;
    }
private:
    AssetManager& asset;
};

class GameWindow : public MainWindow {
public:
    struct MyTank {
        float mySpriteCoor[3] = { 256, 256, 0 };
    };

    MyTank myTank;

    GameWindow(RenderWindow& window, AssetManager& asset)
        : MainWindow(window, asset), asset(asset) {//myTank(asset.includeSprite("MyTank", asset.findTexture("assets/images/entity/tank.png")))

        asset.includeSprite("MoneyBlock", asset.findTexture("assets/images/blocks/moneyBlock.png"));
        asset.includeSprite("GrassFloor", asset.findTexture("assets/images/floor/grass.png"));
        asset.findSprite("MyTank", asset.findTexture("assets/images/entity/tank.png"));

        asset.findSprite("GrassFloor").setOrigin(128, 128);
        asset.findSprite("MyTank").setOrigin(32, 32);

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
                asset.findSprite("GrassFloor").setPosition(i, j);
                window.draw(asset.findSprite("GrassFloor"));
            }
        }

        asset.findSprite("MyTank").setPosition(myTank.mySpriteCoor[0], myTank.mySpriteCoor[1]);
        asset.findSprite("MyTank").setRotation(myTank.mySpriteCoor[2]);
        window.draw(asset.findSprite("MyTank"));

        return 0;
    }

private:
    AssetManager& asset;
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
    SceneManager sceneManager;

    MenuWindow menu(window, asset);
    sceneManager.RunScene(menu);

    GameWindow game(window, asset);
    sceneManager.RunScene(game);

    return 0;
}