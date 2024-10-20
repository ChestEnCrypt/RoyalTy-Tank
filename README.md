﻿Описание кода:
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

[строка 32](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L32). Создана структура `Button` унаследующего от `RenderTexture` для создание и корректного отображение его тектуры.

[строка 33](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L33). Создается текструра `Texture texture` для хранение шаблона текстуры кнопки.

[строка 34](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L34). Создаются `_size pos, size, texSize` для хранение позиции, размера, и размер частей шаблона текстуры кнопки, для упрощение будущий математики.

[строка 36](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L36). Создается конструктор структуры `Button(const string& path, _size pos, _size __size)` для присвоение нужных данных в переменные как `pos(pos), size(__size)`.

[строка 37](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L37). Создается `RenderTexture.create()` и с помощью оператора `if` можем определить произошла ли ошибка в этом пути создании `if (!create(size.x, size.y))`. Можно было и поместить код который должен был выполнится при ошибочной создани `RenderTexture`, я этого добовлять не стал, поскольку `SFML` сама оповещает об ошибке.

[строка 38](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L38). Импортируется картинка `loadFromFile(path)` и присваивается к переменной `texture` с директории `path`. Альтернативно прошлому он может оповещать об ошибке, я добовлять не стал, и я сказал почему.

[строка 39-40](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L39-L40). присваивается переменной `texSize.x` и `texSize.y` размеры текстуры `texture`, с помощью метода `getSize().x` и `getSize().y`, и делится они на `3` потому что, картина которую мы присваиваем к `texture`, делится на `9` ровные части

[строка 45](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L45). В методе `setButtonSize` задается и размер кнопки а так же создается или пересоздается текстура кнопки. Не могу полностью описать код но концепцию могу рассказать.

[строки 48-83](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L48-L83). Концепция кода

Текстура кнопки
`1|2|3`
`4|5|6`
`7|8|9`

И это должно превратится в это
`1|2|2|3`
`4|5|5|6`
`4|5|5|6`
`7|8|8|9`

Углы `1`, `3`, `7`, `9`, вставляются только 1 за жадый угол соответствующем образом
`1|...|3`
`.|...|.`
`.|...|.`
`7|...|9`

И есть грани `2`, `4`, `6`, `8` которые должны копироватся столько раз, сколько в высоту и столько в ширину.
`.|2|2|.`
`4|...|6`
`4|...|6`
`.|8|9|.`

И в конце центр `5` должен заполнить всю оставшиюся пространства.
`.|...|.`
`.|5|5|.`
`.|5|5|.`
`.|...|.`
