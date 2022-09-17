#pragma once
#ifndef LEVEL_H
#define LEVEL_H


#include<json/json.h>
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include"Block.h"
#include"constants.h"
#include"Player.h"

class Level {


public:
	
	Level();

	void InitLevel(Player* playerObj);

	void InitWindow(sf::RenderWindow* window);

	virtual ~Level();
	void Render();

	void Update();

private:

	Player* player;
	sf::RenderWindow* window;

	int numberOfMapsX;
	int	numberOfMapsY;

	int mapHeight;
	int mapWidth;

	int mapIndexX;
	int mapIndexY;

	int mapIncX;
	int mapIncY;

	short* gameMap;

	int tileSize;
	

	void CreatePlayer();

	void InitMap();

	void ParseJSON();

	void InitVariables();

	void InitBlocks();

	void MoveCamera();

	sf::RectangleShape rect;
	
	sf::Sprite backGround;
	sf::Texture* backgroundTexture = new sf::Texture();
	

	Block purpleBlock;
	Block halfPurpleBlockLeftTop;
	Block halfPurpleBlockRightTop;
	Block halfPurpleBlockTop;
	Block tinyGrass1;
	Block tinyGrass2;
	Block tree;
	Block spike;

	sf::Vector2f leftExit;
	sf::Vector2f rightExit;
	sf::Vector2f topExit;
	sf::Vector2f bottomExit;

	std::vector<sf::RectangleShape> rects;

	std::vector<sf::Vector2f> leftExits;
	std::vector<sf::Vector2f> rightExits;
	std::vector<sf::Vector2f> topExits;
	std::vector<sf::Vector2f> bottomExits;

	std::vector<Block> visibleTiles;
	std::vector<Block> visibleBackgroundSprites;
	std::vector<Block> hitboxSprites;
	std::vector<Block> backgroundSprites;
	std::vector<Block> spikes;

	sf::RectangleShape transitionScreen;
};


#endif
