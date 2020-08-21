#include "../include/print_desk.h"

void print_number_column(int &y)
{
	// Рисуем клетки для обозначений игрового поля (Цифры)
	std::cout << VERTICAL_LINE << g_number_color << " " << MAX_LINES - y <<
		g_un_number_color << " ";
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
		std::cout << " " << g_letter_color << letter++ << g_un_letter_color <<
			" " << "";
	}
	std::cout << VERTICAL_LINE << '\n';
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
	// Рисуем начало нижней части клетки
	std::cout << BEGIN_BOTTOM_CELL_LINE;

	// Выводим нижнюю линию, между игровым полем и буквенными значениями
	print_line(INTERCELLULAR_LINE);

	// Рисуем конец нижней части клетки
	std::cout << END_BOTTOM_CELL_LINE;
}

// Повторяющийся цикл при смене вида от белых и чёрных фигур
void cycle_in_swap_desk(const Desk *desk, int &y, Coordinate &matrix,
							Figure &cell)
{
	// Рисуем цифровые обозначения клеток
	print_number_column(y);

	// Выводим фигуры с вертикальными линиями
	for (matrix.x = 0; matrix.x < 8; ++matrix.x)
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
	print_number_column(y);

	// Рисуем последнюю вертикальную линию
	std::cout << VERTICAL_LINE << '\n';
	
	// Рисуем горизонтальные линии между клетками игрового поля
	print_horizontal_line();
}

// Переворачивает доску для другого игрока
void swap_desk(const Desk *desk, Figure_Color &color_passage)
{
	// Координаты клетки
	Coordinate matrix;

	// Шашки или пустое место
	Figure cell;

	// Рисуем доску для белых
	if (color_passage == White)
	{
		for (int y = 7; y >= 0; --y)
		{
			cycle_in_swap_desk(desk, y, matrix, cell);
		}
		color_passage = Black;
	}

	// Для чёрных
	else 
	{
		for (int y = 0; y < 8; ++y)
		{
			cycle_in_swap_desk(desk, y, matrix, cell);
		}
		color_passage = White;
	}
}

void print_rules()
{
	std::cout << "Чтобы выйти из игры напишите: выйти\n" <<
	"Чтобы предложить ничью: ничья\nЧтобы сдаться: сдаюсь\n";

}

// Рисуем доску
void print_desk(const Desk *desk, Figure_Color &color_passage)
{
	// Очищаем терминал, прежде чем нарисовать доску
	system("clear");

	// Выводим правила игры, вверху доски
	print_rules();

	// Рисуем вехнюю часть доски
	std::cout << LEFT_TOP_CORNER;
	print_line(TOP_LINE);
	std::cout << RIGHT_TOP_CORNER;

	// Рисуем буквенные обозначения
	print_letter_line();

	// Рисуем границу между буквенными обозначениями и фигурами
	print_horizontal_line();

	// Меняем отрисовку доски на противоположную
	swap_desk(desk, color_passage);
	
	// Рисуем буквенные обозначения
	print_letter_line();

	// Рисуем нижнюю часть доски
	std::cout << LEFT_BOTTOM_CORNER;
	print_line(BOTTOM_LINE);
	std::cout << RIGHT_BOTTOM_CORNER;
}