#ifndef RULES_H
#define RULES_H

#include "input.h"
#include "general_functions.h"
#include "king.h"

bool rules(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n, 
			Figure_Color &color_passage, Desk *copy_desk, 
			Figure_Color &copy_color_passage, bool &player_draw);

#endif