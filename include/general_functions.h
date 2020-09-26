#ifndef GENERAL_FUNCTIONS_H
#define GENERAL_FUNCTIONS_H

#include "actions_on_array.h"

bool if_in_hit_checker_n_king(Desk *desk, Coordinate position_c,
								Coordinate position_n, Coordinate &enemy_checker);
void func_in_hit_n_step(Desk *desk, Coordinate &position_c, Coordinate &position_n);

#endif