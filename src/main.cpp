// Для setlocale();
#include <iostream>

#include "../include/begin_game.h"

int main() {
    setlocale (LC_ALL, "ru_RU.UTF-8");
    
    // Create menu doo
    // Начинаем игру
    begin_game();

	return 0;
}