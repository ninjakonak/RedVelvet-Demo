#include"include/Game.h"





int main() {

	std::srand(static_cast<unsigned>(time(NULL)));
	
	Game game;


	while (game.Running()) {
		game.Update();
	}
	

	return 0;
}