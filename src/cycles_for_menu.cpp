#include "../include/cycles_for_menu.h"

void cycle_color(Desk *desk, Figure_Color &color_passage, 
					std::string &inner_option, std::string &local_string,
					std::string &global_color, bool &text)
{
	do {
		std::cout << "\n1. Черный\n2. Белый\n3. Красный\n4. Синий\n5. Голубой\n"
		"6. Зелёный\n7. Лаймовый\n8. Жёлтый\n9. Оранжевый\n10. Розовый\n" <<
		"11. Фиолетовый\n\u2500\n";

		std::cin >> inner_option;
		if (text)
		{
			if (inner_option == "1")
			{
				local_string = "\e[30m";
				break;
			}
			if (inner_option == "2")
			{
				local_string = "\e[97m";
				break;
			}
			if (inner_option == "3")
			{
				local_string = "\e[31m";
				break;
			}
			if (inner_option == "4")
			{
				local_string = "\e[34m";
				break;
			}
			if (inner_option == "5")
			{
				local_string = "\e[96m";
				break;
			}
			if (inner_option == "6")
			{
				local_string = "\e[32m";
				break;
			}
			if (inner_option == "7")
			{
				local_string = "\e[92m";
				break;
			}
			if (inner_option == "8")
			{
				local_string = "\e[93m";
				break;
			}
			if (inner_option == "9")
			{
				local_string = "\e[33m";
				break;
			}
			if (inner_option == "10")
			{
				local_string = "\e[91m";
				break;
			}
			if (inner_option == "11")
			{
				local_string = "\e[35m";
				break;
			}
		}
		else
		{
			if (inner_option == "1")
			{
				local_string = "\e[100m";
				break;
			}
			if (inner_option == "2")
			{
				local_string = "\e[47m";
				break;
			}
			if (inner_option == "3")
			{
				local_string = "\e[41m";
				break;
			}
			if (inner_option == "4")
			{
				local_string = "\e[44m";
				break;
			}
			if (inner_option == "5")
			{
				local_string = "\e[106m";
				break;
			}
			if (inner_option == "6")
			{
				local_string = "\e[42m";
				break;
			}
			if (inner_option == "7")
			{
				local_string = "\e[102m";
				break;
			}
			if (inner_option == "8")
			{
				local_string = "\e[103m";
				break;
			}
			if (inner_option == "9")
			{
				local_string = "\e[43m";
				break;
			}
			if (inner_option == "10")
			{
				local_string = "\e[101m";
				break;
			}
			if (inner_option == "11")
			{
				local_string = "\e[45m";
				break;
			}	
		}
		
	} while (inner_option != "выйти");
	if (inner_option == "выйти")
	{
		system("clear");
		save_config();
		menu();
	}
	global_color = local_string;
	print_desk(desk, color_passage);
}

void cycle_answer(Desk *desk, Figure_Color &color_passage,
 					std::string &inner_option, std::string &local_string,
 					std::string &global_color, std::string &answer, bool &text)
{
	do
	{
		std::cin >> answer;
		if (answer == "да")
		{
			std::cout << "Введите другой номер цвета: ";
			if (text)
			{
				cycle_color(desk, color_passage, inner_option, local_string,
								global_color, text);
			}
			else
			{
				cycle_color(desk, color_passage, inner_option, local_string,
								global_color, text);
			}
			std::cout << "Выбрать другой цвет?(да/нет): ";
		}
	} while (answer != "нет");
}

void call_cycles(Desk *desk, Figure_Color &color_passage,
 					std::string &inner_option, std::string &local_string,
 					std::string &global_color, std::string &answer, bool &text)
{
	cycle_color(desk, color_passage, inner_option, local_string,
							global_color, text);
	std::cout << "Выбрать другой цвет?(да/нет): ";
	cycle_answer(desk, color_passage, inner_option, local_string,
						global_color, answer, text);
}
