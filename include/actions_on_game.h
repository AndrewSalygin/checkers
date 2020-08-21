#ifndef ACTIONS_ON_GAME_H
#define ACTIONS_ON_GAME_H

#include "restart_game.h"

bool quantity_checkers(Desk *desk, Figure_Color &color_passage);
bool exit_game(const std::string &step);
void draw(Desk *desk, Figure_Color &color_passage, const std::string &step,
			bool &players_draw);

#endif