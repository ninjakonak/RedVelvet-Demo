#include"include/Game.h"
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>





int main() {

	std::srand(static_cast<unsigned>(time(NULL)));
	
	Game game;


	while (game.Running()) {
		game.Update();
	}
	

	

	

	return 0;
}