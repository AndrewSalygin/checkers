#include "../include/deadlock.h"

bool deadlock(Desk *desk)
{
	int x;
	Figure_Color local_color;
	int count = 0;

	// Если такая ситуация сложилась, то присваиваем победу чёрным
	for (int y = 1; y < 7; ++y)
	{
		if (y < 4)
		{	
			local_color = White;
		}
		else
		{
			local_color = Black;
		}
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
			if (y == 3 && x == 5)
			{
				if ((*desk)[y][x].figure_color == Black)
				{
					++count;
				}
			}
			if (y == 4 && x == 2)
			{
				if ((*desk)[y][x].figure_color == White)
				{
					++count;
				}
			}
			if ((*desk)[y][x].figure_color == local_color)
			{
				++count;
			}
		}
	}

	// Единственный случай, когда белые не могут сделать ход
	if (count == 24)
	{
		std::cout << "\nЧёрные выиграли!";
		question_restart_game(desk);
	}
	return false;
}
