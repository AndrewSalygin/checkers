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
void filling_array(Desk *desk, Figure_Color &color_passage, Coordinate &matrix_c,
					Figure_Type &type, Figure_Color &color, int &count,
					std::string &position);
void cycle_before_filling(Desk *desk, Figure_Color &color_passage, 
	Coordinate &matrix_c, Figure_Type &type, Figure_Color &color, int &count,
	std::string &position);

#endif