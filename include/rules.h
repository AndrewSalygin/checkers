#ifndef RULES_H
#define RULES_H
#include "data.h"
#include "actions_on_array.h"

bool hit_checker(Desk *desk, int &next_line, int &next_column, int &hit_column,
		int &hit_line);
bool step_checker(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n,
		int &next_line);
bool rules(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n, 
	Figure_Color color_passage);
#endif