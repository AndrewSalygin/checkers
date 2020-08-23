#ifndef KING_H
#define KING_H

#include "checker.h"

bool king(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n, 
	Coordinate &enemy_checker, Figure_Color &color_passage, bool &players_draw,
	Desk *copy_desk, Figure_Color &copy_color_passage);
bool check_all_hit_king(Desk *desk, Figure_Color &color_passage,
													Coordinate &enemy_checker);
bool check_current_hit_king(Desk *desk, Coordinate &enemy_checker,
														Coordinate &matrix_c);

#endif