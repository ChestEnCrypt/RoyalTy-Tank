#include "MainWindow.hpp"

MainWindow::MainWindow(RenderWindow& _window, RenderTexture& _renderTexture, Place& place, float& res)
	: window(_window),
	renderTexture(_renderTexture),
	place(place),
	res(res)
{
	windowSize = window.getSize();
	displayMode = VideoMode();

	if (!renderTexture.create(res, res)) {}
}

MainWindow::MainWindow(const MainWindow& mainWindow)
	: window(mainWindow.window),
	windowSize(window.getSize()),
	displayMode(mainWindow.displayMode),
	renderTexture(mainWindow.renderTexture),
	place(mainWindow.place),
	res(mainWindow.res)
{}

int MainWindow::SceneLogic() { return 1; }
int MainWindow::SceneDraw() { return 0; }

void MainWindow::SceneRun() {
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

		Sprite textureSprite(renderTexture.getTexture());
		textureSprite.setScale(windowSize.x / res, windowSize.x / res);
		textureSprite.setTextureRect(IntRect(0, (res - windowSize.y / (windowSize.x / res)) / 2, res, windowSize.y / (windowSize.x / res)));

		window.draw(textureSprite);
		window.display();
	}
}
