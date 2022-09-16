#pragma once
#ifndef GAME_H
#define GAME_H
#include<iostream>
#include<vector>
#include<ctime>
#include"Player.h"
#include<string>
#include<thread>
#include<json/json.h>
#include"constants.h"
#include"Level.h"

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>

class Game
{
public:
	Game();
	virtual ~Game();
	const bool Running() const;
	void Update();
private:
	void InitVariables();
	void InitWindow();
	

	sf::VideoMode videoMode;
	sf::RenderWindow* window;

	Level level;

	sf::Event ev;

	std::vector<sf::Sprite> visibleTiles;
	std::vector<sf::Sprite> visibleBackgroundSprites;

	std::vector<sf::Sprite> hitboxSprites;
	std::vector<sf::Sprite> backgroundSprites;

	sf::Vector2f leftExit;
	sf::Vector2f rightExit;
	sf::Vector2f topExit;
	sf::Vector2f bottomExit;

	std::vector<sf::Vector2f> leftExits;
	std::vector<sf::Vector2f> rightExits;
	std::vector<sf::Vector2f> topExits;
	std::vector<sf::Vector2f> bottomExits;

	int screen_height = 960;
	int screen_width = 960;
	int tileSize;

	int numberOfMapsX = 3;
	int	numberOfMapsY = 3;

	int mapHeight = 180;
	int mapWidth = 180;
	

	short* gameMap = new short[numberOfMapsX * numberOfMapsY * mapHeight * mapWidth];
		

	int mapIndexX = 1;
	int mapIndexY = 1;

	int mapIncX = 0;
	int mapIncY = 0;


	
	
	void PollEvents();
	void ClearScreen();
	void DisplayScreen();

	Player player;
	void SetPlayerWindow();

	sf::Texture dirtTexture;
	sf::Texture grassTexture;
	sf::Texture backgroundTexture;
	sf::Texture edgeGrassTexture;
	sf::Texture rockTexture;
	sf::Texture rockTexture2;
	sf::Texture purpleBlockTexture;
	sf::Texture halfPurpleBlockLeftTopTexture;
	sf::Texture halfPurpleBlockTopTexture;
	sf::Texture halfPurpleBlockRightTopTexture;
	sf::Texture tinyGrass1Texture;
	sf::Texture tinyGrass2Texture;
	sf::Texture treeTexture;
	sf::Texture spikeTexture;

	sf::Sprite block;
	sf::Sprite grass;
	sf::Sprite backGround;
	sf::Sprite edgeGrass;
	sf::Sprite rock;
	sf::Sprite rock2;
	sf::Sprite purpleBlock;
	sf::Sprite halfPurpleBlockLeftTop;
	sf::Sprite halfPurpleBlockRightTop;
	sf::Sprite halfPurpleBlockTop;
	sf::Sprite tinyGrass1;
	sf::Sprite tinyGrass2;
	sf::Sprite tree;
	sf::Sprite spike;


	std::ifstream dataFile;
	Json::Value jsonData;
	Json::Reader jsonReader;
};

#endif
