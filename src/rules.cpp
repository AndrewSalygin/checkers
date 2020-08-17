#include "../include/rules.h"
#include <iostream>

void checker_to_king(Desk *desk, Coordinate &matrix_c)
{
	if (matrix_c.y == 7 && (*desk)[matrix_c.y][matrix_c.x].figure_color == White)
	{
		(*desk)[matrix_c.y][matrix_c.x].figure_type = King;
	}
	if (matrix_c.y == 0 && (*desk)[matrix_c.y][matrix_c.x].figure_color == Black)
	{
		(*desk)[matrix_c.y][matrix_c.x].figure_type = King;
	}
}

void func_in_hit_n_step(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n)
{
	// Меняем элементы в массиве друг с другом 
	swap_checkers(desk, matrix_c, matrix_n);

	// Удаляем элемент, который мы поменяли
	clear_element((*desk)[matrix_c.y][matrix_c.x]);
}

bool if_in_hit_checker(Desk *desk, Coordinate matrix_c, Coordinate matrix_n,
		Coordinate &enemy_checker)
{
	if ((*desk)[enemy_checker.y][enemy_checker.x].figure_type != Empty &&
		(*desk)[enemy_checker.y][enemy_checker.x].figure_color != 
		(*desk)[matrix_c.y][matrix_c.x].figure_color && 
		(*desk)[matrix_n.y][matrix_n.x].figure_type == Empty)
	{
		return true;
	}
	return false;
}
bool hit_checker(Desk *desk, Coordinate matrix_c, Coordinate matrix_n,
		Coordinate &enemy_checker)
{
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
	if (matrix_n.y == matrix_c.y + 2 && matrix_n.x == matrix_c.x + 2)
	{
		if (if_in_hit_checker(desk, matrix_c, matrix_n, enemy_checker))
			return true;
	}
	if (matrix_n.y == matrix_c.y + 2 && matrix_n.x == matrix_c.x - 2)
	{
		if (if_in_hit_checker(desk, matrix_c, matrix_n, enemy_checker))
			return true;
	}
	if (matrix_n.y == matrix_c.y - 2 && matrix_n.x == matrix_c.x + 2)
	{
		if (if_in_hit_checker(desk, matrix_c, matrix_n, enemy_checker))
			return true;
	}
	if (matrix_n.y == matrix_c.y - 2 && matrix_n.x == matrix_c.x - 2)
	{
		if (if_in_hit_checker(desk, matrix_c, matrix_n, enemy_checker))
			return true;
	}
	return false;
}

bool check_all_hit_checker(Desk *desk, Figure_Color &color_passage,
					 Coordinate &enemy_checker)
{
	Coordinate coordinate_c;
	Coordinate coordinate_n;
	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			if ((*desk)[y][x].figure_type == Checker &&
				(*desk)[y][x].figure_color == color_passage)
			{
				coordinate_c.x = x;
				coordinate_c.y = y;
				if (y < 6)
				{
					coordinate_n.y = y + 2;
				}
				if (x < 6)
				{
					coordinate_n.x = x + 2;
				}
				if (hit_checker(desk, coordinate_c, coordinate_n, enemy_checker))
				{
					return true;
				}
				if (y > 1)
				{
					coordinate_n.y = y - 2;
				}				
				if (hit_checker(desk, coordinate_c, coordinate_n, enemy_checker))
				{
					return true;
				}
				if (x > 1)
				{
					coordinate_n.x = x - 2;
				}
				if (y < 6)
				{
					coordinate_n.y = y + 2;	
				}
				if (hit_checker(desk, coordinate_c, coordinate_n, enemy_checker))
				{
					return true;
				}
				if (y > 1)
				{
					coordinate_n.y = y - 2;
				}
				if (x > 1)
				{
					coordinate_n.x = x - 2;
				}
				
				if (hit_checker(desk, coordinate_c, coordinate_n, enemy_checker))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool step_checker(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n,
		int &next_line, Figure_Color &color_passage)
{
	if (matrix_n.y == next_line && 
		(matrix_n.x == matrix_c.x + 1 || matrix_n.x == matrix_c.x - 1) &&
		(*desk)[matrix_n.y][matrix_n.x].figure_type == Empty &&
		(*desk)[matrix_c.y][matrix_c.x].figure_color == color_passage)
	{
		return true;
	}
	return false;
}

bool rules(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n,
			Figure_Color &color_passage)
{
	// Если выбранная фигура шашка
	if ((*desk)[matrix_c.y][matrix_c.x].figure_type == Checker)
	{
		Coordinate enemy_checker;
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
		if (step_checker(desk, matrix_c, matrix_n, next_line, color_passage))
		{
			if (check_all_hit_checker(desk, color_passage, enemy_checker))
			{
				return false;
			}
			func_in_hit_n_step(desk, matrix_c, matrix_n);
			checker_to_king(desk, matrix_n);
			return true;
		}

		// Удар:
		if (hit_checker(desk, matrix_c, matrix_n, enemy_checker) &&
				color_passage == (*desk)[matrix_c.y][matrix_c.x].figure_color)
		{
			func_in_hit_n_step(desk, matrix_c, matrix_n);
			clear_element((*desk)[enemy_checker.y][enemy_checker.x]);
			checker_to_king(desk, matrix_n);
			while (check_all_hit_checker(desk, color_passage, enemy_checker) ==
					true)
			{
				std::cout << "Введите следующую позицию пешки\nПример(d6f4): ";
				std::string step;
				check_input(step);
				// Правильность хода
				while (move_checkers(desk, step, color_passage) != true)
				{
					std::cout << "Неправильный ход!\n";
					check_input(step);
				}
			}
			return true;
		}

	}
	// Если выбранная фигура дамка
	if ((*desk)[matrix_c.y][matrix_c.x].figure_type == King)
	{
		return true;
	}
	return false;
}