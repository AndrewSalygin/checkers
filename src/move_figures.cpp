#include "../include/actions_on_figures.h"

// Движение фигур
bool move_figures(std::string &step)
{
	Coordinate matrix_c;
	Coordinate matrix_n;

	matrix_c.y = (int)step[1] - 49;
	matrix_c.x = (int)step[0] - 97;

	matrix_n.y = (int)step[3] - 49;
	matrix_n.x = (int)step[2] - 97;

	if (rules(matrix_c, matrix_n))
	{
		swap_figures(matrix_c, matrix_n);
		clear_element(g_desk[matrix_c.y][matrix_c.x]);
		return true;
	}
	return false;
}