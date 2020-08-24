#include "../include/rules.h"

// Правила игры
bool rules(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n,
				Figure_Color &color_passage, Desk *copy_desk, 
				Figure_Color &copy_color_passage, bool &players_draw,
				std::fstream &save_moves)
{
	// Координаты вражеской шашки
	Coordinate enemy_checker;

	// Если выбрана шашка
	if ((*desk)[matrix_c.y][matrix_c.x].figure_type == Checker &&
		(*desk)[matrix_c.y][matrix_c.x].figure_color == color_passage)
	{
		return checker(desk, matrix_c, matrix_n, enemy_checker, color_passage, 
			players_draw, copy_desk, copy_color_passage, save_moves);
	}

	// Если выбрана дамка
	if ((*desk)[matrix_c.y][matrix_c.x].figure_type == King &&
		(*desk)[matrix_c.y][matrix_c.x].figure_color == color_passage)
	{
		return king(desk, matrix_c, matrix_n, enemy_checker, color_passage, 
			players_draw, copy_desk, copy_color_passage, save_moves);
	}
	return false;
}