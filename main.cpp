#include <iostream>
#include "SDL2/SDL.h"

#include "game.hpp"


int main(int argc, char *argv[])
{

	Game new_game;
	new_game.set_game(1024,600,"JOGO");
	new_game.init_game();

	new_game.Run();


	return 0;
}