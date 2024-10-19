Описание кода:

[строки 1-4](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L1). Добавляется библиотека `<SFML/Graphics.hpp>`. Это библиотека оотвесчает за графический вывод интерфейса.
Снизу него добавляются стандартные библиотеки c++.

[строки 6-7](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L6-L7). Объявляются именные пространства `std` и `sf`, для того что бы каждый раз не использовать `std::` и `sf::` для более удобного понимание и быстрого написание кода.

[строка 9](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L9). Создана константная переменная `PI`.

[строка 11](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L11). Созддана множество `resolution` из типа `float`, они предназначены для создание под окна для более удобного управление адаптивности окна. Они служат таблицой доступных разрешений как в ютубе от 144 до 2K, но в моем случии это 256, 512, 1024, 2048. Это сделано для того что бы мои текстуры правильно отображались в экране.

[строка 18](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L18). Создана основной класс `MainWindow` для более удобного управление сценами игры. Следующие сцены должны унаследоваться от него иначе он не будет работать.

[строка 20](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L20). Создана окно `RenderWindow` с названием `window`. это основное окно. Дочери  класса будут его использовать для вывода графики на окно.

[строка 21](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L21). Создана подокно `RenderTexture` с названием `renderTexture` для большей адаптивности окна. Изначально все изображние выводятся на него, и только после вывода всех выводов графики, оно масштабируется под основной окно с помощью метода `setScale()`, не теряя свое соотношение, например, `1:1` было `1:1` стало после масштабирование. 

[строка 22](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L22). Создана переменная `Vector2u windowSize` для хранение размена онка запускаемой программы. `x` - ширина, `y` - высота.

[строка 23](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L23). Создана переменная `VideoMode displayMode` для хранение размера монитора. `width` - ширина, `heigth` - высота.

[строка 24](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L24). Создана ссылка на одну из чисел из `resolution`. Он и отвечает за быстрый доступ к активному разрешению.

[строка 25](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L25). Создана структура `_size` для хранение двух типов данный, например, размер, позиция, и т.п. Данные присваивается через коструктор в [src/main.cpp#L29].

[строка 32](https://github.com/ChestEnCrypt/RoyalTy-Tank/blob/c07d073d41c3364bd9954252b01e52de4765cf1a/src/main.cpp#L32). Создана структура `Button` унаследующего от `RenderTexture` для создание и корректного отображение его тектуры.
