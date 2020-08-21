#include "../include/input.h"

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
