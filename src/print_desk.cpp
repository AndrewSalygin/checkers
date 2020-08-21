#include "../include/print_desk.h"

void print_space()
{
	std::cout << ' ';
}

void print_number_column(int &y)
{
	// Рисуем клетки для обозначений игрового поля (Цифры)
	std::cout << VERTICAL_LINE << g_number_color << " " << MAX_LINES - y <<
		g_un_number_color << " ";
}

void cycle_in_letter_line(char &letter, bool &inc)
{
	// Рисуем клетки для обозначений игрового поля (Буквы)
	for (int x = 0; x < 10; ++x)
	{
		std::cout << VERTICAL_LINE;

		// Оставляем пустые клетки на углах
		if (x == 0 || x == 9)
		{
			std::cout << "   ";
			continue;
		}

		// Если буквы выводятся по алфавиту
		if (inc)
		{
			// Выводим буквенные обозначения
			std::cout << " " << g_letter_color << letter++ << g_un_letter_color 
			<< " " << "";
		}
		// Против
		else
		{
			// Выводим буквенные обозначения
			std::cout << " " << g_letter_color << letter-- << g_un_letter_color 
			<< " " << "";
		}
		
	}
	std::cout << VERTICAL_LINE;
}

void print_letter_line()
{
	// Для белых
	// Буква A
	char letter = 65;
	bool inc    = true;

	cycle_in_letter_line(letter, inc);

	// Оставляем пробел
	print_space();

	// Для чёрных
	// Буква H
	letter = 72;
	inc    = false;

	cycle_in_letter_line(letter, inc);

	std::cout << '\n';
}

// Выводим данные из массива в виде фигур
std::string int_to_checkers(const Desk *desk, Coordinate &matrix, Figure &cell)
{
	// Выбираем клетку
	cell = (*desk)[matrix.y][matrix.x];
	
	// Раскраска пешек
	if (cell.figure_type == Checker)
	{
		if (cell.figure_color == Black) 
		{
			// Цвет шашки                                 
			return g_black_checker + "⛂";
		} 
		if (cell.figure_color == White)
		{
			return g_white_checker + "⛂";
		} 
	}
	// Раскраска дамок
	if (cell.figure_type == King)
	{
		if (cell.figure_color == Black) 
		{
			// Цвет шашки                                 
			return g_black_checker + "⛃";
		} 
		if (cell.figure_color == White)
		{
			return g_white_checker + "⛃";
		} 
	}

	// Отображение пустых клеток
	return " ";
}

// Печатаем различные линии для доски
void print_line(const std::string &line)
{
	for (int i = 0; i < 9; ++i)
	{
		std::cout << line;
	}
}

void print_horizontal_line()
{
	for (int i = 0; i < 2; ++i)
	{
		// Рисуем начало нижней части клетки
		std::cout << BEGIN_BOTTOM_CELL_LINE;

		// Выводим нижнюю линию, между игровым полем и буквенными значениями
		print_line(INTERCELLULAR_LINE);

		// Рисуем конец нижней части клетки
		std::cout << END_BOTTOM_CELL_LINE;

		// Оставляем пробел
		print_space();
	}
}

void if_in_cycle(const Desk *desk, int &y, Coordinate &matrix, Figure &cell)
{
	// Рисуем первую вертикальную линию
	std::cout << VERTICAL_LINE;

	// Раскрашиваем клетки в чёрный и белый
	if ((y % 2 != 0 && matrix.x % 2 == 0) ||
			((y % 2 == 0 && matrix.x % 2 != 0)))
	{
		std::cout << g_black_cell;
	} 
	else
	{
		std::cout << g_white_cell;
	}

	matrix.y = MAX_LINES - y - 1;
	std::cout << " " << int_to_checkers(desk, matrix, cell) << " \e[0m"; 
}

// Повторяющийся цикл при смене вида от белых и чёрных фигур
void cycle_in_main_desk(const Desk *desk, int &y, Coordinate &matrix,
								Figure &cell, const Figure_Color &local_color)
{
	// Рисуем цифровые обозначения клеток
	print_number_column(y);

	if (local_color == White)
	{
		// Выводим фигуры с вертикальными линиями
		for (matrix.x = 0; matrix.x < 8; ++matrix.x)
		{
			if_in_cycle(desk, y, matrix, cell);
		}

		// Рисуем цифровые обозначения клеток
		print_number_column(y);

		// Рисуем последнюю вертикальную линию
		std::cout << VERTICAL_LINE;
		
		print_space();
	}
	else
	{
		// Выводим фигуры с вертикальными линиями
		for (matrix.x = 7; matrix.x >= 0; --matrix.x)
		{
			if_in_cycle(desk, y, matrix, cell);
		}

		// Рисуем цифровые обозначения клеток
		print_number_column(y);

		// Рисуем последнюю вертикальную линию
		std::cout << VERTICAL_LINE;
	}
}

// Рисует основную часть досок
void print_main_desk(const Desk *desk)
{
	// Координаты клетки
	Coordinate matrix;

	// Сама клетка
	Figure cell;

	// Цвет для которого отрисовываем доску
	Figure_Color local_color;

	// Рисуем доски
	for (int y_w = 7, y_b = 0; y_w >= 0 && y_b < 8; --y_w, ++y_b)
	{
		// Для белых
		local_color = White;
		cycle_in_main_desk(desk, y_b, matrix, cell, local_color);

		// Для чёрных
		local_color = Black;
		cycle_in_main_desk(desk, y_w, matrix, cell, local_color);

		std::cout << '\n';

		// Рисуем горизонтальные линии между клетками игрового поля
		print_horizontal_line();

		std::cout << '\n';
	}
}

// Отображаем подсказки
void print_hint()
{
	std::cout << "Чтобы выйти из игры напишите: выйти\n" <<
	"Чтобы предложить ничью: ничья\nЧтобы сдаться: сдаюсь\n";
}

// Рисует края досок
void print_group(const std::string LEFT_CORNER, const std::string RIGHT_CORNER,
					const std::string LINE)
{
	for (int i = 0; i < 2; ++i)
	{
		std::cout << LEFT_CORNER;
		print_line(LINE);
		std::cout << RIGHT_CORNER;

		// Оставляем пробел
		print_space();
	}
	std::cout << '\n';
}

// Рисуем доску
void print_desk(const Desk *desk, const Figure_Color &color_passage)
{
	// Очищаем терминал, прежде чем нарисовать доску
	system("clear");

	// Выводим подсказки, вверху досок
	print_hint();

	// Рисуем вехнюю часть досок
	print_group(LEFT_TOP_CORNER, RIGHT_TOP_CORNER, TOP_LINE);

	// Рисуем верхние буквенные обозначения досок
	print_letter_line();

	// Рисуем границу между буквенными обозначениями и фигурами
	print_horizontal_line();

	std::cout << '\n';

	// Рисуем основную часть досок
	print_main_desk(desk);
	
	// Рисуем нижние буквенные обозначения досок
	print_letter_line();

	// Рисуем нижнюю часть досок
	print_group(LEFT_BOTTOM_CORNER, RIGHT_BOTTOM_CORNER, BOTTOM_LINE);
}