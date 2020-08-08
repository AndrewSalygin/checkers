#include "../include/input.h"

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
			std::cout << "\nХод первого игрока: ";
		}
		else
		{
			std::cout << "\nХод второго игрока: ";
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
	} while (true);
}