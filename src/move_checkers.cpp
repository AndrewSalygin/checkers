#include "../include/move_checkers.h"

// Движение фигур
bool move_checkers(Desk *desk, std::string &step, Figure_Color &color_passage,
					bool &player_draw, Desk *copy_desk,
					Figure_Color &copy_color_passage, std::fstream &save_moves)
{
	// Координаты выбранной фигуры
	Coordinate position_c;
	Coordinate position_n;

	position_c.y = (int)step[1] - 49;
	position_c.x = (int)step[0] - 97;

	position_n.y = (int)step[3] - 49;
	position_n.x = (int)step[2] - 97;

	// Проверяем возможность такого хода
	if (rules(desk, step, position_c, position_n, color_passage, copy_desk,
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