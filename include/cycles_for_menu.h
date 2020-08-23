#ifndef CYCLES_FOR_MENU_H
#define CYCLES_FOR_MENU_H

#include "menu.h"

void cycle_color(Desk *desk, Figure_Color &color_passage, 
					std::string &inner_option, std::string &local_string,
					std::string &global_color, bool &text);
void cycle_answer(Desk *desk, Figure_Color &color_passage,
 					std::string &inner_option, std::string &local_string,
 					std::string &global_color, std::string &answer, bool &text);
void call_cycles(Desk *desk, Figure_Color &color_passage,
 					std::string &inner_option, std::string &local_string,
 					std::string &global_color, std::string &answer, bool &text);

#endif