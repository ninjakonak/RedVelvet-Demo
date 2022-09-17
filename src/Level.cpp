#include"../include/Level.h"



Level::Level() {
	
}

void Level::InitLevel(Player* playerObj) {
	this->player = playerObj;

	this->InitVariables();
	this->InitMap();
}

void Level::InitWindow(sf::RenderWindow* window) {
	this->window = window;
}

Level::~Level() {
	delete this->backgroundTexture;

	delete this->purpleBlock.texture;
	delete this->halfPurpleBlockLeftTop.texture;
	delete this->halfPurpleBlockRightTop.texture;
	delete this->halfPurpleBlockTop.texture;
	delete this->tinyGrass1.texture;
	delete this->tinyGrass2.texture;
	delete this->tree.texture;
	delete this->spike.texture;
}

void Level::ParseJSON() {
	std::ifstream dataFile;
	Json::Value jsonData;
	Json::Reader jsonReader;
	dataFile = std::ifstream("Data/GameData.json");
	jsonReader.parse(dataFile, jsonData);


	int index = 0;




	for (int i = 1; i < 10; i++) {
		for (Json::Value mapValue : jsonData["maps"]["map" + std::to_string(i)]) {

			this->gameMap[index] = mapValue.asInt();
			//std::cout << mapValue.asInt();
			
			index++;
		}
	}
	//std::cout << "a";
}

void Level::InitVariables() {

	this->transitionScreen.setSize(sf::Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT));
	this->transitionScreen.setPosition(0, 0);

	this->tileSize = TILE_HEIGHT;
	if (!this->backgroundTexture->loadFromFile("graphics/background.png")) {
		std::cout << "error";
	}
	this->InitBlocks();



	this->numberOfMapsX = 3;
	this->numberOfMapsY = 3;

	this->mapHeight = 180;
	this->mapWidth = 180;

	this->mapIndexX = 1;
	this->mapIndexY = 1;

	this->mapIncX = 0;
	this->mapIncY = 0;

	this->gameMap = new short[numberOfMapsX * numberOfMapsY * mapHeight * mapWidth];
	this->ParseJSON();
}

void Level::InitBlocks() {

	this->rect.setSize(sf::Vector2f(20.f, 20.f));
	this->rect.setFillColor(sf::Color::Red);
	
	this->backGround.setTexture(*this->backgroundTexture);
	//this->backGround = Block("graphics/blocks/background.png");

	this->purpleBlock.setTexturePath("graphics/blocks/FullPurpleBlock.png");
	this->halfPurpleBlockLeftTop.setTexturePath("graphics/blocks/PurpleGrass2.png");
	this->halfPurpleBlockRightTop.setTexturePath("graphics/blocks/PurpleGrass1.png");
	this->halfPurpleBlockTop.setTexturePath("graphics/blocks/PurpleGrass3.png");
	this->tinyGrass1.setTexturePath("graphics/blocks/TinyGrass1.png");
	this->tinyGrass2.setTexturePath("graphics/blocks/TinyGrass2.png");
	this->tree.setTexturePath("graphics/blocks/Tree.png");
	this->spike.setTexturePath("graphics/blocks/Spike.png");
}

void Level::InitMap() {
	std::cout << "before clear" << "\n";
	this->hitboxSprites.clear();
	this->visibleTiles.clear();
	this->leftExits.clear();
	this->topExits.clear();
	this->bottomExits.clear();
	this->rightExits.clear();
	this->backgroundSprites.clear();
	this->visibleBackgroundSprites.clear();
	
	int startpoint = ((this->mapIndexY * this->numberOfMapsX) + this->mapIndexX) * (this->mapHeight * this->mapWidth);
	
	std::cout << "started"<<"\n";
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
				float y = ((ystart / this->mapWidth) - (this->player->height / this->tileSize)) * this->tileSize;
				this->player->SetBeginningCoordinates(x, y);
	
			}
		}
	
		if (this->gameMap[i] == 10) {
			this->leftExit.x = (ystart % this->mapWidth) * this->tileSize;
			this->leftExit.y = (ystart / this->mapWidth) * this->tileSize;
	
			if (this->mapIncX == 1) {
				float x = ((ystart % this->mapWidth) + 2) * this->tileSize;
				float y = ((ystart / this->mapWidth) - (this->player->height / this->tileSize)) * this->tileSize;
				this->player->SetBeginningCoordinates(x, y);
			}
	
			this->leftExits.push_back(this->leftExit);
		}
	
		if (this->gameMap[i] == 11) {
			this->rightExit.x = (ystart % this->mapWidth) * this->tileSize;
			this->rightExit.y = (ystart / this->mapWidth) * this->tileSize;
	
			if (this->mapIncX == -1) {
				float x = ((ystart % this->mapWidth) - 3) * this->tileSize;
				float y = ((ystart / this->mapWidth) - (this->player->height / this->tileSize)) * this->tileSize;
				this->player->SetBeginningCoordinates(x, y);
			}
	
			this->rightExits.push_back(this->rightExit);
		}
	
		if (this->gameMap[i] == 12) {
			this->topExit.x = (ystart % this->mapWidth) * this->tileSize;
			this->topExit.y = (ystart / this->mapWidth) * this->tileSize;
	
			if (this->mapIncY == 1) {
				float x = ((ystart % this->mapWidth)) * this->tileSize;
				float y = ((ystart / this->mapWidth) + 4) * this->tileSize;
				this->player->SetBeginningCoordinates(x, y);
			}
	
	
			this->topExits.push_back(this->topExit);
		}
	
		if (this->gameMap[i] == 13) {
			this->bottomExit.x = (ystart % this->mapWidth) * this->tileSize;
			this->bottomExit.y = (ystart / this->mapWidth) * this->tileSize;
	
			if (this->mapIncY == -1) {
				float x = (ystart % this->mapWidth - (this->player->width / this->tileSize) / 2) * this->tileSize;
				float y = ((ystart / this->mapWidth) - 4) * this->tileSize;
				this->player->SetBeginningCoordinates(x, y);
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
	std::cout << "finished"<<"\n";
	this->mapIncX = 0;
	this->mapIncY = 0;
	this->CreatePlayer();

	
}



void Level::CreatePlayer() {
	this->player->SetMap(this->hitboxSprites, this->spike.getTexture(), &this->mapIndexX, &this->mapIndexY, &this->mapIncX, &this->mapIncY);
	this->player->SetExits(this->leftExits, this->rightExits, this->topExits, this->bottomExits);
	
}

void Level::MoveCamera() {
	int index = 0;
	for (auto& tile : this->hitboxSprites) {



		this->visibleTiles[index].setPosition(tile.getPosition().x - this->player->offsetPos.x, tile.getPosition().y - this->player->offsetPos.y);


		index += 1;
	}
	index = 0;
	for (auto& tile : this->backgroundSprites) {



		this->visibleBackgroundSprites[index].setPosition(tile.getPosition().x - this->player->offsetPos.x, tile.getPosition().y - this->player->offsetPos.y);


		index += 1;
	}
}

void Level::Render() {
	this->MoveCamera();
	
	this->window->draw(this->backGround);
	for (auto& e : this->visibleTiles) {
		
		if (e.getPosition().x < 960 && e.getPosition().y < 960 && e.getPosition().x > 0 - this->tileSize && e.getPosition().y > 0 - this->tileSize) {
			this->window->draw(e);
		}

	}

	for (auto& e : this->visibleBackgroundSprites) {
		if (e.getPosition().x < 960 && e.getPosition().y < 960 && e.getPosition().x > 0 - 120 && e.getPosition().y > 0 - 120) {
			this->window->draw(e);
		}

	}
	
}

void Level::Update() {

	if (this->player->CheckExits()) {
		
		this->InitMap();
	}
}