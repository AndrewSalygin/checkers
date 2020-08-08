#include "../include/move_figures.h"

// Движение фигур
bool move_figures(Desk *desk, std::string &step, Figure_Color color_passage)
{
	Coordinate matrix_c;
	Coordinate matrix_n;

	matrix_c.y = (int)step[1] - 49;
	matrix_c.x = (int)step[0] - 97;

	matrix_n.y = (int)step[3] - 49;
	matrix_n.x = (int)step[2] - 97;

	if (rules(desk, matrix_c, matrix_n, color_passage))
	{
		swap_figures(desk, matrix_c, matrix_n);
		clear_element((*desk)[matrix_c.y][matrix_c.x]);
		return true;
	}
	return false;
}