#include "../include/move_checkers.h"

// Движение фигур
bool move_checkers(Desk *desk, std::string &step, Figure_Color color_passage)
{
	// Координаты выбранной фигуры
	Coordinate matrix_c;
	Coordinate matrix_n;

	matrix_c.y = (int)step[1] - 49;
	matrix_c.x = (int)step[0] - 97;

	matrix_n.y = (int)step[3] - 49;
	matrix_n.x = (int)step[2] - 97;

	// Проверяем возможность такого хода
	if (rules(desk, matrix_c, matrix_n, color_passage))
	{
		// Меняем элементы в массиве друг с другом 
		swap_checkers(desk, matrix_c, matrix_n);

		// Удаляем элемент, который мы поменяли
		clear_element((*desk)[matrix_c.y][matrix_c.x]);
		return true;
	}
	return false;
}