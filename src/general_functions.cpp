#include "../include/general_functions.h"

// Функция удара для дамок и шашек
bool if_in_hit_checker_n_king(Desk *desk, Coordinate position_c, 
								Coordinate position_n, Coordinate &enemy_checker)
{
	if ((*desk)[enemy_checker.y][enemy_checker.x].figure_type != Empty &&
		(*desk)[enemy_checker.y][enemy_checker.x].figure_color != 
		(*desk)[position_c.y][position_c.x].figure_color && 
		(*desk)[position_n.y][position_n.x].figure_type == Empty)
	{
		return true;
	}
	return false;
}

// Операции в массиве
void func_in_hit_n_step(Desk *desk, Coordinate &position_c, Coordinate &position_n)
{
	// Меняем элементы в массиве друг с другом 
	swap_checkers(desk, position_c, position_n);

	// Удаляем элемент, который мы поменяли
	clear_element((*desk)[position_c.y][position_c.x]);
}