#include "../include/rules.h"

// Функция удара для дамок и шашек
bool if_in_hit_checker_n_king(Desk *desk, Coordinate matrix_c, Coordinate matrix_n,
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

// Операции в массиве
void func_in_hit_n_step(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n)
{
	// Меняем элементы в массиве друг с другом 
	swap_checkers(desk, matrix_c, matrix_n);

	// Удаляем элемент, который мы поменяли
	clear_element((*desk)[matrix_c.y][matrix_c.x]);
}

// Ходит дамка
bool step_king(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n)
{
	// Запоминаем переменные для дальнейшего их изменения
	int y_c = matrix_c.y;
	int y_n = matrix_n.y;
	int x_c = matrix_c.x;
	int x_n = matrix_n.x;

	// Ходим только по диагоналям y_c = x_c && y_n = x_n, поэтому x не проверяем
	while (y_c != y_n)
	{
		// Вверх
		if (matrix_n.y > matrix_c.y)
		{
			// Вправо
			if (matrix_n.x > matrix_c.x)
			{
				// Если следущая клетка пустая
				if ((*desk)[y_c + 1][x_c + 1].figure_type == Empty)
				{
					++y_c;
					++x_c;
				}
				else
				{
					return false;
				}
			}
			// Влево
			else
			{
				if ((*desk)[y_c + 1][x_c - 1].figure_type == Empty)
				{
					++y_c;
					--x_c;
				}
				else
				{
					return false;
				}
			}
		}
		// Вниз
		else
		{
			// Вправо
			if (matrix_n.x > matrix_c.x)
			{
				if ((*desk)[y_c - 1][x_c + 1].figure_type == Empty)
				{
					--y_c;
					++x_c;
				}
				else
				{
					return false;
				}
			}
			// Влево
			else
			{
				if ((*desk)[y_c - 1][x_c - 1].figure_type == Empty)
				{
					--y_c;
					--x_c;
				}
				else
				{
					return false;
				}
			}
		}
	}
	return true;
}

// Король атакует
bool hit_king(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n, 
	Coordinate &enemy_checker)
{
	// Количество вражеских фигур на пути
	int count = 0;

	int y_c = matrix_c.y;
	int y_n = matrix_n.y;
	int x_c = matrix_c.x;
	int x_n = matrix_n.x;

	while (y_c != y_n)
	{
		if (matrix_n.y > matrix_c.y)
		{
			if (matrix_n.x > matrix_c.x)
			{
				if ((*desk)[y_c + 1][x_c + 1].figure_type == Empty)
				{
					++y_c;
					++x_c;
				}
				else
				{
					++y_c;
					++x_c;

					// Запоминаем координаты вражеской фигуры
					enemy_checker.y = y_c;
					enemy_checker.x = x_c;

					// Две подряд фигуры не могут стоять на пути
					++count;
				}
			}
			else
			{
				if ((*desk)[y_c + 1][x_c - 1].figure_type == Empty)
				{
					++y_c;
					--x_c;
				}
				else
				{
					++y_c;
					--x_c;
					enemy_checker.y = y_c;
					enemy_checker.x = x_c;
					++count;
				}
			}
		}
		else
		{
			if (matrix_n.x > matrix_c.x)
			{
				if ((*desk)[y_c - 1][x_c + 1].figure_type == Empty)
				{
					--y_c;
					++x_c;
				}
				else
				{
					--y_c;
					++x_c;
					enemy_checker.y = y_c;
					enemy_checker.x = x_c;
					++count;
				}
			}
			else
			{
				if ((*desk)[y_c - 1][x_c - 1].figure_type == Empty)
				{
					--y_c;
					--x_c;
				}
				else
				{
					--y_c;
					--x_c;
					enemy_checker.y = y_c;
					enemy_checker.x = x_c;
					++count;
				}
			}
		}
	}
	if (count == 1)
	{
		return if_in_hit_checker_n_king(desk, matrix_c, matrix_n, enemy_checker);
	}
	return false;
}


bool check_current_hit_king(Desk *desk, Coordinate &enemy_checker,
									Coordinate &matrix_c)
{
	Coordinate coordinate_n;
	Coordinate inner;
	// Вверх влево
	inner.y = matrix_c.y + 1;
	inner.x = matrix_c.x - 1;
	while (inner.y < 7 && inner.x > 0)
	{
		if ((*desk)[inner.y][inner.x].figure_type != Empty)
		{
			if ((*desk)[inner.y + 1][inner.x - 1].figure_type == Empty)
			{
				++inner.y;
				--inner.x;
				break;
			}
		}
		++inner.y;
		--inner.x;
	}
	if (hit_king(desk, matrix_c, inner, enemy_checker))
	{
		return true;
	}
	// Вниз вправо
	inner.y = matrix_c.y - 1;
	inner.x = matrix_c.x + 1;
	while (inner.x < 7 && inner.y > 0)
	{
		if ((*desk)[inner.y][inner.x].figure_type != Empty)
		{
			if ((*desk)[inner.y - 1][inner.x + 1].figure_type == Empty)
			{
				--inner.y;
				++inner.x;
				break;
			}
		}
		--inner.y;
		++inner.x;
	}
	if (hit_king(desk, matrix_c, inner, enemy_checker))
	{
		return true;
	}

	// Вправо вверх
	inner.y = matrix_c.y + 1;
	inner.x = matrix_c.x + 1;

	while (inner.y < 7 && inner.x < 7)
	{
		if ((*desk)[inner.y][inner.x].figure_type != Empty)
		{
			if ((*desk)[inner.y + 1][inner.x + 1].figure_type == Empty)
			{
				++inner.y;
				++inner.x;
				break;
			}
		}
		++inner.y;
		++inner.x;
	}
	if (hit_king(desk, matrix_c, inner, enemy_checker))
	{
		return true;
	}

	// Вниз влево
	inner.y = matrix_c.y - 1;
	inner.x = matrix_c.x - 1;
	while (inner.y > 0 && inner.x > 0)
	{
		if ((*desk)[inner.y][inner.x].figure_type != Empty)
		{
			if ((*desk)[inner.y - 1][inner.x - 1].figure_type == Empty)
			{
				--inner.y;
				--inner.x;
				break;
			}
		}
		--inner.y;
		--inner.x;
	}
	if (hit_king(desk, matrix_c, inner, enemy_checker))
	{
		return true;
	}
	return false;
}

// Проверка, есть ли вариант удара, вместо ходьбы фигуры
bool check_all_hit_king(Desk *desk, Figure_Color &color_passage,
					 Coordinate &enemy_checker)
{
	// Внутренние координаты функции
	Coordinate coordinate_c;
	Coordinate coordinate_n;

	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			// Если король
			if ((*desk)[y][x].figure_type == King &&
				(*desk)[y][x].figure_color == color_passage)
			{
				coordinate_c.x = x;
				coordinate_c.y = y;
				if (check_current_hit_king(desk, enemy_checker, coordinate_c))
				{
					return true;
				}
			}
		}
	}
	return false;
}

int count = 0;

// Король
bool king(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n, 
	Coordinate &enemy_checker, Figure_Color &color_passage)
{
	// Ходим только по диагоналям
	if (abs(matrix_n.y - matrix_c.y) == abs(matrix_n.x - matrix_c.x))
	{
		// Проверяем ходит ли дамка
		if (step_king(desk, matrix_c, matrix_n))
		{
			if (!check_all_hit_king(desk, color_passage, enemy_checker))
			{
				func_in_hit_n_step(desk, matrix_c, matrix_n);
				return true;
			}
			return false;
		}

		// Проверяем ударяет ли король
		if (hit_king(desk, matrix_c, matrix_n, enemy_checker))
		{
			func_in_hit_n_step(desk, matrix_c, matrix_n);
			clear_element((*desk)[enemy_checker.y][enemy_checker.x]);
			if (check_current_hit_king(desk, enemy_checker, matrix_n))
			{
				std::cout << "Введите следующую позицию дамки\nПример(e1b4): ";
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
	return false;
}

// При достижении последней горизонтали происходит превращение шашки в дамку
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

// Шашка атакует
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
		if (if_in_hit_checker_n_king(desk, matrix_c, matrix_n, enemy_checker))
			return true;
	}
	if (matrix_n.y == matrix_c.y + 2 && matrix_n.x == matrix_c.x - 2)
	{
		if (if_in_hit_checker_n_king(desk, matrix_c, matrix_n, enemy_checker))
			return true;
	}
	if (matrix_n.y == matrix_c.y - 2 && matrix_n.x == matrix_c.x + 2)
	{
		if (if_in_hit_checker_n_king(desk, matrix_c, matrix_n, enemy_checker))
			return true;
	}
	if (matrix_n.y == matrix_c.y - 2 && matrix_n.x == matrix_c.x - 2)
	{
		if (if_in_hit_checker_n_king(desk, matrix_c, matrix_n, enemy_checker))
			return true;
	}
	return false;
}

// Может ли шашка продолжить поедать шашки
bool check_current_hit_checker(Desk *desk, Coordinate &enemy_checker,
									Coordinate &matrix_c)
{
	Coordinate coordinate_n;
	if (matrix_c.y < 6)
	{
		coordinate_n.y = matrix_c.y + 2;
	}
	if (matrix_c.x < 6)
	{
		coordinate_n.x = matrix_c.x + 2;
	}
	if (hit_checker(desk, matrix_c, coordinate_n, enemy_checker))
	{
		return true;
	}
	if (matrix_c.y > 1)
	{
		coordinate_n.y = matrix_c.y - 2;
	}				
	if (hit_checker(desk, matrix_c, coordinate_n, enemy_checker))
	{
		return true;
	}
	if (matrix_c.x > 1)
	{
		coordinate_n.x = matrix_c.x - 2;
	}
	if (matrix_c.y < 6)
	{
		coordinate_n.y = matrix_c.y + 2;	
	}
	if (hit_checker(desk, matrix_c, coordinate_n, enemy_checker))
	{
		return true;
	}
	if (matrix_c.y > 1)
	{
		coordinate_n.y = matrix_c.y - 2;
	}
	if (matrix_c.x > 1)
	{
		coordinate_n.x = matrix_c.x - 2;
	}
	if (hit_checker(desk, matrix_c, coordinate_n, enemy_checker))
	{
		return true;
	}
	return false;
}

// Проверка, может ли шашка не пойти, а съесть фигуру
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
				if (check_current_hit_checker(desk, enemy_checker, coordinate_c))
				{
					return true;
				}
			}
		}
	}
	return false;
}

// Шашка ходит
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

// Правила игры
bool rules(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n,
			Figure_Color &color_passage)
{
	Coordinate enemy_checker;
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
		if (step_checker(desk, matrix_c, matrix_n, next_line, color_passage))
		{
			// Может ли другая шашка ударить
			if (check_all_hit_checker(desk, color_passage, enemy_checker))
			{
				return false;
			}
			// // Может ли дамка ударить
			if (check_all_hit_king(desk, color_passage, enemy_checker))
			{
				return false;
			}
			// Действие в массиве
			func_in_hit_n_step(desk, matrix_c, matrix_n);

			// Проверка на последнюю горизонталь
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

			// Проверяем может ли превращённая шашка, которая только что съела 
			//вражескую фигуру продолжить есть фигуры
			if (check_current_hit_king(desk, enemy_checker, matrix_n) &&
				(*desk)[matrix_n.y][matrix_n.x].figure_type == King)
			{
				std::cout << "Введите следующую позицию дамки\nПример(d8g5): ";
				std::string step;
				check_input(step);
				// Правильность хода
				while (move_checkers(desk, step, color_passage) != true)
				{
					std::cout << "Неправильный ход!\n";
					check_input(step);
				}
			}
			// Может ли данная шашка съесть ещё
			if (check_current_hit_checker(desk, enemy_checker, matrix_n))
			{
				std::cout << "Введите следующую позицию шашки\nПример(d6f4): ";
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
	if ((*desk)[matrix_c.y][matrix_c.x].figure_type == King &&
		(*desk)[matrix_n.y][matrix_n.x].figure_type == Empty &&
		(*desk)[matrix_c.y][matrix_c.x].figure_color == color_passage)
	{
		return king(desk, matrix_c, matrix_n, enemy_checker, color_passage);
	}
	return false;
}