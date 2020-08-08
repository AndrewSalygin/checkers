#include "../include/actions_on_array.h"

// Очищаем элемент массива, где раньше находилась фигура
void clear_element(Figure &elem)
{
	elem.figure_type  = Empty;
	elem.figure_color = None;
}

// Меняем фигуры местами
void swap_checkers(Desk *desk, Coordinate &matrix_c, Coordinate &matrix_n)
{
	(*desk)[matrix_n.y][matrix_n.x].figure_type  =
		(*desk)[matrix_c.y][matrix_c.x].figure_type;
		
	(*desk)[matrix_n.y][matrix_n.x].figure_color =
		(*desk)[matrix_c.y][matrix_c.x].figure_color;
}