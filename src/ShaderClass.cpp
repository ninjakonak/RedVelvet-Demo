#include "../include/ShaderClass.h"
#include<iostream>

ShaderClass::ShaderClass(sf::Vector2f playerCoordinates, const float* lightMap, std::string glslPlayer, std::string glslMap, sf::Vector2f offsetPos, sf::RenderWindow* window, sf::Shader* shader) {
	this->window = window;
	shader->loadFromFile("PlayerShader.frag", sf::Shader::Fragment);
	this->lightMap = lightMap;
	this->playerCoordinates = playerCoordinates;
	this->offsetPos = offsetPos;

	this->GLSL_MAP_VARIABLE_NAME = glslMap;
	this->GLSL_PLAYER_VARIABLE_NAME = glslPlayer;

#pragma warning(suppress : 4996)
	shader->setUniform(this->GLSL_PLAYER_VARIABLE_NAME, this->playerCoordinates);
	//#pragma warning(suppress : 4996)
		//this->characterShader.setUniformArray(GLSL_MAP_VARIABLE_NAME, this->lightMap, sizeof(this->lightMap));
	this->initMask();
	
}

void ShaderClass::update(sf::Vector2f playerCoordinates, sf::Vector2f offsetPos, sf::Shader* shader) {
	this->playerCoordinates = playerCoordinates;
	this->offsetPos = offsetPos;
#pragma warning(supress: 4996)
	shader->setUniform(this->GLSL_PLAYER_VARIABLE_NAME, this->playerCoordinates);
}

void ShaderClass::render(sf::Shader* shader) {
	//this->window->draw(this->mask, shader);
}

void ShaderClass::initMask() {
	this->mask.setSize(sf::Vector2f(960, 960));
	this->mask.setPosition(0, 0);
	this->mask.setFillColor(sf::Color::Black);
}






