#ifndef KING_H
#define KING_H

#include "checker.h"

bool king(Desk *desk, std::string &step, Coordinate &position_c, Coordinate &position_n, 
	Coordinate &enemy_checker, Figure_Color &color_passage, bool &players_draw,
	Desk *copy_desk, Figure_Color &copy_color_passage, std::fstream &save_moves);
bool check_all_hit_king(Desk *desk, Figure_Color &color_passage,
													Coordinate &enemy_checker);
bool check_current_hit_king(Desk *desk, Coordinate &enemy_checker,
														Coordinate &position_c);

#endif