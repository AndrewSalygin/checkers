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
void check_input(std::string &step)
{
	do
	{
		std::cin >> step;
	} while (!std::regex_match(step, std::regex("[a-h][1-8][a-h][1-8]")) ||
			// Идентичность клетки
			(step[0] == step[2] && step[1] == step[3])); 
}

void game(Desk *desk, Figure_Color &color_passage)
{
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

		check_input(step);

		// Правильность хода
		while (move_checkers(desk, step, color_passage) != true)
		{
			std::cout << "Неправильный ход!\n";
			check_input(step);
		}

		// Отрисовываем доску заново
		print_desk(desk, color_passage);
	} while (quantity_checkers(desk, color_passage));
}