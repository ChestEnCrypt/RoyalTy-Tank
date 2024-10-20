#include "Button.hpp"

Button::Button(const string path, _size pos, _size __size) {
	setButtonTex(path);
	setButtonPos(pos);
	setButtonSize(__size);
}

void Button::drawButtonTex() {
	if (!create(size.x, size.y)) {};

	clear();

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

void Button::setButtonTex(string path) {
	if (!texture.loadFromFile(path)) {}
	texSize.x = texture.getSize().x / 3;
	texSize.y = texture.getSize().y / 3;
}

void Button::setButtonSize(_size __size) {
	size = __size;
	drawButtonTex();
}

void Button::setButtonPos(_size __pos) {
	pos = __pos;
}