#include "../include/restart_game.h"

void restart_game(Desk *desk, Figure_Color &color_passage, Desk *copy_desk, 
			Figure_Color &copy_color_passage)
{
	// Рисуем начальную доску
	print_desk(copy_desk, copy_color_passage);

	// Начинаем игру
	game(copy_desk, copy_color_passage);
}

bool question_restart_game(Desk *desk, Figure_Color &color_passage, Desk *copy_desk, 
			Figure_Color &copy_color_passage, std::fstream &save_moves)
{
	std::cout << "\nХотите сыграть ещё? (д/н): ";
	std::string answer;
	do
	{
		std::cin >> answer;
	} while (answer != "д" && answer != "н");
	if (answer == "д")
	{
		save_moves.close();
		restart_game(desk, color_passage, copy_desk, copy_color_passage);
		return true;
	}
	if (answer == "н")
	{
		save_moves.close();
		system("clear");
		menu();
	}
	return false;
}