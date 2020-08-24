#ifndef DEADLOCK_H
#define DEADLOCK_H

#include "restart_game.h"

bool deadlock(Desk *desk, Figure_Color &color_passage, Desk *copy_desk,
				Figure_Color &copy_color_passage, std::fstream &save_moves);

#endif