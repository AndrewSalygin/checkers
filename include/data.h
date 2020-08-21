#ifndef DATA_H
#define DATA_H
#include <array>

// Тип шашек
enum Figure_Type
{
	Empty,
	Checker,
	King
};

// Цвет шашек
enum Figure_Color
{
	None,
	White,
	Black
};

// Координаты
struct Coordinate
{
	int y;
	int x;
};

// Фигура
struct Figure
{
	Figure_Type figure_type;
	Figure_Color figure_color;
};

// Игровая доска
typedef std::array<std::array<Figure, 8>, 8> Desk;

#endif