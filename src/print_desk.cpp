#include "../include/print_desk.h"

void print_number_column(int &y)
{
	// Рисуем клетки для обозначений игрового поля (Цифры)
	std::cout << VERTICAL_LINE << NUMBER_COLOR << " " << MAX_LINES - y << UN_NUMBER_COLOR << " ";
}

void print_letter_line()
{
	// Буква A
	char letter = 65;

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

		// Выводим буквенные обозначения
		std::cout << " " << LETTER_COLOR << letter++ << UN_LETTER_COLOR << " "  << "";
	}
	std::cout << VERTICAL_LINE << '\n';
}

// Выводим данные из массива в виде фигур
std::string int_to_figures(Coordinate &matrix, Figure &cell)
{
	cell = g_desk[matrix.y][matrix.x];
	// Раскраска фигур
	if (cell.figure_color == Black) 
	{
		// Цвет фигуры                                  
		return BLACK_FIGURES + 
				// Выбираем фигуру для вывода
				g_char_figures[cell.figure_type - 1];
	} 

	if (cell.figure_color == White && cell.figure_type != E)
	{
		return WHITE_FIGURES + g_char_figures[cell.figure_type - 1];
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
	// Рисуем начало нижней части клетки
	std::cout << BEGIN_BOTTOM_CELL_LINE;

	// Выводим нижнюю линию, между игровым полем и буквенными значениями
	print_line(INTERCELLULAR_LINE);

	// Рисуем конец нижней части клетки
	std::cout << END_BOTTOM_CELL_LINE;
}

// Повторяющийся цикл при смене вида от белых и чёрных фигур
void cycle_in_swap_desk(int &y, Coordinate &matrix, Figure &cell)
{
	// Рисуем цифровые обозначения клеток
	print_number_column(y);

	// Выводим фигуры с вертикальными линиями
	for (matrix.x = 0; matrix.x < 8; ++matrix.x)
	{
		std::cout << VERTICAL_LINE;

		// Раскрашиваем клетки в чёрный и белый
		if ((y % 2 != 0 && matrix.x % 2 == 0) || ((y % 2 == 0 && matrix.x % 2 != 0)))
		{
			std::cout << BLACK_CELL;
		} 
		else
		{
			std::cout << WHITE_CELL;
		} 
		matrix.y = MAX_LINES - y - 1;
		std::cout << " " << int_to_figures(matrix, cell) << " \e[0m";
	}
	print_number_column(y);

	// Рисуем последнюю вертикальную линию
	std::cout << VERTICAL_LINE << '\n';
	
	// Рисуем горизонтальные линии между клетками игрового поля
	print_horizontal_line();
}

// Переворачивает доску для другого игрока
void swap_desk()
{
	Coordinate matrix;

	Figure cell;

	// Рисуем доску для белых
	if (g_color_passage == true)
	{
		for (int y = 7; y >= 0; --y)
		{
			cycle_in_swap_desk(y, matrix, cell);
		}
		g_color_passage = false;
	}

	// Для чёрных
	else 
	{
		for (int y = 0; y < 8; ++y)
		{
			cycle_in_swap_desk(y, matrix, cell);
		}
		g_color_passage = true;
	}
}

// Рисуем доску
void print_desk(desk desk)
{
	// Очищаем терминал, прежде чем нарисовать доску
	system("clear");

	// Рисуем вехнюю часть доски
	std::cout << LEFT_TOP_CORNER;
	print_line(TOP_LINE);
	std::cout << RIGHT_TOP_CORNER;

	// Рисуем буквенные обозначения
	print_letter_line();

	// Рисуем границу между буквенными обозначениями и фигурами
	print_horizontal_line();

	// Меняем отрисовку доски на противоположную
	swap_desk();
	
	// Рисуем буквенные обозначения
	print_letter_line();

	// Рисуем нижнюю часть доски
	std::cout << LEFT_BOTTOM_CORNER;
	print_line(BOTTOM_LINE);
	std::cout << RIGHT_BOTTOM_CORNER;
}