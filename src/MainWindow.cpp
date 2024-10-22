#include "MainWindow.hpp"

MainWindow::MainWindow(RenderWindow& _window, RenderTexture& _renderTexture, float& res)
	: window(_window),
	renderTexture(_renderTexture),
	res(res)
{
	//cout << 10 << endl;
	windowSize = window.getSize();
	displayMode = VideoMode();

	if (!renderTexture.create(res, res)) {
		//cerr << "Failed to create renderTexture" << endl;
	}
}

MainWindow::MainWindow(const MainWindow& mainWindow)
	: window(mainWindow.window),
	windowSize(mainWindow.windowSize),
	displayMode(mainWindow.displayMode),
	renderTexture(mainWindow.renderTexture),
	res(mainWindow.res)
{}

int MainWindow::SceneLogic() { return 1; }
int MainWindow::SceneDraw() { return 0; }

void MainWindow::SceneRun() {
	//cout << "SceneRun" << endl;
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

		window.draw(textureSprite);
		window.display();
	}
}