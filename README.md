Описание кода:
```cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
```
Добавляется библиотека `<SFML/Graphics.hpp>`. Это библиотека оотвесчает за графический вывод интерфейса.
Снизу него добавляются стандартные библиотеки c++.

```cpp
using namespace std;
using namespace sf;
```
Объявляются именные пространства `std` и `sf`, для того что бы каждый раз не использовать `std::` и `sf::` для более удобного понимание и быстрого написание кода.

```cpp
const float PI = 3.14159f;
```
Создана константная переменная `PI`.

```cpp
float resolution[] = {
    256.f,
    512.f,
    1024.f,
    2048.f
};
```
 Созддана множество `resolution` из типа `float`, они предназначены для создание под окна для более удобного управление адаптивности окна. Они служат таблицой доступных разрешений как в ютубе от 144 до 2K, но в моем случии это 256, 512, 1024, 2048. Это сделано для того что бы мои текстуры правильно отображались в экране.

```cpp
class MainWindow{
```
Создана основной класс `MainWindow` для более удобного управление сценами игры. Следующие сцены должны унаследоваться от него иначе он не будет работать.

```cpp
RenderWindow& window;
```
Создана окно `RenderWindow` с названием `window`. это основное окно. Дочери  класса будут его использовать для вывода графики на окно.

```cpp
RenderTexture renderTexture;
```
Создана подокно `RenderTexture` с названием `renderTexture` для большей адаптивности окна. Изначально все изображние выводятся на него, и только после вывода всех выводов графики, оно масштабируется под основной окно с помощью метода `setScale()`, не теряя свое соотношение, например, `1:1` было `1:1` стало после масштабирование. 

```cpp
Vector2u windowSize;
```
Создана переменная `Vector2u windowSize` для хранение размена онка запускаемой программы. `x` - ширина, `y` - высота.

```cpp
VideoMode displayMode;
```
Создана переменная `VideoMode displayMode` для хранение размера монитора. `width` - ширина, `heigth` - высота.

```cpp
float& res = resolution[1];
```
Создана ссылка на одну из чисел из `resolution`. Он и отвечает за быстрый доступ к активному разрешению.

```cpp
struct _size {
        int x = 0;
        int y = 0;

        _size(int x = 0, int y = 0) : x(x), y(y) {}
    };
```
Создана структура `_size` для хранение двух типов данный, например, размер, позиция, и т.п. Данные присваивается через коструктор ```_size(int x = 0, int y = 0) : x(x), y(y) {}```.

```cpp
struct Button : RenderTexture { ... }
```
 Создана структура `Button` унаследующего от `RenderTexture` для создание и корректного отображение его тектуры.

```cpp
Texture texture;
```
Создается текструра `Texture texture` для хранение шаблона текстуры кнопки.

```cpp
_size pos, size, texSize;
```
Создаются `_size pos, size, texSize` для хранение позиции, размера, и размер частей шаблона текстуры кнопки, для упрощение будущий математики.

```cpp
Button(const string& path, _size pos, _size __size) : pos(pos), size(__size) { ... }
```
Создается конструктор структуры `Button(const string& path, _size pos, _size __size)`.

```cpp
if (!create(size.x, size.y)) {};
```
Создается `RenderTexture.create()` и с помощью оператора `if` можем определить произошла ли ошибка в этом пути создании `if (!create(size.x, size.y))`. Можно было и поместить код который должен был выполнится при ошибочной создани `RenderTexture`, я этого добовлять не стал, поскольку `SFML` сама оповещает об ошибке.

```cpp
if (!texture.loadFromFile(path)) {}
```
 Импортируется картинка `loadFromFile(path)` и присваивается к переменной `texture` с директории `path`. Альтернативно прошлому он может оповещать об ошибке, я добовлять не стал, и я сказал почему.

```cpp
texSize.x = texture.getSize().x / 3;
texSize.y = texture.getSize().y / 3;
```
Присваивается переменной `texSize.x` и `texSize.y` размеры текстуры `texture`, с помощью метода `getSize().x` и `getSize().y`, и делится они на `3` потому что, картина которую мы присваиваем к `texture`, делится на `9` ровные части

```cpp
setButtonPos(__pos);
setButtonSize(__size);
```
Вызывается метод для указание позиции кнопки и создание или пересоздание текстуры кнопки.

```cpp
void setButtonSize(_size __size) { ... }
```
В методе `setButtonSize` задается и размер кнопки а так же создается или пересоздается текстура кнопки. Не могу полностью описать код но концепцию могу рассказать.

```cpp
size = __size;
```
Присваивается размер кнопки.

```cpp
clear();
```
Очишает текстуру кнопки.

```cpp
Sprite peace;
peace.setTexture(texture);
```
Создается спрайт `peace` для вывода частей картинки кнопки в `renderTexture`, и задает текстуру на него.

Концепция последуещего кода

Текстура кнопки `peace` (изначально).
```example
1|2|3
4|5|6
7|8|9
```

И это должно превратится в это (результат).
```example
1|2|2|3
4|5|5|6
4|5|5|6
7|8|8|9
```

```cpp
for (int i = 0; i <= 1; i++) {
    for (int j = 0; j <= 1; j++) {
        peace.setTextureRect(IntRect((texSize.x * 3 - texSize.x) * i, (texSize.y * 3 - texSize.y) * j, texSize.x, texSize.y));
        peace.setPosition((size.x - texSize.x) * i, (size.y - texSize.y) * j);
        draw(peace);
    }
}
```
Углы `1`, `3`, `7`, `9`, вставляются только 1 за жадый угол соответствующем образом
```example
1|...|3
.|...|.
.|...|.
7|...|9
```

```cpp
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
```
И есть грани `2`, `4`, `6`, `8` которые должны копироватся столько раз, сколько в высоту и столько в ширину.
```example
.|2|2|.
4|...|6
4|...|6
.|8|8|.
```
Этот код состаит двух частей, сначало рисует горизонтальные части кнопки (`2`, `8`), и вторая часть кода выводит вертикальные части кнопки (`4`, `6`).


```cpp
for (int i = texSize.x; i < size.x - texSize.x; i += texSize.x) {
    for (int j = texSize.y; j < size.y - texSize.y; j += texSize.y) {
        peace.setTextureRect(IntRect(texSize.x, texSize.y, texSize.x, texSize.y));
        peace.setPosition(i, j);
        draw(peace);
    }
}
```
И центр `5` должен заполнить всю оставшиюся пространства.
```example
.|...|.
.|5|5|.
.|5|5|.
.|...|.
```

```cpp
display();
```
И в конце все это отрисовывается этим методом.

```cpp
void setButtonPos(_size __pos) {
    pos = __pos;
}
```
Создан метод для указываение позиции кнопки.
На этом структура `Button` закрывается.
```cpp
};
```

```cpp
MainWindow(RenderWindow& window) : window(window) { ... }
```
Создается конструктор класса `MainWindow`, и принимает он тип `RenderWindow& window`, `window` не является копией передающего аргумента, а ссылкой на него, тоесть передающийся и принимающийся объект остается одной и тойже объектом, а не отдельной копией. И присваивается к своиству `window` класса `MainWindow`.

```cpp
windowSize = window.getSize();
displayMode = VideoMode();
```
В конструкторе присваивается двум переменным а именно `windowSize` и `displayMode`, как описывал ранее `windowSize` - это размеры окна, `displayMode` - это размеры монтора.

```cpp
if (!renderTexture.create(res, res)) {
    cerr << "Can't create renderTexture" << endl;
}
```
Создается подокно с размера `res`x`res`. Для более адаптивности, как сказано ранее. И он имеет блок для сообщение об ошибке, ему выделено отдельное внимание потому что, это важный часть всего кода.

```cpp
MainWindow(const MainWindow& mainWindow)
```
Создается още один конструктор для копирования уже созданного `MainWindow` объекта.

```cpp
: window(mainWindow.window),
windowSize(mainWindow.windowSize),
displayMode(mainWindow.displayMode),
res(mainWindow.res)
```
каждая переменная копирует в сабя самого от переданного на конструктор `const MainWindow& mainWindow`.

```cpp
if (!renderTexture.create(res, res)) {
    cerr << "Can't create renderTexture" << endl;
}
```
`renderTexture` Создается еще раз потому что прошлый кадр нам уже не нужен в новой сцене, и не получится скопировать, поскольку конфеденциальность тоже важна.

```cpp
virtual int SceneLogic() { return 0; }
virtual int SceneDraw() { return 0; }
```
Создана виртуальные методы для изменение в будущем. И возвращаемое число от `SceneLogic()` определяет выход эз текущей сцены, И он же выполняет все механики. И на `SceneDraw()` выводится все изображение на `renderTexture`.

```cpp
void SceneRun() { ... }
```
И в методе `SceneRun()` активируется текущая сцена. В нем ничего не изменяется.

```cpp
while (window.isOpen()) { ... }
```
Этот цикл выполняется пока окно игры открыт.

```cpp
Event event;
while (window.pollEvent(event)) { ... }
```
Этот цикл перебирает все события которые происходят с окной игры.

```cpp
if (event.type == Event::Closed) {
    window.close();
}
```
Этот оператор проверяет не активно ли окна игры, если условия истино то закрывает окно.

```cpp
else if (event.type == Event::Resized) { ... }
```
Этот оператор проверяет, изменился ли размеры окна игры. Если условия истино, выполняет несколько важных частей адаптивности окна.

```cpp
windowSize = window.getSize();
```
Занаво фиксирует размеры окна игры.

```cpp
if (windowSize.x < windowSize.y) {
    windowSize.x = windowSize.y;
    window.setSize(windowSize);
}
```
И если высота больше чем ширина окна, сделает его квадратным `1:1`, поскольку `renderTexture` создан именно `1:1`.

```cpp
FloatRect visibleArea(0, 0, event.size.width, event.size.height);
window.setView(View(visibleArea));
```
Этот часть кода выполняет чуть ли не самую главную часть адаптивности экрана, если его убрать не смотря на созданные `renderTexture` и его масштабирование под окно, окно будет растягивать картину так, как будто он все еще находится на изначальных размерах окна.

```cpp
if (SceneLogic()) {
    break;
}
```
Этот оператор уже вне цикла для перебора событий, и он выполняет `SceneLogic()` и получает результат от него, если вернет число `1` то выйдет из цикла `while (window.isOpen()) { ... }`.

```cpp
window.clear();
SceneDraw();
```
С начало очищаем окна от предыдущего кадра и получаем нувый кадр с помощью `SceneDraw()`.

```cpp
Sprite textureSprite(renderTexture.getTexture());
textureSprite.setScale(windowSize.x / res, windowSize.x / res);
```
Тут создается спрайт который получает текстуру от `renderTexture`. Именно он и адаптируется под основной окно `window` с помощью метода `setScale()`. `windowSize.x / res` это процентное соотношение `res` от `window`. И подгоняет столько же в высоту и столько же в ширину, это помогает достичь сохранность соотношение сторон `1:1`.

```cpp
window.draw(textureSprite);
window.display();
```
Выводит `textureSprite` в окно и отрисовывает кадр.

И на этом полностью закрывается класс `MainWindow`.
```
};
```
