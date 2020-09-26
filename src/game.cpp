#include "../include/game.h"

// Начинаем игру
void game(Desk *desk, Figure_Color &color_passage)
{
	Desk copy_desk = (*desk);
	Desk *copy_desk_ptr = &copy_desk;
	Figure_Color copy_color_passage = color_passage;
	
	// Отслеживание ничьи
	bool players_draw = false;

	// Ввод игрока
	std::string step;

	std::fstream save_moves;

	int count_moves = 0;

	// Открываем
	save_moves.open("../game", std::ios::out);

	// Вывод текста для игроков
	do
	{
		// begin_game первый раз вернул black для этого цикла;
		// Ходят чёрные
		if (color_passage == White)
		{
			color_passage = Black;
			std::cout << "\nХод второго игрока\nПример(d6e5): ";
		}
		// Ходят белые
		else
		{
			color_passage = White;
			std::cout << "\nХод первого игрока\nПример(e3f4): ";
		}

		// Игрок ходит
		do
		{
			// Проверка на ввод
			check_input(step, players_draw, desk, color_passage, copy_desk_ptr,
				copy_color_passage, save_moves); 
		} while (move_checkers(desk, step, color_passage, players_draw, 
								copy_desk_ptr, copy_color_passage, save_moves) != true 
								&& step != "сдаюсь" && step != "выйти");

		// Отрисовываем доску заново
		print_desk(desk, color_passage);
		
		if (color_passage == White && step != "выйти" && step != "сдаюсь")
		{
			++count_moves;
		}
		
		// Если открыт
		if(save_moves.is_open() && step != "выйти" && step != "сдаюсь")
		{
			if (color_passage == White)
			{
				save_moves << count_moves << ". " << step << ' ';
			}
			else
			{
				save_moves << step << ' ';
			}
		}

	} while (quantity_checkers(desk, color_passage, copy_desk_ptr, copy_color_passage, 
		save_moves) && !deadlock(desk, color_passage, copy_desk_ptr, copy_color_passage, 
	 	save_moves) && step != "выйти" && step != "сдаюсь" && !players_draw);

	save_moves.close();

	if (step == "выйти")
	{
		std::cout << '\n';
		menu();
	}

	if (step == "сдаюсь")
	{
		if (color_passage == White)
		{
			std::cout << '\n';
			std::cout << "Победил второй игрок!\n";

			// Спрашиваем о рестарте игры
			question_restart_game(desk, color_passage, copy_desk_ptr, copy_color_passage, save_moves);
		}
		else
		{
			std::cout << '\n';
			std::cout << "Победил первый игрок!\n";

			// Спрашиваем о рестарте игры
			question_restart_game(desk, color_passage, copy_desk_ptr, copy_color_passage, save_moves);
		}
	}
}