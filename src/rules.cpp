#include "../include/rules.h"

// Правила игры
bool rules(Desk *desk, std::string &step, Coordinate &position_c, Coordinate &position_n,
				Figure_Color &color_passage, Desk *copy_desk, 
				Figure_Color &copy_color_passage, bool &players_draw,
				std::fstream &save_moves)
{
	// Координаты вражеской шашки
	Coordinate enemy_checker;

	// Если выбрана шашка
	if ((*desk)[position_c.y][position_c.x].figure_type == Checker &&
		(*desk)[position_c.y][position_c.x].figure_color == color_passage)
	{
		return checker(desk, step, position_c, position_n, enemy_checker, color_passage, 
			players_draw, copy_desk, copy_color_passage, save_moves);
	}

	// Если выбрана дамка
	if ((*desk)[position_c.y][position_c.x].figure_type == King &&
		(*desk)[position_c.y][position_c.x].figure_color == color_passage)
	{
		return king(desk, step, position_c, position_n, enemy_checker, color_passage, 
			players_draw, copy_desk, copy_color_passage, save_moves);
	}
	return false;
}