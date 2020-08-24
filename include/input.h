#ifndef INPUT_H
#define INPUT_H

#include <regex>
#include "print_desk.h"
#include "move_checkers.h"
#include "actions_on_game.h"

void check_input(std::string &step, bool &players_draw, Desk *desk, 
					Figure_Color &color_passage, Desk *copy_desk, 
					Figure_Color &copy_color_passage, std::fstream &save_moves);
#endif