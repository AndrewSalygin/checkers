#ifndef ACTIONS_ON_GAME_H
#define ACTIONS_ON_GAME_H

#include "restart_game.h"

bool quantity_checkers(Desk *desk, Figure_Color &color_passage, Desk *copy_desk, 
							Figure_Color &copy_color_passage, std::fstream &save_moves);
void draw(Desk *desk, Desk *copy_desk, Figure_Color &color_passage,
			Figure_Color &copy_color_passage, const std::string &step,
			bool &players_draw, std::fstream &save_moves);

#endif