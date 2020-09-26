#include "../include/move_checkers.h"

// Движение фигур
bool move_checkers(Desk *desk, std::string &step, Figure_Color &color_passage,
					bool &player_draw, Desk *copy_desk,
					Figure_Color &copy_color_passage, std::fstream &save_moves)
{
	// Координаты выбранной фигуры
	Coordinate matrix_c;
	Coordinate matrix_n;

	matrix_c.y = (int)step[1] - 49;
	matrix_c.x = (int)step[0] - 97;

	matrix_n.y = (int)step[3] - 49;
	matrix_n.x = (int)step[2] - 97;

	// Проверяем возможность такого хода
	if (rules(desk, step, matrix_c, matrix_n, color_passage, copy_desk,
				copy_color_passage, player_draw, save_moves))
	{
		return true;
	}
	else
	{
		std::cout << "\nХод невозможен!\nВведите другой:\n";
	}
	return false;
}