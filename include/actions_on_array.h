#ifndef ACTIONS_ON_ARRAY
#define ACTIONS_ON_ARRAY

#include "data.h"

void clear_element(Figure &elem);
void swap_checkers(Desk *desk, const Coordinate &position_c, 
													const Coordinate &position_n);

#endif