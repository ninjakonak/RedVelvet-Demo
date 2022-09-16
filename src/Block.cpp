#include "../include/Block.h"
#include "../include/constants.h"


void Block::LoadTextures() {
	this->texture->loadFromFile(this->texturePath);
	this->setTexture(*this->texture);
}

Block::Block() {

}

void Block::setTexturePath(std::string texturePath) {
	this->texturePath = texturePath;
	this->texturePathInitiated = true;

	this->width = TILE_WIDTH;
	this->height = TILE_HEIGHT;

	this->LoadTextures();
}


Block::~Block() {
	
}
