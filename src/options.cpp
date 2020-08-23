#include "../include/options.h"

void options()
{
	std::string option;
	do
	{
		std::cout << "\t    ";
		std::cin >> option;
	} while (option != "1" && option != "2" && option != "3" && option != "4" &&
				option != "5");

	if (option == "1")
	{
		// Начинаем игру
    	begin_game();
	}
	if (option == "2")
	{
		// Очищаем терминал
		system("clear");

		// Инициализируем доску
		Desk desk = init_desk();
		Desk *desk_ptr = &desk;

		// Рисуем начальную доску
		print_desk(desk_ptr, None);
		std::cout << "Настройте терминал так, чтобы доски gбыло хорошо видно\n" <<
		"Ctrl++ - увеличить\nCtrl+- - уменьшить\nВведите выйти, чтобы " <<
		"вернуться\n";
		
		std::string exit;
		do {
			std::cin >> exit;
		} while (exit != "выйти");
		menu();
	}
	if (option == "3")
	{
		system("clear");

		Desk desk = init_desk();
		Desk *desk_ptr = &desk;
		Figure_Color color_passage = None;
		std::string answer_while;

		do
		{
			answer_while = "";
			// Рисуем начальную доску
			print_desk(desk_ptr, color_passage);

			std::cout << "Выберите цвет первого игрока: ";

			std::string inner_option;
			std::string local_string;
			std::string answer;
			bool text = true;

			call_cycles(desk_ptr, color_passage, inner_option, local_string,
						g_white_checker, answer, text);
			
			std::cout << "Выберите цвет второго игрока: ";

			call_cycles(desk_ptr, color_passage, inner_option, local_string,
						g_black_checker, answer, text);

			text = false;

			std::cout << "Выберите цвет клеток на которых стоят шашки: ";

			call_cycles(desk_ptr, color_passage, inner_option, local_string,
						g_black_cell, answer, text);

			std::cout << "Выберите цвет клеток на которых не стоят шашки: ";

			call_cycles(desk_ptr, color_passage, inner_option, local_string,
						g_white_cell, answer, text);

			text = true;

			std::cout << "Выберите цвет цифр на краях доски: ";

			call_cycles(desk_ptr, color_passage, inner_option, local_string,
						g_number_color, answer, text);

			std::cout << "Выберите цвет букв на краях доски: ";

			call_cycles(desk_ptr, color_passage, inner_option, local_string,
						g_letter_color, answer, text);

			std::cout << "Повторить настройку?(да/нет): ";

			while (answer_while != "да" && answer_while != "нет")
			{
				std::cin >> answer_while;
			}
		} while (answer_while != "нет");

		save_config();
		menu();
	}
	if (option == "4")
	{
		Desk desk;
		Desk *desk_ptr = &desk;
		Figure_Color color_passage;
		print_desk(desk_ptr, color_passage);

		std::string position;
		do
		{
			std::cout << "Расставьте белые шашки, позже напишите 'продолжить'\n";
			
			do
			{
				std::cin >> position;

				// Выходим из режима редактора
				if (position == "выйти")
				{
					break;
				}

				// Если не ключевое слово
				std::cout << "\nХод невозможен!\nВведите другой:\n";

			} while (//!std::regex_match(position, std::regex("[a-h][1-8]"))
				true); 
		} while (position != "продолжить" && position != "выйти");
		if (position == "выйти")
		{
			system("clear");
			menu();
		}
	}
	if (option == "5")
	{
		system("clear");
		exit(0);
	}
}