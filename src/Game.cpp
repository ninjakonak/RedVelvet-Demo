#include "../include/Game.h"



void Game::InitWindow() {
	this->videoMode.height = this->screen_height;
	this->videoMode.width = this->screen_width;
	this->window = new sf::RenderWindow(this->videoMode, "...", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}




void Game::InitVariables() {
	this->window = nullptr;
	this->tileSize = TILE_HEIGHT;
}





void Game::SetPlayerWindow() {
	this->player.SetWindow(this->window);
}

Game::Game() {
	this->InitVariables();
	this->InitWindow();
	this->level.InitiatePlayer(this->window, &this->player);
	this->SetPlayerWindow();
}

Game::~Game() {
	delete this->window;
	delete[] this->gameMap;
}

void Game::PollEvents() {
	while (this->window->pollEvent(this->ev)) {

		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
			break;
		}
	}
}



void Game::Update() {
	this->ClearScreen();
	this->PollEvents();
	this->player.Update();
	this->level.Update();
	this->level.Render();
	this->player.Draw();
	this->DisplayScreen();
}

const bool Game::Running() const {
	return this->window->isOpen();
}



void Game::DisplayScreen() {
	this->window->display();
}

void Game::ClearScreen() {
	this->window->clear();
}