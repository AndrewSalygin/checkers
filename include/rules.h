#ifndef RULES_H
#define RULES_H
#include "data.h"
#include "actions_on_array.h"
#include "input.h"

bool if_in_hit_checker(Desk *desk, Coordinate matrix_c, Coordinate matrix_n,
		Coordinate &enemy_checker);
void func_in_hit_n_step(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n);
bool hit_checker(Desk *desk, int &next_line, int &next_column, int &hit_column,
		int &hit_line);
bool step_checker(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n,
		int &next_line, Figure_Color &color_passage);
bool rules(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n, 
	Figure_Color &color_passage);
#endif