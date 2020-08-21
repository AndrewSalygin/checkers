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

// Шашка атакует
bool hit_checker(Desk *desk, Coordinate matrix_c, Coordinate matrix_n,
													Coordinate &enemy_checker)
{
	// Четыре направления

	// Вверх
	if (matrix_n.y > matrix_c.y)
	{
		enemy_checker.y = matrix_n.y - 1;
	}

	// Вниз
	else
	{
		enemy_checker.y = matrix_n.y + 1;
	}

	// Вправо
	if (matrix_n.x > matrix_c.x)
	{
		enemy_checker.x = matrix_n.x - 1;
	}

	// Влево
	else
	{
		enemy_checker.x = matrix_n.x + 1;
	}

	// Вверх вправо
	if (matrix_n.y == matrix_c.y + 2 && matrix_n.x == matrix_c.x + 2)
	{
		if (if_in_hit_checker_n_king(desk, matrix_c, matrix_n, enemy_checker))
			return true;
	}

	// Вверх влево
	if (matrix_n.y == matrix_c.y + 2 && matrix_n.x == matrix_c.x - 2)
	{
		if (if_in_hit_checker_n_king(desk, matrix_c, matrix_n, enemy_checker))
			return true;
	}

	// Вниз вправо
	if (matrix_n.y == matrix_c.y - 2 && matrix_n.x == matrix_c.x + 2)
	{
		if (if_in_hit_checker_n_king(desk, matrix_c, matrix_n, enemy_checker))
			return true;
	}

	// Вниз влево
	if (matrix_n.y == matrix_c.y - 2 && matrix_n.x == matrix_c.x - 2)
	{
		if (if_in_hit_checker_n_king(desk, matrix_c, matrix_n, enemy_checker))
			return true;
	}
	return false;
}

// Может ли шашка ударить
bool check_current_hit_checker(Desk *desk, Coordinate &enemy_checker,
														Coordinate &matrix_c)
{
	// Координаты для следующей клетки шашки
	Coordinate coordinate_n;

	// Мы имеем 4 направления, по которому шашка может бить

	// Вверх вправо
	// Проверяем, не стоит ли шашка на краю, иначе будет выход за рамки массива
	if (matrix_c.y < 6)
	{
		coordinate_n.y = matrix_c.y + 2;
	}
	if (matrix_c.x < 6)
	{
		coordinate_n.x = matrix_c.x + 2;
	}
	// Пытаемся ударить
	if (hit_checker(desk, matrix_c, coordinate_n, enemy_checker))
	{
		return true;
	}

	// Вниз вправо
	if (matrix_c.y > 1)
	{
		coordinate_n.y = matrix_c.y - 2;
	}				
	if (hit_checker(desk, matrix_c, coordinate_n, enemy_checker))
	{
		return true;
	}

	// Вверх влево
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

	// Вниз влево
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

// Может ли какая-либо шашка ударить
bool check_all_hit_checker(Desk *desk, Figure_Color &color_passage,
													Coordinate &enemy_checker)
{
	// Координаты для проверки каждой шашки
	Coordinate coordinate_c;
	Coordinate coordinate_n;

	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			// Если цвет шашки совпадает с цветом хода
			if ((*desk)[y][x].figure_type == Checker &&
				(*desk)[y][x].figure_color == color_passage)
			{
				// Берём координаты шашки
				coordinate_c.x = x;
				coordinate_c.y = y;

				// Проверяем, может ли она ударить
				if (check_current_hit_checker(desk, enemy_checker, coordinate_c))
				{
					return true;
				}
			}
		}
	}
	return false;
}

// Король
bool king(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n, 
	Coordinate &enemy_checker, Figure_Color &color_passage, bool &players_draw)
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
				std::string step;

				// Игрок ходит
				do
				{
					// Проверка на ввод
					check_input(step, players_draw, desk, color_passage);
				} while (move_checkers(desk, step, color_passage, players_draw) != true
				 							&& step != "сдаюсь" && step != "выйти");
			}
			return true;
		}
	}
	return false;
}

// При достижении последней горизонтали происходит превращение шашки в дамку
void checker_to_king(Desk *desk, Coordinate &matrix_c)
{
	// Если белая, то восьмая горизонталь
	if (matrix_c.y == 7 && (*desk)[matrix_c.y][matrix_c.x].figure_color == White)
	{
		(*desk)[matrix_c.y][matrix_c.x].figure_type = King;
	}

	// Если чёрная, то первая горизонталь
	if (matrix_c.y == 0 && (*desk)[matrix_c.y][matrix_c.x].figure_color == Black)
	{
		(*desk)[matrix_c.y][matrix_c.x].figure_type = King;
	}
}

// Шашка ходит
bool step_checker(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n,
																int &next_line)
{
	// Правила хода шашки
	if (matrix_n.y == next_line && 
		(matrix_n.x == matrix_c.x + 1 || matrix_n.x == matrix_c.x - 1) &&
		(*desk)[matrix_n.y][matrix_n.x].figure_type == Empty)
	{
		return true;
	}
	return false;
}

bool checker(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n, 
	Coordinate &enemy_checker, Figure_Color &color_passage, bool &players_draw)
{
	// Следующая линия, на которую ступит шашка
	int next_line;

	// Если шашка белая
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

		// Если нет, то шагаем шашкой
		func_in_hit_n_step(desk, matrix_c, matrix_n);

		// Проверка на последнюю горизонталь
		checker_to_king(desk, matrix_n);

		return true;
	}

	// Удар:
	if (hit_checker(desk, matrix_c, matrix_n, enemy_checker))
	{
		// Перескакиваем шашку
		func_in_hit_n_step(desk, matrix_c, matrix_n);

		// Удаляем вражескую шашку
		clear_element((*desk)[enemy_checker.y][enemy_checker.x]);

		// Проверка на последнюю горизонталь
		checker_to_king(desk, matrix_n);

		// Если верхняя функция сработала
		if (check_current_hit_king(desk, enemy_checker, matrix_n) &&
			(*desk)[matrix_n.y][matrix_n.x].figure_type == King)
		{
			std::cout << "Введите следующую позицию дамки\nПример(d8g5): ";
			std::string step;

			// Игрок ходит
			do
			{
				// Проверка на ввод
				check_input(step, players_draw, desk, color_passage);
			} while (move_checkers(desk, step, color_passage, players_draw) != true
			 							&& step != "сдаюсь" && step != "выйти");
		}

		// Может ли данная шашка съесть ещё
		if (check_current_hit_checker(desk, enemy_checker, matrix_n))
		{
			std::cout << "Введите следующую позицию шашки\nПример(d6f4): ";
			std::string step;

			// Игрок ходит
			do
			{
				// Проверка на ввод
				check_input(step, players_draw, desk, color_passage);
			} while (move_checkers(desk, step, color_passage, players_draw) != true
			 							&& step != "сдаюсь" && step != "выйти");
		}
		return true;
	}
	return false;
}

// Правила игры
bool rules(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n,
								Figure_Color &color_passage, bool &players_draw)
{
	// Координаты вражеской шашки
	Coordinate enemy_checker;

	// Если выбрана шашка
	if ((*desk)[matrix_c.y][matrix_c.x].figure_type == Checker &&
		(*desk)[matrix_c.y][matrix_c.x].figure_color == color_passage)
	{
		return checker(desk, matrix_c, matrix_n, enemy_checker, color_passage, 
			players_draw);
	}

	// Если выбрана дамка
	if ((*desk)[matrix_c.y][matrix_c.x].figure_type == King &&
		(*desk)[matrix_c.y][matrix_c.x].figure_color == color_passage)
	{
		return king(desk, matrix_c, matrix_n, enemy_checker, color_passage, 
			players_draw);
	}
	return false;
}