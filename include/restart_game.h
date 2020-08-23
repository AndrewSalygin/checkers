#ifndef RESTART_GAME_H
#define RESTART_GAME_H

#include "init_desk.h"
#include "game.h"

bool question_restart_game(Desk *desk, Figure_Color &color_passage,
							Desk *copy_desk, Figure_Color &copy_color_passage);

#endif