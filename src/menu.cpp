#include "../include/menu.h"

void print_line(std::string &line, std::string &left_corner, 
					std::string &right_corner)
{
	std::cout << left_corner;
	for (int i = 0; i < 23; ++i)
	{
		std::cout << line;
	}
	std::cout << right_corner << '\n';
}

void menu()
{
	// Очищаем терминал
	system("clear");

	std::string line              = "\u2500";
	std::string left_corner       = "\u256D";
	std::string right_corner      = "\u256E";

	// Рисуем верхушку меню
	print_line(line, left_corner, right_corner);


	std::string vertical_line     = "\u2502";


	// Заголовок
	std::cout << vertical_line << "   ⛂ Русские Шашки ⛂   " << vertical_line << '\n';


	std::string begin_bottom_line = "\u251C";
	std::string end_bottom_line   = "\u2524";


	// Отделяющую линию заголовка от меню
	print_line(line, begin_bottom_line, end_bottom_line);

	std::cout << vertical_line << " 1. Начать игру        " << vertical_line << '\n';
	std::cout << vertical_line << " 2. Настроить терминал " << vertical_line << '\n'; 
	std::cout << vertical_line << " 3. Выбрать тему       " << vertical_line << '\n';
	std::cout << vertical_line << " 4. Режим редактора    " << vertical_line << '\n';
	std::cout << vertical_line << " 5. Выйти из игры      " << vertical_line << '\n';
	
	left_corner = "\u2570";
	right_corner = "\u256F";

	print_line(line, left_corner, right_corner);

	options();
}