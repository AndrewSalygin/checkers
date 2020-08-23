#include "../include/cycles_for_menu.h"

// Выбираем цвет
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
		// Очищаем терминал
		system("clear");

		// Сохраняем настройки
		save_config();

		// Выходим в меню
		menu();
	}

	// Меняем на выбранный цвет
	global_color = local_string;

	// Отображаем изменения
	print_desk(desk, color_passage);
}

void cycle_answer(Desk *desk, Figure_Color &color_passage,
 					std::string &inner_option, std::string &local_string,
 					std::string &global_color, std::string &answer, bool &text)
{
	do
	{
		std::cin >> answer;
		if (answer == "д")
		{
			std::cout << "Введите другой номер цвета: ";

			// Если это текст
			if (text)
			{
				cycle_color(desk, color_passage, inner_option, local_string,
								global_color, text);
			}
			// Если это фон
			else
			{
				cycle_color(desk, color_passage, inner_option, local_string,
								global_color, text);
			}

			std::cout << "Выбрать другой цвет?(д/н): ";
		}
	} while (answer != "н");
}

// Вызов циклов
void call_cycles(Desk *desk, Figure_Color &color_passage,
 					std::string &inner_option, std::string &local_string,
 					std::string &global_color, std::string &answer, bool &text)
{
	// Выбор цвета
	cycle_color(desk, color_passage, inner_option, local_string,
							global_color, text);

	std::cout << "Выбрать другой цвет?(д/н): ";

	// Поменять выбранный цвет
	cycle_answer(desk, color_passage, inner_option, local_string,
						global_color, answer, text);
}

void filling_array(Desk *desk, Figure_Color &color_passage, Coordinate &matrix_c,
					Figure_Type &type, Figure_Color &color, int &count,
					std::string &position)
{
	// Выходим из режима редактора
	if (!(position == "выйти"))
	{
		// Проверяем с помощью регулярных условий и логики шашек
		if (std::regex_match(position, std::regex("[a-h][1-8]")) &&
			((matrix_c.y % 2 != 0 && matrix_c.x % 2 != 0) ||
			  matrix_c.y % 2 == 0 && matrix_c.x % 2 == 0) &&
			  ((*desk)[matrix_c.y][matrix_c.x].figure_type == Empty || 
			  (*desk)[matrix_c.y][matrix_c.x].figure_color == color))
		{
			// Если цвет совпадает, то мы убираем фигуру, которая стояла раньше
			if ((*desk)[matrix_c.y][matrix_c.x].figure_color == color)
			{
				(*desk)[matrix_c.y][matrix_c.x].figure_type = Empty;
				(*desk)[matrix_c.y][matrix_c.x].figure_color = None;
				--count;
				print_desk(desk, color_passage);
				return;
			}

			// Если это белая шашка
			if (type == Checker && color == White)
			{
				if (matrix_c.y != 7)
				{
					(*desk)[matrix_c.y][matrix_c.x].figure_type = Checker;
					(*desk)[matrix_c.y][matrix_c.x].figure_color = White;
					++count;
					print_desk(desk, color_passage);
				}
				else
				{
					std::cout << "Шашки не могут стоять на последней " <<
					"горизонтали. Поставьте туда дамку, в следующем этапе\n";
				}
			}

			// Если это белая дамка
			if (type == King && color == White)
			{
				(*desk)[matrix_c.y][matrix_c.x].figure_type = King;
				(*desk)[matrix_c.y][matrix_c.x].figure_color = White;
				++count;
				print_desk(desk, color_passage);
			}

			// Если это чёрная шашка
			if (type == Checker && color == Black)
			{
				if (matrix_c.y != 0)
				{
					(*desk)[matrix_c.y][matrix_c.x].figure_type = Checker;
					(*desk)[matrix_c.y][matrix_c.x].figure_color = Black;
					++count;
					print_desk(desk, color_passage);
				}
				else
				{
					std::cout << "Шашки не могут стоять на последней " <<
					"горизонтали. Поставьте туда дамку, в следующем этапе\n";
				}
			}

			// Если это чёрная дамка
			if (type == King && color == Black)
			{
				(*desk)[matrix_c.y][matrix_c.x].figure_type = King;
				(*desk)[matrix_c.y][matrix_c.x].figure_color = Black;
				++count;
				print_desk(desk, color_passage);
			}
		}
		else
		{
			std::cout << "Координаты указаны неверно. Попробуйте ещё раз!\n";
		}
	}
	else
	{
		system("clear");
		menu();
	}			
}

void cycle_before_filling(Desk *desk, Figure_Color &color_passage, 
	Coordinate &matrix_c, Figure_Type &type, Figure_Color &color, int &count,
	std::string &position)
{
	do
	{
		// Вводим координаты
		std::cin >> position;

		// Запоминаем координаты
		matrix_c.y = (int)position[1] - 49;
		matrix_c.x = (int)position[0] - 97;

		if (count <= 12)
		{
			if (position == "n")
			{
				std::cout << '\n';
				break;
			}
			filling_array(desk, color_passage, matrix_c, type, color, count, 
							position);
		}
		else
		{
			// Проверяем совпадает ли цвет, чтобы убрать фигуру
			if ((*desk)[matrix_c.y][matrix_c.x].figure_color == color)
			{
				(*desk)[matrix_c.y][matrix_c.x].figure_type = Empty;
				(*desk)[matrix_c.y][matrix_c.x].figure_color = None;
				--count;
				print_desk(desk, color_passage);
			}
			else
			{
				if (position != "n")
				{
					std::cout << "Количество фигур данного цвета максимально!\n";
				}
			}
		}
	} while (position != "выйти" && position != "n");
}