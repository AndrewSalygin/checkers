#include "../include/rules.h"

bool hit_checker(Desk *desk, Coordinate matrix_c, Coordinate matrix_n)
{
	Coordinate enemy_checker;
	if (matrix_n.y > matrix_c.y)
	{
		enemy_checker.y = matrix_n.y - 1;
	}
	else
	{
		enemy_checker.y = matrix_n.y + 1;
	}
	if (matrix_n.x > matrix_c.x)
	{
		enemy_checker.x = matrix_n.x - 1;
	}
	else
	{
		enemy_checker.x = matrix_n.x + 1;
	}
	if ((matrix_n.y == matrix_c.y + 2 || matrix_n.y == matrix_c.y - 2) &&
	 	(matrix_n.x == matrix_c.x + 2 || matrix_n.x == matrix_c.x - 2) &&
		(*desk)[enemy_checker.y][enemy_checker.x].figure_type != Empty)
	{
		clear_element((*desk)[enemy_checker.y][enemy_checker.x]);
		return true;
	}
	return false;
}

bool step_checker(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n,
		int &next_line)
{
	if (matrix_n.y == next_line && 
		(matrix_n.x == matrix_c.x + 1 || matrix_n.x == matrix_c.x - 1) &&
		(*desk)[matrix_n.y][matrix_n.x].figure_type == Empty)
	{
		return true;
	}
	return false;
}

bool rules(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n,
			Figure_Color color_passage)
{
	// Если выбранная фигура шашка
	if ((*desk)[matrix_c.y][matrix_c.x].figure_type == Checker)
	{
		// Следующая линия, на которую ступит пешка
		int next_line;
		if ((*desk)[matrix_c.y][matrix_c.x].figure_color == White)
		{
			// Подготовка переменных для выбранного цвета
			next_line = matrix_c.y + 1;
		}
		else
		{
			// Подготовка переменных для выбранного цвета
			next_line = matrix_c.y - 1;
		}
		// Шаг:
		if (step_checker(desk, matrix_c, matrix_n, next_line))
		{
			return true;
		}

		// Удар:
		if (hit_checker(desk, matrix_c, matrix_n))
		{
			return true;
		}
		// Множественный удар

	}
	// Если выбранная фигура дамка
	if ((*desk)[matrix_c.y][matrix_c.x].figure_type == King)
	{
		return true;
	}
	return false;
}