#include "../include/checker.h"

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
	Coordinate &enemy_checker, Figure_Color &color_passage, bool &players_draw,
	Desk *copy_desk, Figure_Color &copy_color_passage)
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
				check_input(step, players_draw, desk, color_passage, copy_desk,
								copy_color_passage); 
			} while (move_checkers(desk, step, color_passage, players_draw, 
								copy_desk, copy_color_passage) != true
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
				check_input(step, players_draw, desk, color_passage, copy_desk,
								copy_color_passage);
			} while (move_checkers(desk, step, color_passage, players_draw, 
								copy_desk, copy_color_passage) != true
			 							&& step != "сдаюсь" && step != "выйти");
		}
		return true;
	}
	return false;
}