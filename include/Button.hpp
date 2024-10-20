#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

struct _size {
	int x = 0;
	int y = 0;

	_size(int x = 0, int y = 0) : x(x), y(y) {}
};

struct Button : public RenderTexture {
	Texture texture;
	_size pos, size, texSize;

	Button(const string path, _size pos, _size __size);

	void setButtonTex(string path);
	void setButtonSize(_size __size);
	void setButtonPos(_size __pos);

	void drawButtonTex();
};
