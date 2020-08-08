#ifndef RULES_H
#define RULES_H
#include <iostream>
#include "data.h"

bool step_checker(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n,
		int &next_line);
bool rules(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n, 
	Figure_Color color_passage);
#endif