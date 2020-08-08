#include "../include/init_desk.h"

Desk init_desk()
{
	// Создаём пустую доску
	Desk desk = {NULL};

	int y;
	int max;

	// Заполняем поле шашками
	for (int color = 1; color <= 2; ++color) 
	{
		// Переменные для белых шашек
		if (color == 1)
		{
			y = 0;
			max = 3;
		}
		// Переменные для чёрных шашек
		else
		{
			y = 5;
			max = 8;
		}

		// Заполняем массив
		for (; y < max; ++y)
		{
			int x;

			// Шашки должны стоять только на чёрных клетках
			if (y % 2 == 0)
			{
				x = 0;
			}
			else
			{
				x = 1;
			}
			for (; x < 8; x += 2)
			{
				desk[y][x].figure_type = Checker;
				desk[y][x].figure_color = (Figure_Color) color;
				desk[y][x].coordinate.y = y;
				desk[y][x].coordinate.x = x;
			}
		}
	}
	return desk;
}