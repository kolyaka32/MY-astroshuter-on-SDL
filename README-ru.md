# Игра "Астрошутер"
[![en](https://img.shields.io/badge/lang-en-green.svg)](https://github.com/kolyaka32/Astroshuter-on-SDL/blob/master/README.md)

Этот репозиторий содержит файлы для сборки игры в жанре 'shoot-em-up' 'Астрошутер', написанной на c++ используя библитеки SDL3

![Изображение игры](/screenshots/game-main.png?raw=true)

## Установка игры
1. Скачать архив из [релизы](https://github.com/kolyaka32/Astroshuter-on-SDL/releases), распокавать и запустить 'Astroshooter.exe'!
2. Вы можете сами собрать этот проект, для этого смотрите пункт 'Установка для собственного использования'.


## Game
После запуска игры вы можете уничтожать и уклоняться от астероидов.
Единственная цель - прожить как можно дольше и получить максимальный счёт.
Для дополнительного интереса вы можете собирать бонусы и улучшения.
Дополнительные настройки могут быть изменены в файле 'settings1.ini'


## Поддерживаемые языки
* Английский
* Русский


![Изображение меню](/screenshots/game-menu-ru.png?raw=true)


## Установка для собственного использования (windows)
1. Установить компилятор для C++ (например [MSYS2](https://www.msys2.org/#installation));
2. Установить [Make](https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download);
3. Установить [CMake](https://sourceforge.net/projects/cmake.mirror/);
4. Скачать и разархивировать библиотеки SDL (готовые):
4.1. [SDL3](https://github.com/libsdl-org/SDL/releases);
4.2. [SDL3-image](https://github.com/libsdl-org/SDL_image/releases);
4.3. [SDL3-mixer](https://github.com/libsdl-org/SDL_mixer/releases);
4.4. [SDL3-ttf](https://github.com/libsdl-org/SDL_ttf/releases);
5. Дополнительная библиотека - libzip (компилируется самостоятельно), требуется:
5.1. [zlib](https://www.zlib.net/);
5.2. bzip (идёт вместе с GNU(с компилятор));
5.3. [сама libzip](https://libzip.org/download/);
5.4. Собрать libzip используя cmake в папку 'build/';
5.5. Запустить 'make' и 'make install' в командной строке в папке 'build' (с правами администратора);
6. (Опционально) Визуальная оболочка для редактирования кода [Visual Studio Code](https://code.visualstudio.com/download) (Рекомендуется для более простого использования с плагинами для c++ и cmake).


## Установка для собственного использования (unux системы)
1. Проверить наличие компиляторов [g++], [make] и [cmake];
2. Проверить наличие [git];
3. Установить (или собрать самому) следующие библиотеки:
4. Внешние SDL библиотеки ([SDL3](https://github.com/libsdl-org/SDL/releases), [SDL3-image](https://github.com/libsdl-org/SDL_image/releases), [SDL3-mixer](https://github.com/libsdl-org/SDL_mixer/releases), [SDL3-ttf](https://github.com/libsdl-org/SDL_ttf/releases));
5. Внешняя библиотека архивации (собирается самостоятельно): [libzip](https://libzip.org/download/);
6. (Опционально) Визуальная оболочка для редактирования кода [Visual Studio Code](https://code.visualstudio.com/download) (Рекомендуется для более простого использования с плагинами для c++ и cmake).


## Готовые исходники
Исходные файлы со всеми собранными библиотеками могут быть найден в [релизы](https://github.com/kolyaka32/Astroshuter-on-SDL/releases) (Development-kit).


## Использованные внешние зависимости:
* https://github.com/libsdl-org/SDL
* https://github.com/libsdl-org/SDL_image
* https://github.com/libsdl-org/SDL_mixer
* https://github.com/libsdl-org/SDL_ttf
* https://github.com/libsdl-org/SDL_net
* https://github.com/nih-at/libzip
