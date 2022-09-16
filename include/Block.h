#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>
class Block:public sf::Sprite
{

public:
	Block();
	

	

	void setTexturePath(std::string texturePath);

	virtual ~Block();

	bool texturePathInitiated = false;

	
	
	int width;
	int height;

	float x;
	float y;

	std::string texturePath;

	sf::Texture* texture = new sf::Texture;

	

private:
	
	void LoadTextures();


};

#endif