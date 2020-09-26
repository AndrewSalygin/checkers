#include "../include/options.h"

// Выбор пункта в меню
void options()
{
	// Пункт
	std::string option = "";
	
	// Проверяем, есть ли такой пункт
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
		// Инициализируем доску
		Desk desk = init_desk();
		Desk *desk_ptr = &desk;

		// Рисуем начальную доску
		print_desk(desk_ptr, None);
		std::cout << "Настройте терминал так, чтобы доски было хорошо видно\n" <<
		"Ctrl++ - увеличить\nCtrl+- - уменьшить\nВведите выйти, чтобы " <<
		"вернуться\n";
		
		// Выход
		std::string exit;
		do {
			std::cin >> exit;
		} while (exit != "выйти");

		// Возвращаемся в меню
		menu();
	}
	if (option == "3")
	{
		// Инициализируем доску
		Desk desk = init_desk();
		Desk *desk_ptr = &desk;
		Figure_Color color_passage;

		std::string answer_while;

		do
		{
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

			std::cout << "Повторить настройку?(д/н): ";

			while (answer_while != "д" && answer_while != "н")
			{
				std::cin >> answer_while;
			}
		} while (answer_while != "н");

		// Сохраняем конфиг
		save_config();

		// Выходим в меню
		menu();
	}
	if (option == "4")
	{
		// Позиция фигуры в координатах
		Coordinate position_c;

		// Позиция фигуры в строке
		std::string position;
		do
		{
			// Инициализируем доску
			Desk desk = {NULL};
			Desk *desk_ptr = &desk;
			Figure_Color color_passage;
			
			// Выводим пустую доску
			print_desk(desk_ptr, color_passage);

			Figure_Type type = Checker;
			Figure_Color color = White;

			std::cout << "Укажите координаты всех белых шашек" <<
					" по одной\n(чтобы убрать шашку, введите её координаты),\n" <<
					"а позже напишите 'n': ";
			
			int count_white = 1;

			cycle_before_filling(desk_ptr, color_passage, position_c, type, color,
									count_white, position);
			if (count_white < 12)
			{
				std::cout << "Укажите координаты всех белых дамок" <<
					" по одной\n(чтобы убрать дамку, введите её координаты),\n" <<
					"а позже напишите 'n': ";

				type = King;
				cycle_before_filling(desk_ptr, color_passage, position_c, type, color,
										count_white, position);
			}
			
			std::cout << "Укажите координаты всех чёрных шашек" <<
					" по одной\n(чтобы убрать шашку, введите её координаты),\n" <<
					"а позже напишите 'n': ";

			int count_black = 1;
			type = Checker;
			color = Black;
			cycle_before_filling(desk_ptr, color_passage, position_c, type, color,
									count_black, position);

			if (count_black < 12)
			{
				std::cout << "Укажите координаты всех чёрных дамок" <<
					" по одной\n(чтобы убрать дамку, введите её координаты),\n" <<
					"а позже напишите 'n': ";
		
				type = King;
				cycle_before_filling(desk_ptr, color_passage, position_c, type, color,
									count_black, position);
			}
			if (count_white == 1 || count_black == 1)
			{
				std::cout << "Фигур слишком мало. Настройте игру заново!\n\n" <<
				"Введите любой текст, чтобы продолжить: ";
				std::cin >> position;
				continue;
			}
			std::cout << "Кто начинает ходить первым? (1 - Первый игрок, " << 
			"2 - Второй игрок): ";
			do
			{
				std::cin >> position;
				if (position == "1")
				{
					color_passage = Black;
				}
				if (position == "2")
				{
					color_passage = White;
				}
			} while (position != "1" && position != "2" && position != "выйти");

			std::cout << "\nХотите ли вы начать заполнение заново?(д/н): ";

			do
			{
				std::cin >> position; 
				if (position == "н")
				{
					std::cout << '\n';
					print_desk(desk_ptr, color_passage);
					game(desk_ptr, color_passage);
					break;
				}
				std::cout << '\n';
			} while (position != "д" && position != "н");
		} while (position != "выйти" && position != "н");
	}
	if (option == "5")
	{
		// Очищаем терминал
		system("clear");

		// Выходим из игры
		exit(0);
	}
}