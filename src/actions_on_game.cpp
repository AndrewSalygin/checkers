#include "../include/actions_on_game.h"

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