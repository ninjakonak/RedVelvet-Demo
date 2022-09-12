#include<SFML/Graphics.hpp>
#pragma once
#ifndef SHADERCLASS_H
#define SHADERCLASS_H

class ShaderClass
{
public:
	void update(sf::Vector2f playerCoordinates, sf::Vector2f offsetPos, sf::Shader* shader);
	void render(sf::Shader* shader);
	void initMask();

	
	ShaderClass(sf::Vector2f playerCoordinates, const float* lightMap, std::string glslPlayer, std::string glslMap, sf::Vector2f offsetPos, sf::RenderWindow *window, sf::Shader* shader);
	
	sf::RenderWindow* window;
	//sf::Shader characterShader;
	sf::Vector2f playerCoordinates;
	sf::Vector2f offsetPos;

	const float* lightMap;

	std::string GLSL_MAP_VARIABLE_NAME;
	std::string GLSL_PLAYER_VARIABLE_NAME;

	sf::RectangleShape mask;
};

#endif
