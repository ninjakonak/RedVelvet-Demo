#include "../include/Game.h"



void Game::InitWindow() {
	this->videoMode.height = this->screen_height;
	this->videoMode.width = this->screen_width;
	this->window = new sf::RenderWindow(this->videoMode, "...", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::ParseJSON() {
	this->dataFile = std::ifstream("Data/GameData.json");
	jsonReader.parse(this->dataFile, this->jsonData);

	
	int index = 0;

	
	
	
	
	for (int i = 1; i < 10; i++) {
		for (Json::Value mapValue : this->jsonData["maps"]["map" + std::to_string(i)]) {

			this->gameMap[index] = mapValue.asInt();
			
			index++;
		}
	}
}


void Game::InitVariables() {
	this->window = nullptr;
	this->ParseJSON();
}




void Game::InitSprites() {
	this->block.setTexture(this->dirtTexture);
	this->grass.setTexture(this->grassTexture);
	this->backGround.setTexture(this->backgroundTexture);
	this->edgeGrass.setTexture(this->edgeGrassTexture);
	this->rock.setTexture(this->rockTexture);
	this->rock2.setTexture(this->rockTexture2);
	this->purpleBlock.setTexture(this->purpleBlockTexture);
	this->halfPurpleBlockRightTop.setTexture(this->halfPurpleBlockRightTopTexture);
	this->halfPurpleBlockLeftTop.setTexture(this->halfPurpleBlockLeftTopTexture);
	this->halfPurpleBlockTop.setTexture(this->halfPurpleBlockTopTexture);
	this->tinyGrass1.setTexture(this->tinyGrass1Texture);
	this->tinyGrass2.setTexture(this->tinyGrass2Texture);
	this->tree.setTexture(this->treeTexture);
	this->spike.setTexture(this->spikeTexture);
}

void Game::InitTextures() {
	if (!this->dirtTexture.loadFromFile("graphics/blocks/bottomgrass.png")) {
		std::cout << "error";
	}

	if (!this->grassTexture.loadFromFile("graphics/blocks/grassdeneme.png")) {
		std::cout << "error";
	}

	if (!this->backgroundTexture.loadFromFile("graphics/background.png")) {
		std::cout << "error";
	}

	if (!this->rockTexture.loadFromFile("graphics/blocks/rock2.png")) {
		std::cout << "error";
	}

	if (!this->purpleBlockTexture.loadFromFile("graphics/blocks/FullPurpleBlock.png")) {
		std::cout << "error";
	}

	if (!this->halfPurpleBlockRightTopTexture.loadFromFile("graphics/blocks/PurpleGrass1.png")) {
		std::cout << "error";
	}

	if (!this->halfPurpleBlockLeftTopTexture.loadFromFile("graphics/blocks/PurpleGrass2.png")) {
		std::cout << "error";
	}

	if (!this->halfPurpleBlockTopTexture.loadFromFile("graphics/blocks/PurpleGrass3.png")) {
		std::cout << "error";
	}

	if (!this->tinyGrass1Texture.loadFromFile("graphics/blocks/TinyGrass1.png")) {
		std::cout << "error";
	}

	if (!this->tinyGrass2Texture.loadFromFile("graphics/blocks/TinyGrass2.png")) {
		std::cout << "error";
	}

	if (!this->treeTexture.loadFromFile("graphics/blocks/Tree.png")) {
		std::cout << "error";
	}

	if (!this->spikeTexture.loadFromFile("graphics/blocks/Spike.png")) {
		std::cout << "error";
	}
}

void Game::InitMap() {
	this->hitboxSprites.clear();
	this->visibleTiles.clear();
	this->leftExits.clear();
	this->topExits.clear();
	this->bottomExits.clear();
	this->rightExits.clear();
	this->backgroundSprites.clear();
	this->visibleBackgroundSprites.clear();
	
	int startpoint = ((this->mapIndexY * this->numberOfMapsX) + this->mapIndexX) * (this->mapHeight * this->mapWidth);

	for (int i = startpoint; i < startpoint + (this->mapHeight * this->mapWidth); i++) {
		int ystart = i % (this->mapHeight * this->mapWidth);
		


		if (this->gameMap[i] == 1) {
			this->purpleBlock.setPosition((ystart % this->mapWidth) * this->tileSize, (ystart / this->mapWidth) * this->tileSize);
			this->visibleTiles.push_back(this->purpleBlock);
			this->hitboxSprites.push_back(this->purpleBlock);
		}

		if (this->gameMap[i] == 2) {

			this->halfPurpleBlockTop.setPosition((ystart % this->mapWidth) * this->tileSize, (ystart / this->mapWidth) * this->tileSize);
			this->visibleTiles.push_back(this->halfPurpleBlockTop);
			this->hitboxSprites.push_back(this->halfPurpleBlockTop);
		}

		if (this->gameMap[i] == 3) {

			if (this->mapIncX == 0 && this->mapIncY == 0) {
				float x = (ystart % this->mapWidth) * this->tileSize;
				float y = ((ystart / this->mapWidth) - (this->player.height / this->tileSize)) * this->tileSize;
				this->player.SetBeginningCoordinates(x,y);
				
			}
		}

		if (this->gameMap[i] == 10) {
			this->leftExit.x = (ystart % this->mapWidth) * this->tileSize;
			this->leftExit.y = (ystart / this->mapWidth) * this->tileSize;

			if (this->mapIncX == 1) {
				float x = ((ystart % this->mapWidth) + 2) * this->tileSize;
				float y = ((ystart / this->mapWidth) - (this->player.height / this->tileSize)) * this->tileSize;
				this->player.SetBeginningCoordinates(x,y);
			}

			this->leftExits.push_back(this->leftExit);
		}

		if (this->gameMap[i] == 11) {
			this->rightExit.x = (ystart % this->mapWidth) * this->tileSize;
			this->rightExit.y = (ystart / this->mapWidth) * this->tileSize;

			if (this->mapIncX == -1) {
				float x = ((ystart % this->mapWidth) - 3) * this->tileSize;
				float y = ((ystart / this->mapWidth) - (this->player.height / this->tileSize)) * this->tileSize;
				this->player.SetBeginningCoordinates(x, y);
			}

			this->rightExits.push_back(this->rightExit);
		}

		if (this->gameMap[i] == 12) {
			this->topExit.x = (ystart % this->mapWidth) * this->tileSize;
			this->topExit.y = (ystart / this->mapWidth) * this->tileSize;

			if (this->mapIncY == 1) {
				float x = ((ystart % this->mapWidth)) * this->tileSize;
				float y = ((ystart / this->mapWidth) + 4) * this->tileSize;
				this->player.SetBeginningCoordinates(x, y);
			}


			this->topExits.push_back(this->topExit);
		}

		if (this->gameMap[i] == 13) {
			this->bottomExit.x = (ystart % this->mapWidth) * this->tileSize;
			this->bottomExit.y = (ystart / this->mapWidth) * this->tileSize;

			if (this->mapIncY == -1) {
				float x = (ystart % this->mapWidth - (this->player.width / this->tileSize) / 2) * this->tileSize;
				float y = ((ystart / this->mapWidth) - 4) * this->tileSize;
				this->player.SetBeginningCoordinates(x, y);
			}

			this->bottomExits.push_back(this->bottomExit);
		}
		
		if (this->gameMap[i] == 8) {
			this->halfPurpleBlockLeftTop.setPosition((ystart % this->mapWidth) * this->tileSize, (ystart / this->mapWidth) * this->tileSize);
			this->visibleTiles.push_back(this->halfPurpleBlockLeftTop);
			this->hitboxSprites.push_back(this->halfPurpleBlockLeftTop);
		}

		if (this->gameMap[i] == 9) {
			this->halfPurpleBlockRightTop.setPosition((ystart % this->mapWidth) * this->tileSize, (ystart / this->mapWidth) * this->tileSize);
			this->visibleTiles.push_back(this->halfPurpleBlockRightTop);
			this->hitboxSprites.push_back(this->halfPurpleBlockRightTop);
		}

		if (this->gameMap[i] == 4) {
			this->tree.setPosition((ystart % this->mapWidth) * this->tileSize, (ystart / this->mapWidth) * this->tileSize);
			this->visibleBackgroundSprites.push_back(this->tree);
			this->backgroundSprites.push_back(this->tree);
		}

		if (this->gameMap[i] == 5) {
			this->spike.setPosition((ystart % this->mapWidth) * this->tileSize, (ystart / this->mapWidth) * this->tileSize);
			this->visibleTiles.push_back(this->spike);
			this->hitboxSprites.push_back(this->spike);
			this->spikes.push_back(this->spike);
		}

		if (this->gameMap[i] == 6) {
			this->tinyGrass1.setPosition((ystart % this->mapWidth) * this->tileSize, (ystart / this->mapWidth) * this->tileSize);
			this->visibleBackgroundSprites.push_back(this->tinyGrass1);
			this->backgroundSprites.push_back(this->tinyGrass1);
		}

		if (this->gameMap[i] == 7) {
			this->tinyGrass2.setPosition((ystart % this->mapWidth) * this->tileSize, (ystart / this->mapWidth) * this->tileSize);
			this->visibleBackgroundSprites.push_back(this->tinyGrass2);
			this->backgroundSprites.push_back(this->tinyGrass2);
		}
	}
	this->mapIncX = 0;
	this->mapIncY = 0;
	this->CreatePlayer();
	
}

void Game::CreatePlayer() {
	this->player.SetMap(this->hitboxSprites,this->spike.getTexture(),this->mapIndexX, this->mapIndexY, this->mapIncX, this->mapIncY);
	this->player.SetExits(this->leftExits, this->rightExits, this->topExits, this->bottomExits);
	this->player.SetWindow(this->window);
}

Game::Game() {
	this->InitVariables();
	this->InitWindow();
	this->InitTextures();
	this->InitSprites();
	this->InitMap();
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
	if (this->player.CheckExits()) {
		this->mapIndexX = this->player.getMapIndexes().x;
		this->mapIndexY = this->player.getMapIndexes().y;
		this->mapIncX = this->player.getMapIncrements().x;
		this->mapIncY = this->player.getMapIncrements().y;
		this->InitMap();
	}
	this->MoveCamera();
	this->Render();
	this->player.Draw();
	this->DisplayScreen();
}

void Game::MoveCamera() {
	int index = 0;
	for (auto& tile : this->hitboxSprites) {



		this->visibleTiles[index].setPosition(tile.getPosition().x - this->player.offsetPos.x, tile.getPosition().y - this->player.offsetPos.y);
		

		index += 1;
	}
	index = 0;
	for (auto& tile : this->backgroundSprites) {



		this->visibleBackgroundSprites[index].setPosition(tile.getPosition().x - this->player.offsetPos.x, tile.getPosition().y - this->player.offsetPos.y);


		index += 1;
	}
}

void Game::RenderTiles() {
	for (auto& e : this->visibleTiles) {
		if (e.getPosition().x < 960 && e.getPosition().y < 960 && e.getPosition().x > 0 - this->tileSize && e.getPosition().y > 0 - this->tileSize) {
			this->window->draw(e);
		}
		
	}

	for (auto& e : this->visibleBackgroundSprites) {
		if (e.getPosition().x < 960 && e.getPosition().y < 960&& e.getPosition().x > 0 - 120 && e.getPosition().y > 0-120) {
			this->window->draw(e);
		}
		
	}
	
}

const bool Game::Running() const {
	return this->window->isOpen();
}

void Game::Render() {
	this->window->draw(this->backGround);
	this->RenderTiles();
}

void Game::DisplayScreen() {
	this->window->display();
}

void Game::ClearScreen() {
	this->window->clear();
}