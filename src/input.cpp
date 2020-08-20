#include "../include/input.h"

void restart_game(Desk *desk, Figure_Color &color_passage)
{
	(*desk) = init_desk();

	// Ход начинается с black, т.к print_desk() поменяет его на white
	color_passage = Black;
	
	// Рисуем начальную доску
	print_desk(desk, color_passage);

	// Начинаем игру
	game(desk, color_passage);
}

bool deadlock(Desk *desk)
{
	int x;
	Figure_Color local_color;
	int count = 0;
	for (int y = 1; y < 7; ++y)
	{
		if (y < 4)
		{	
			local_color = White;
		}
		else
		{
			local_color = Black;
		}
		if (y % 2 == 0)
		{
			x = 0;
		}
		else
		{
			x = 1;
		}
		for (; x < 8; x += 2)
		{
			if (y == 3 && x == 5)
			{
				if ((*desk)[y][x].figure_color == Black)
				{
					++count;
				}
			}
			if (y == 4 && x == 2)
			{
				if ((*desk)[y][x].figure_color == White)
				{
					++count;
				}
			}
			if ((*desk)[y][x].figure_color == local_color)
			{
				++count;
			}
		}
	}
	if (count == 24)
	{
		std::cout << "\nЧёрные выиграли!\nХотите сыграть ещё? (да/нет): ";
		std::string answer;
		Figure_Color color_passage;
		do
		{
			std::cin >> answer;
		} while (answer != "да" && answer != "нет");
		if (answer == "да")
		{
			restart_game(desk, color_passage);
		}
		if (answer == "нет")
		{
			exit(0);
		}
		return true;
	}
	return false;
}

// Проверка количества шашек на доске
bool quantity_checkers(Desk *desk, Figure_Color &color_passage)
{
	int count_white = 0;
	int count_black = 0;
	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			if ((*desk)[y][x].figure_type == Checker || 
				(*desk)[y][x].figure_type == King)
			{
				if ((*desk)[y][x].figure_color == White)
				{
					++count_white;
				}
				else
				{
					++count_black;
				}
			}

		}
	}
	if (count_white == 0)
	{
		std::cout << "\nЧёрные выиграли!\nХотите сыграть ещё? (да/нет): ";
		std::string answer;
		do
		{
			std::cin >> answer;
		} while (answer != "да" && answer != "нет");
		if (answer == "да")
		{
			restart_game(desk, color_passage);
		}
		if (answer == "нет")
		{
			exit(0);
		}
		return false;
	}
	if (count_black == 0)
	{
		std::cout << "\nБелые выиграли!\nХотите сыграть ещё? (да/нет): ";
		std::string answer;
		do
		{
			std::cin >> answer;
		} while (answer != "да" && answer != "нет");
		if (answer == "да")
		{
			restart_game(desk, color_passage);
		}
		if (answer == "нет")
		{
			exit(0);
		}
		return false;
	} 
	return true;
}

// Проверка ввода с помощью регулярных выражений
void check_input(std::string &step, bool &players_draw, Desk *desk, 
					Figure_Color &color_passage)
{
	do
	{
		std::cin >> step;
		if (step == "выйти")
		{
			break;
		}
		if (step == "сдаюсь")
		{
			break;
		}
		if (step == "ничья")
		{
			std::string players_draw_str;
			do
			{
				std::cout << "\nСогласен ли второй игрок? (да/нет)\n";
				std::cin >> players_draw_str;
			} while (players_draw_str != "да" && players_draw_str != "нет");
				if (players_draw_str == "да")
				{
					players_draw = true;
					std::cout << "\nОбъявляется ничья!\nХотите сыграть ещё? (да/нет): ";
					std::string answer;
					do
					{
						std::cin >> answer;
					} while (answer != "да" && answer != "нет");
					if (answer == "да")
					{
						restart_game(desk, color_passage);
					}
					if (answer == "нет")
					{
						exit(0);
					}
				}
				else
				{
					players_draw = false;
					std::cout << "Следующий ход: ";
				}
		}
	} while (!std::regex_match(step, std::regex("[a-h][1-8][a-h][1-8]")) ||
			// Идентичность клетки
			(step[0] == step[2] && step[1] == step[3])); 
}

void game(Desk *desk, Figure_Color &color_passage)
{
	bool players_draw = false;
	std::string step;
	do
	{
		if (color_passage == White)
		{
			std::cout << "\nХод первого игрока\nПример(e3f4): ";
		}
		else
		{
			std::cout << "\nХод второго игрока\nПример(d6e5): ";
		}

		check_input(step, players_draw, desk, color_passage);
		if (step == "выйти")
		{
			break;
		}
		if (step == "сдаюсь")
		{
			break;
		}
		// Правильность хода
		while (move_checkers(desk, step, color_passage, players_draw) != true)
		{
			std::cout << "\nХод невозможен!\nВведите другой: ";
			check_input(step, players_draw, desk, color_passage);
		}
		// Отрисовываем доску заново
		print_desk(desk, color_passage);
	} while (quantity_checkers(desk, color_passage) && !deadlock(desk) &&
				step != "выйти" && step != "сдаюсь" && !players_draw);
	if (step == "сдаюсь")
	{
		if (color_passage == White)
		{
			std::cout << "Победили чёрные!\n";
		}
		else
		{
			std::cout << "Победили белые!\n";
		}
	}
}