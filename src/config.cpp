#include "../include/config.h"

// Чтение конфига
void read_config()
{
	// Делаем массив из глобальных цветов
	std::array<std::string, 8> color_scheme = {g_number_color, g_un_number_color, 
		  g_letter_color, g_un_letter_color, g_white_checker, g_black_checker,
		  g_white_cell, g_black_cell};

    // Файл
  	std::fstream config;

  	// Открываем конфиг
   	config.open("config", std::ios::in);

   	// Если он открыт
	if (config.is_open())
	{
		// Линия в файле
		std::string line;
		int i = 0;

		// Получаем линии
		while (getline(config, line)) 
		{
			color_scheme[i] = line;
			++i;
		}

		// Закрываем файл
		config.close();
	}

	// Меняем цвета на те, которые были установлены игроком
	g_number_color = color_scheme[0];
	g_un_number_color = color_scheme[1];
	g_letter_color = color_scheme[2];
	g_un_letter_color = color_scheme[3];
	g_white_checker = color_scheme[4];
	g_black_checker = color_scheme[5];
	g_white_cell = color_scheme[6];
	g_black_cell = color_scheme[7];
}

// Сохраняем конфиг
void save_config()
{
	// Файл
	std::fstream config;

	// Открываем
	config.open("config", std::ios::out);

	// Если открыт
	if(config.is_open())
	{
		// Записываем в файл
	  	config << g_number_color << '\n' << g_un_number_color << '\n' << 
	  	g_letter_color << '\n' << g_un_letter_color << '\n' << 
	  	g_white_checker << '\n' << g_black_checker << '\n' << g_white_cell <<
	  	'\n' << g_black_cell;

	  	// Закрываем файл
	  	config.close();
	}
}