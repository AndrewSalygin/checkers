#include "../include/actions_on_array.h"

// Очищаем элемент массива, где раньше находилась фигура
void clear_element(Figure &elem)
{
	elem.figure_type  = Empty;
	elem.figure_color = None;
}

// Меняем фигуры местами
void swap_checkers(Desk *desk, const Coordinate &position_c, const Coordinate &position_n)
{
	(*desk)[position_n.y][position_n.x].figure_type  =
		(*desk)[position_c.y][position_c.x].figure_type;
		
	(*desk)[position_n.y][position_n.x].figure_color =
		(*desk)[position_c.y][position_c.x].figure_color;
}