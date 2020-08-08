#include "../include/begin_game.h"

void begin_game()
{
	// Подготавливаем доску для игры
	desk desk = init_desk();

	// Ход начинается с black, т.к print_desk() поменяет его на white
	Figure_Color color_passage = Black;
	// Рисуем начальную доску
	// print_desk(desk);
}
 