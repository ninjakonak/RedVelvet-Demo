#pragma once
#ifndef PLAYER2_H
#define PLAYER2_H
#include<iostream>
#include<vector>
#include<format>
#include<ctime>
#include<string>
#include"Animator.h"
#include"ShaderClass.h"


#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>
#include<fstream>
#include<json/json.h>
#include"Timer.h"



class Player
{

public:

	Player();
	virtual ~Player();

	void SetMap(std::vector<sf::Sprite> hitboxSprites, const sf::Texture* spikeTxt, int mapIndexX, int mapIndexY, int mapIncX, int mapIncY);
	void SetBeginningCoordinates(float x, float y);
	void SetExits(std::vector<sf::Vector2f> leftExits, std::vector<sf::Vector2f> rightExits, std::vector<sf::Vector2f> upExits, std::vector<sf::Vector2f> downExits);
	void InitVariables();
	void SetWindow(sf::RenderWindow* window);

	sf::Vector2i getMapIndexes();
	sf::Vector2i getMapIncrements();

	int width = 36;
	int height = 48;

	sf::Vector2f offsetPos;

	void Input();
	void Move();
	void InitPlayerSprite();
	void InitPlayerTexture();
	void ChangeTexture();
	bool Collide(float x1, float x2, float y1, float y2, int width1, int width2, int height1, int height2);
	void Horizontal_Collisions();
	void Vertical_Collisions();
	void Draw();
	void ApplyGravity();
	void Update();
	void UpdateCamera();
	bool CheckExits();
	bool CheckForIdle();
	void Death();

	
	
private:
	sf::RenderWindow* window;

	sf::Vector2f playerCoordinates;
	sf::Vector2f playerBeginningCoordinates;

	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	sf::RectangleShape playerHitbox;

	int tileSize = 20;

	int screen_height = 960;
	int screen_width = 960;

	int mapIndexX;
	int mapIndexY;

	int mapIncX;
	int mapIncY;

	std::vector<sf::Sprite> hitboxSprites;
	const sf::Texture* spikeTxt;

	std::vector<sf::Vector2f> leftExits;
	std::vector<sf::Vector2f> rightExits;
	std::vector<sf::Vector2f> topExits;
	std::vector<sf::Vector2f> bottomExits;
	
	float moveSpeed;

	bool goingLeft;
	bool goingRight;

	bool canJump;
	float jumpSpeed;
	float GravitationalForce;
	
	bool canSlide;
	bool sliding;
	void DisableSliding();
	void EnableSliding();
	void CheckSliding();


	void CheckWalking();
	void CheckJumping();

	void LockMovement(bool x);
	bool movementLocked;

	float vectorX;
	float vectorY;

	float accelerationSpeed;
	float stopSpeed;

	bool spaceBarPressed;

	float frameIndex = 0;

	int direction = 1;

	float halfWidth = this->screen_width / 2;
	float halfHeight = this->screen_height / 2;

	sf::Vector2f cameraFrame;
	
	float cameraReturnSpeed;

	float YLevelLimit = 180*22;

	EngineUtils::Timer* jumpTimer = EngineUtils::Timer::Instance();
	EngineUtils::Timer* groundTimer = EngineUtils::Timer::Instance();

	
	std::vector<std::string> framesIdleLeft =
	{
		"graphics/character_frames/left_idle/velvet_idle1.png",
		"graphics/character_frames/left_idle/velvet_idle1.png",
		"graphics/character_frames/left_idle/velvet_idle1.png",
		"graphics/character_frames/left_idle/velvet_idle1.png",
		"graphics/character_frames/left_idle/velvet_idle2.png",
		"graphics/character_frames/left_idle/velvet_idle2.png",
		"graphics/character_frames/left_idle/velvet_idle3.png",
		"graphics/character_frames/left_idle/velvet_idle4.png",
		"graphics/character_frames/left_idle/velvet_idle4.png",
		"graphics/character_frames/left_idle/velvet_idle4.png",
		"graphics/character_frames/left_idle/velvet_idle4.png",
		"graphics/character_frames/left_idle/velvet_idle3.png",
		"graphics/character_frames/left_idle/velvet_idle2.png",
		"graphics/character_frames/left_idle/velvet_idle2.png",
		"graphics/character_frames/left_idle/velvet_idle1.png",
		"graphics/character_frames/left_idle/velvet_idle1.png",
		"graphics/character_frames/left_idle/velvet_idle1.png",
		"graphics/character_frames/left_idle/velvet_idle1.png"
	};



	std::vector<std::string> framesIdleRight =
	{
		"graphics/character_frames/right_idle/velvet_idle1.png",
		"graphics/character_frames/right_idle/velvet_idle1.png",
		"graphics/character_frames/right_idle/velvet_idle1.png",
		"graphics/character_frames/right_idle/velvet_idle1.png",
		"graphics/character_frames/right_idle/velvet_idle2.png",
		"graphics/character_frames/right_idle/velvet_idle2.png",
		"graphics/character_frames/right_idle/velvet_idle3.png",
		"graphics/character_frames/right_idle/velvet_idle4.png",
		"graphics/character_frames/right_idle/velvet_idle4.png",
		"graphics/character_frames/right_idle/velvet_idle4.png",
		"graphics/character_frames/right_idle/velvet_idle4.png",
		"graphics/character_frames/right_idle/velvet_idle3.png",
		"graphics/character_frames/right_idle/velvet_idle2.png",
		"graphics/character_frames/right_idle/velvet_idle2.png",
		"graphics/character_frames/right_idle/velvet_idle1.png",
		"graphics/character_frames/right_idle/velvet_idle1.png",
		"graphics/character_frames/right_idle/velvet_idle1.png",
		"graphics/character_frames/right_idle/velvet_idle1.png"
	};

	std::vector<std::string> framesWalkRight =
	{
		"graphics/character_frames/right_walk/velvetrun1.png",
		"graphics/character_frames/right_walk/velvetrun2.png",
		"graphics/character_frames/right_walk/velvetrun3.png",
		"graphics/character_frames/right_walk/velvetrun4.png",
		"graphics/character_frames/right_walk/velvetrun5.png",
		"graphics/character_frames/right_walk/velvetrun6.png"
	};

	std::vector<std::string> framesWalkLeft =
	{
		"graphics/character_frames/left_walk/velvetrun1.png",
		"graphics/character_frames/left_walk/velvetrun2.png",
		"graphics/character_frames/left_walk/velvetrun3.png",
		"graphics/character_frames/left_walk/velvetrun4.png",
		"graphics/character_frames/left_walk/velvetrun5.png",
		"graphics/character_frames/left_walk/velvetrun6.png"
	};

	std::vector<std::string> framesFallLeft =
	{
		"graphics/character_frames/jump_left/jump_frame4.png",
		"graphics/character_frames/jump_left/jump_frame5.png",
	};

	std::vector<std::string> framesFallRight =
	{
		"graphics/character_frames/jump_right/jump_frame4.png",
		"graphics/character_frames/jump_right/jump_frame5.png",
	};

	std::vector<std::string> framesJumpRight =
	{
		"graphics/character_frames/jump_right/jump_frame1.png",
		"graphics/character_frames/jump_right/jump_frame2.png",
		"graphics/character_frames/jump_right/jump_frame3.png"
	};

	std::vector<std::string> framesJumpLeft =
	{
		"graphics/character_frames/jump_left/jump_frame1.png",
		"graphics/character_frames/jump_left/jump_frame2.png",
		"graphics/character_frames/jump_left/jump_frame3.png"

	};

	std::vector<std::string> framesSlideLeft = 
	{
		"graphics/character_frames/slide_left/slide_frame1.png",
		"graphics/character_frames/slide_left/slide_frame1.png",
		"graphics/character_frames/slide_left/slide_frame2.png",
		"graphics/character_frames/slide_left/slide_frame2.png",
		"graphics/character_frames/slide_left/slide_frame2.png",
		"graphics/character_frames/slide_left/slide_frame3.png",
		"graphics/character_frames/slide_left/slide_frame3.png",
		"graphics/character_frames/slide_left/slide_frame3.png",
	};

	std::vector<std::string> framesSlideRight =
	{
		"graphics/character_frames/slide_right/slide_frame1.png",
		"graphics/character_frames/slide_right/slide_frame1.png",
		"graphics/character_frames/slide_right/slide_frame2.png",
		"graphics/character_frames/slide_right/slide_frame2.png",
		"graphics/character_frames/slide_right/slide_frame2.png",
		"graphics/character_frames/slide_right/slide_frame3.png",
		"graphics/character_frames/slide_right/slide_frame3.png",
		"graphics/character_frames/slide_right/slide_frame3.png",
	};

	Animator slidingAnimation = Animator(this->framesSlideRight, this->framesSlideLeft, false, (float)0.1);
	Animator walking = Animator(this->framesWalkRight, this->framesWalkLeft, true, (float)0.1);
	Animator idle = Animator(this->framesIdleRight, this->framesIdleLeft, true, (float)0.1);
	Animator fallAnimation = Animator(this->framesFallRight, this->framesFallLeft, false, (float)0.1);
	Animator jumpAnimation = Animator(this->framesJumpRight, this->framesJumpLeft, false, (float)0.1);

	void ParseJSON();
	void MoveCamera();
	
	std::ifstream dataFile;
	Json::Value jsonData;
	Json::Reader jsonReader;



	

};

#endif

