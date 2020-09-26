#ifndef CHECKER_H
#define CHECKER_H

#include "rules.h"

bool check_all_hit_checker(Desk *desk, Figure_Color &color_passage,
													Coordinate &enemy_checker);
bool checker(Desk *desk, std::string &step, Coordinate &matrix_c, Coordinate &matrix_n, 
	Coordinate &enemy_checker, Figure_Color &color_passage, bool &players_draw,
	Desk *desk_copy, Figure_Color &copy_color_passage, std::fstream &save_moves);

#endif