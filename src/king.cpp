#include "../include/king.h"

// Ходит дамка
bool step_king(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n)
{
	// Клетка дамки
	int y_c = matrix_c.y;
	int x_c = matrix_c.x;

	// Следующая клетка дамки
	int y_n = matrix_n.y;
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
				// Если следующая клетка пуста, то пропускаем её
				if ((*desk)[y_c + 1][x_c + 1].figure_type == Empty)
				{
					++y_c;
					++x_c;
				}
				// Если клетка занята
				else
				{
					return false;
				}
			}
			// Влево
			else
			{
				// Если следующая клетка пуста, то пропускаем её
				if ((*desk)[y_c + 1][x_c - 1].figure_type == Empty)
				{
					++y_c;
					--x_c;
				}
				// Если клетка занята
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
				// Если следующая клетка пуста, то пропускаем её
				if ((*desk)[y_c - 1][x_c + 1].figure_type == Empty)
				{
					--y_c;
					++x_c;
				}
				// Если клетка занята
				else
				{
					return false;
				}
			}
			// Влево
			else
			{
				// Если следующая клетка пуста, то пропускаем её
				if ((*desk)[y_c - 1][x_c - 1].figure_type == Empty)
				{
					--y_c;
					--x_c;
				}
				// Если клетка занята
				else
				{
					return false;
				}
			}
		}
	}
	return true;
}

// Дамка атакует
bool hit_king(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n, 
	Coordinate &enemy_checker)
{
	// Количество вражеских фигур на пути
	int count = 0;

	// Клетка дамки
	int y_c = matrix_c.y;
	int x_c = matrix_c.x;

	// Следующая клетка дамки
	int y_n = matrix_n.y;
	int x_n = matrix_n.x;

	// Ходим только по диагоналям y_c = x_c && y_n = x_n, поэтому x не проверяем
	while (y_c != y_n)
	{
		// Четыре направления
		// Вверх
		if (matrix_n.y > matrix_c.y)
		{
			// Вправо
			if (matrix_n.x > matrix_c.x)
			{
				// Если следующая клетка пуста, то пропускаем её
				if ((*desk)[y_c + 1][x_c + 1].figure_type == Empty)
				{
					++y_c;
					++x_c;
				}
				// Если клетка занята
				else
				{
					// Увеличиваем координаты
					++y_c;
					++x_c;

					// Запоминаем координаты вражеской фигуры
					enemy_checker.y = y_c;
					enemy_checker.x = x_c;

					// Две подряд фигуры не могут стоять на пути
					++count;
				}
			}
			// Влево
			else
			{
				// Если следующая клетка пуста, то пропускаем её
				if ((*desk)[y_c + 1][x_c - 1].figure_type == Empty)
				{
					++y_c;
					--x_c;
				}
				// Если клетка занята
				else
				{
					// Увеличиваем координаты
					++y_c;
					--x_c;

					// Запоминаем координаты вражеской фигуры
					enemy_checker.y = y_c;
					enemy_checker.x = x_c;

					// Две подряд фигуры не могут стоять на пути
					++count;
				}
			}
		}
		// Вниз
		else
		{
			// Вправо
			if (matrix_n.x > matrix_c.x)
			{
				// Если следующая клетка пуста, то пропускаем её
				if ((*desk)[y_c - 1][x_c + 1].figure_type == Empty)
				{
					--y_c;
					++x_c;
				}
				// Если клетка занята
				else
				{
					// Увеличиваем координаты
					--y_c;
					++x_c;

					// Запоминаем координаты вражеской фигуры
					enemy_checker.y = y_c;
					enemy_checker.x = x_c;

					// Две подряд фигуры не могут стоять на пути
					++count;
				}
			}
			// Влево
			else
			{
				// Если следующая клетка пуста, то пропускаем её
				if ((*desk)[y_c - 1][x_c - 1].figure_type == Empty)
				{
					--y_c;
					--x_c;
				}
				// Если клетка занята
				else
				{
					// Увеличиваем координаты
					--y_c;
					--x_c;

					// Запоминаем координаты вражеской фигуры
					enemy_checker.y = y_c;
					enemy_checker.x = x_c;

					// Две подряд фигуры не могут стоять на пути
					++count;
				}
			}
		}
	}

	// Если количество фигур на пути дамки одно
	if (count == 1)
	{
		// Проверяем, может ли она напасть на эту фигуру
		return if_in_hit_checker_n_king(desk, matrix_c, matrix_n, enemy_checker);
	}
	return false;
}

// Может ли дамка ударить
bool check_current_hit_king(Desk *desk, Coordinate &enemy_checker,
														Coordinate &matrix_c)
{
	// Координаты для следующей клетки дамки
	Coordinate inner;

	// Четыре направления
	// Вверх влево
	inner.y = matrix_c.y + 1;
	inner.x = matrix_c.x - 1;

	// Проверяем, что дамка не стоит на краю доски
	while (inner.y < 7 && inner.x > 0)
	{
		// Если на следующей клетке находим какую-то фигуру
		if ((*desk)[inner.y][inner.x].figure_type != Empty)
		{
			// А следующая клетка за ней пустая
			if ((*desk)[inner.y + 1][inner.x - 1].figure_type == Empty)
			{
				// Запоминаем пустую клетку
				++inner.y;
				--inner.x;
				break;
			}
		}
		// Идём дальше, пока не дойдём до края доски
		++inner.y;
		--inner.x;
	}
	// Пробуем ударить
	if (hit_king(desk, matrix_c, inner, enemy_checker))
	{
		return true;
	}

	// Вниз вправо
	inner.y = matrix_c.y - 1;
	inner.x = matrix_c.x + 1;

	// Проверяем, что дамка не стоит на краю доски
	while (inner.x < 7 && inner.y > 0)
	{
		// Если на следующей клетке находим какую-то фигуру
		if ((*desk)[inner.y][inner.x].figure_type != Empty)
		{
			// А следующая клетка за ней пустая
			if ((*desk)[inner.y - 1][inner.x + 1].figure_type == Empty)
			{
				// Запоминаем пустую клетку
				--inner.y;
				++inner.x;
				break;
			}
		}
		// Идём дальше, пока не дойдём до края доски
		--inner.y;
		++inner.x;
	}
	// Пробуем ударить
	if (hit_king(desk, matrix_c, inner, enemy_checker))
	{
		return true;
	}

	// Вправо вверх
	inner.y = matrix_c.y + 1;
	inner.x = matrix_c.x + 1;

	// Проверяем, что дамка не стоит на краю доски
	while (inner.y < 7 && inner.x < 7)
	{
		// Если на следующей клетке находим какую-то фигуру
		if ((*desk)[inner.y][inner.x].figure_type != Empty)
		{
			// А следующая клетка за ней пустая
			if ((*desk)[inner.y + 1][inner.x + 1].figure_type == Empty)
			{
				// Запоминаем пустую клетку
				++inner.y;
				++inner.x;
				break;
			}
		}
		// Идём дальше, пока не дойдём до края доски
		++inner.y;
		++inner.x;
	}
	// Пробуем ударить
	if (hit_king(desk, matrix_c, inner, enemy_checker))
	{
		return true;
	}

	// Вниз влево
	inner.y = matrix_c.y - 1;
	inner.x = matrix_c.x - 1;

	// Проверяем, что дамка не стоит на краю доски
	while (inner.y > 0 && inner.x > 0)
	{
		// Если на следующей клетке находим какую-то фигуру
		if ((*desk)[inner.y][inner.x].figure_type != Empty)
		{
			// А следующая клетка за ней пустая
			if ((*desk)[inner.y - 1][inner.x - 1].figure_type == Empty)
			{
				// Запоминаем пустую клетку
				--inner.y;
				--inner.x;
				break;
			}
		}
		// Идём дальше, пока не дойдём до края доски
		--inner.y;
		--inner.x;
	}
	// Пробуем ударить
	if (hit_king(desk, matrix_c, inner, enemy_checker))
	{
		return true;
	}
	return false;
}

// Может ли какая-либо дамка ударить
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
			// Если цвет шашки совпадает с цветом хода
			if ((*desk)[y][x].figure_type == King &&
				(*desk)[y][x].figure_color == color_passage)
			{
				// Берём координаты дамки
				coordinate_c.x = x;
				coordinate_c.y = y;

				// Проверяем, может ли она ударить
				if (check_current_hit_king(desk, enemy_checker, coordinate_c))
				{
					return true;
				}
			}
		}
	}
	return false;
}

// Король
bool king(Desk *desk, std::string &step, Coordinate &matrix_c, Coordinate &matrix_n, 
	Coordinate &enemy_checker, Figure_Color &color_passage, bool &players_draw,
	Desk *copy_desk, Figure_Color &copy_color_passage, std::fstream &save_moves)
{
	// Ходим только по диагоналям. Если модуль |y следующий - y текущий| == 
	// == |x следующий - x текущий| 
	if (abs(matrix_n.y - matrix_c.y) == abs(matrix_n.x - matrix_c.x))
	{
		// Шаг:
		if (step_king(desk, matrix_c, matrix_n))
		{
			// Может ли какая-либо шашка ударить
			if (check_all_hit_checker(desk, color_passage, enemy_checker))
			{
				return false;
			}
			// Может ли какая-либо дамка ударить
			if (check_all_hit_king(desk, color_passage, enemy_checker))
			{
				return false;
			}

			// Если нет, то шагаем дамкой
			func_in_hit_n_step(desk, matrix_c, matrix_n);
			return true;
		}

		// Удар:
		if (hit_king(desk, matrix_c, matrix_n, enemy_checker))
		{
			// Перескакиваем фигуру
			func_in_hit_n_step(desk, matrix_c, matrix_n);

			// Удаляем вражескую фигуру
			clear_element((*desk)[enemy_checker.y][enemy_checker.x]);

			// Может ли данная дамка съесть ещё
			if (check_current_hit_king(desk, enemy_checker, matrix_n))
			{
				std::cout << "Введите следующую позицию дамки\nПример(e1b4): ";
				std::string local_step;

				// Игрок ходит
				do
				{
					// Проверка на ввод
					check_input(local_step, players_draw, desk, color_passage, copy_desk,
									copy_color_passage, save_moves);
				} while (move_checkers(desk, local_step, color_passage, players_draw, 
									copy_desk, copy_color_passage, save_moves) != true
				 							&& step != "сдаюсь" && step != "выйти");
			
				// Если открыт
				if(save_moves.is_open() && local_step != "выйти" &&
															local_step != "сдаюсь")
				{
					step[2] = local_step[2];
					step[3] = local_step[3];
				}
			}
			return true;
		}
	}
	return false;
}