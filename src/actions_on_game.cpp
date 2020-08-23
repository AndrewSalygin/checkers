#include "../include/actions_on_game.h"

// Проверка количества шашек на доске
bool quantity_checkers(Desk *desk, Figure_Color &color_passage, Desk *copy_desk, 
							Figure_Color &copy_color_passage)
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
		std::cout << "\nВторой игрок выиграл!";
		question_restart_game(desk, color_passage, copy_desk, copy_color_passage);
	}
	if (count_black == 0)
	{
		std::cout << "\nПерввый игрок выиграл!";
		question_restart_game(desk, color_passage, copy_desk, copy_color_passage);
	} 
	return true;
}

// Ничья
void draw(Desk *desk, Desk *copy_desk, Figure_Color &color_passage,
			Figure_Color &copy_color_passage, const std::string &step,
			bool &players_draw)
{
	if (step == "ничья")
	{
		// Да или нет
		std::string players_draw_str;

		do
		{
			std::cout << "\nСогласен ли второй игрок? (д/н)\n";
			std::cin >> players_draw_str;
		} while (players_draw_str != "д" && players_draw_str != "н");

		if (players_draw_str == "д")
		{
			// Делаем ничью
			players_draw = true;

			std::cout << "\nОбъявляется ничья!";

			// Спрашиваем о рестарте игры
			question_restart_game(desk, color_passage, copy_desk, copy_color_passage);
		}
		else
		{
			std::cout << "Следующий ход: ";
		}
	}
}