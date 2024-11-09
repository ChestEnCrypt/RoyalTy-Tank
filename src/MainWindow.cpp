#include "MainWindow.hpp"

MainWindow::MainWindow(RenderWindow& _window, RenderTexture& _renderTexture, Place& place, float& res, bool& mouseVisible)
	: window(_window),
	renderTexture(_renderTexture),
	place(place),
	res(res),
	mouseVisible(mouseVisible),
	event(Event())
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
	res(mainWindow.res),
	mouseVisible(mainWindow.mouseVisible),
	event(Event())
{}

int MainWindow::SceneLogic() { return 1; }
int MainWindow::SceneDraw() { return 0; }

void MainWindow::SceneRun() {
	while (window.isOpen()) {
		event = Event();
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			//mousePos = Mouse::getPosition(window);

			if (event.type == Event::Resized) {
				windowSize = window.getSize();

				if (windowSize.x < windowSize.y) {
					windowSize.x = windowSize.y;
					window.setSize(windowSize);
				}
				else if (windowSize.x > windowSize.y * 2.5f) {
					windowSize.x = windowSize.y * 2.5f;
					window.setSize(windowSize);
				}

				visibleArea = FloatRect(0, 0, event.size.width, event.size.height);
				window.setView(View(visibleArea));
			}

			else if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Tab) {
					mouseVisible = !mouseVisible;
					window.setMouseCursorVisible(mouseVisible);
				}
			}
		}

		if (SceneLogic()) {
			break;
		}

		window.clear();
		SceneDraw();

		textureSprite.setTexture(renderTexture.getTexture());
		textureSprite.setScale(windowSize.x / res, windowSize.x / res);
		textureSprite.setTextureRect(IntRect(0, (res - windowSize.y / (windowSize.x / res)) / 2, res, windowSize.y / (windowSize.x / res)));

		window.draw(textureSprite);
		window.display();
	}
}
