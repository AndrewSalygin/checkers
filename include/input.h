#ifndef INPUT_H
#define INPUT_H
#include <regex>
#include "print_desk.h"
#include "move_checkers.h"

void check_input(std::string &step);
void game(Desk *desk, Figure_Color &color_passage);

#endif