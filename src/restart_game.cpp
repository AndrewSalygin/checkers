#include "../include/restart_game.h"

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