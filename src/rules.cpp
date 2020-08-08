#include "../include/rules.h"

bool hit_checker(Desk *desk, int &next_line, int &next_column, int &hit_column,
		int &hit_line, Coordinate matrix_n)
{
	if (matrix_n.y == hit_line && matrix_n.x == hit_column &&
		(*desk)[next_line][next_column].figure_type != Empty)
	{
		clear_element((*desk)[next_line][next_column]);
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
		int next_column;
		int hit_line;
		int hit_column;
		if ((*desk)[matrix_c.y][matrix_c.x].figure_color == White)
		{
			// Подготовка переменных для выбранного цвета
			next_line = matrix_c.y + 1;
			next_column = matrix_c.x + 1;
			hit_line = matrix_c.y + 2;
			hit_column = matrix_c.x + 2;
		}
		else
		{
			// Подготовка переменных для выбранного цвета
			next_line = matrix_c.y - 1;
			next_column = matrix_c.x + 1;
			hit_line = matrix_c.y - 2;
			hit_column = matrix_c.x + 2;
		}
		// Шаг:
		if (step_checker(desk, matrix_c, matrix_n, next_line))
		{
			return true;
		}

		// Удар:
		if (hit_checker(desk, next_line, next_column, hit_column, hit_line,
				matrix_n))
		{
			return true;
		}
		next_column = matrix_c.x - 1;
		hit_column  = matrix_c.x - 2;
		if (hit_checker(desk, next_line, next_column, hit_column, hit_line,
				matrix_n))
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