#ifndef RULES_H
#define RULES_H

#include "actions_on_array.h"
#include "input.h"

bool rules(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n, 
								Figure_Color &color_passage, bool &player_draw);

#endif