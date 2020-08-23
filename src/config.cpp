#include "../include/config.h"
void read_config()
{
	std::array<std::string, 8> color_scheme = {g_number_color, g_un_number_color, 
		  g_letter_color, g_un_letter_color, g_white_checker, g_black_checker,
		  g_white_cell, g_black_cell};

  	std::fstream config;
   	config.open("../config", std::ios::in);
	if (config.is_open())
	{
		std::string tp;
		int i = 0;
		while (getline(config, tp)) 
		{
			color_scheme[i] = tp;
			++i;
		}
		config.close();
	}

	g_number_color = color_scheme[0];
	g_un_number_color = color_scheme[1];
	g_letter_color = color_scheme[2];
	g_un_letter_color = color_scheme[3];
	g_white_checker = color_scheme[4];
	g_black_checker = color_scheme[5];
	g_white_cell = color_scheme[6];
	g_black_cell = color_scheme[7];
}
void save_config()
{
	std::fstream config;
	config.open("../config", std::ios::out);
	if(config.is_open())
	{
	  config << g_number_color << '\n' << g_un_number_color << '\n' << 
	  g_letter_color << '\n' << g_un_letter_color << '\n' << 
	  g_white_checker << '\n' << g_black_checker << '\n' << g_white_cell <<
	  '\n' << g_black_cell;
	  config.close();
	}
}