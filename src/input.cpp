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

bool question_restart_game(Desk *desk)
{
	std::cout << "\nХотите сыграть ещё? (да/нет): ";
	std::string answer;
	Figure_Color color_passage;
	do
	{
		std::cin >> answer;
	} while (answer != "да" && answer != "нет");
	if (answer == "да")
	{
		restart_game(desk, color_passage);
		return true;
	}
	if (answer == "нет")
	{
		system("clear");
		exit(0);
	}
	return false;
}

bool deadlock(Desk *desk)
{
	int x;
	Figure_Color local_color;
	int count = 0;

	// Если такая ситуация сложилась, то присваиваем победу чёрным
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

	// Единственный случай, когда белые не могут сделать ход
	if (count == 24)
	{
		std::cout << "\nЧёрные выиграли!";
		question_restart_game(desk);
	}
	return false;
}

// Проверка количества шашек на доске
bool quantity_checkers(Desk *desk, Figure_Color &color_passage)
{
	int count_white = 0;
	int count_black = 0;

	// Считаем количество шашек
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

	// Перезапускаем игру, если требуется
	if (count_white == 0)
	{
		std::cout << "\nЧёрные выиграли!";
		question_restart_game(desk);
	}
	if (count_black == 0)
	{
		std::cout << "\nБелые выиграли!";
		question_restart_game(desk);
	} 
	return true;
}

// Ключевые слова для действий над игрой
bool exit_game(const std::string &step)
{
	if (step == "выйти")
	{
		return true;
	}
	if (step == "сдаюсь")
	{
		return true;
	}
	if (step == "ничья")
	{
		return true;
	}
	return false;
}

// Ничья
void draw(Desk *desk, Figure_Color &color_passage, const std::string &step,
			bool &players_draw)
{
	if (step == "ничья")
	{
		// Да или нет
		std::string players_draw_str;

		do
		{
			std::cout << "\nСогласен ли второй игрок? (да/нет)\n";
			std::cin >> players_draw_str;
		} while (players_draw_str != "да" && players_draw_str != "нет");

		if (players_draw_str == "да")
		{
			// Делаем ничью
			players_draw = true;

			std::cout << "\nОбъявляется ничья!";

			// Спрашиваем о рестарте игры
			question_restart_game(desk);
		}
		else
		{
			std::cout << "Следующий ход: ";
		}
	}
}

// Проверка ввода с помощью регулярных выражений
void check_input(std::string &step, bool &players_draw, Desk *desk, 
					Figure_Color &color_passage)
{
	do
	{
		// Ход
		std::cin >> step;

		// Выходим из игры
		if (exit_game(step))
		{
			// Проверка ничьи
			draw(desk, color_passage, step, players_draw);
			break;
		}

		// Если не ключевое слово
		std::cout << "\nХод невозможен!\nВведите другой:\n";

	} while (!std::regex_match(step, std::regex("[a-h][1-8][a-h][1-8]")) ||
			// Идентичность клетки
			(step[0] == step[2] && step[1] == step[3])); 
}

// Начинаем игру
void game(Desk *desk, Figure_Color &color_passage)
{
	// Отслеживание ничьи
	bool players_draw = false;

	// Ввод игрока
	std::string step;

	// Вывод текста для игроков
	do
	{
		// Ходят белые
		if (color_passage == White)
		{
			std::cout << "\nХод первого игрока\nПример(e3f4): ";
		}

		// Ходят чёрные
		else
		{
			std::cout << "\nХод второго игрока\nПример(d6e5): ";
		}

		// Игрок ходит
		do
		{
			// Проверка на ввод
			check_input(step, players_draw, desk, color_passage);
		} while (move_checkers(desk, step, color_passage, players_draw) != true 
								&& step != "сдаюсь" && step != "выйти");
		
		// Отрисовываем доску заново
		print_desk(desk, color_passage);
	} while (quantity_checkers(desk, color_passage) && !deadlock(desk) &&
				step != "выйти" && step != "сдаюсь" && !players_draw);
	
	if (step == "выйти")
	{
		std::cout << '\n';
		system("clear");
		exit(0);
	}

	if (step == "сдаюсь")
	{
		if (color_passage == Black)
		{
			std::cout << '\n';
			std::cout << "Победили чёрные!\n";

			// Спрашиваем о рестарте игры
			question_restart_game(desk);
		}
		else
		{
			std::cout << '\n';
			std::cout << "Победили белые!\n";

			// Спрашиваем о рестарте игры
			question_restart_game(desk);
		}
	}
}