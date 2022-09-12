#include "../include/Player.h"


void Player::SetMap(std::vector<sf::Sprite> hitboxSprites, const sf::Texture* spikeTxt, int mapIndexX, int mapIndexY, int mapIncX, int mapIncY) {
	this->hitboxSprites = hitboxSprites;
	this->spikeTxt = spikeTxt;
	
	
	this->mapIndexX = mapIndexX;
	this->mapIndexY = mapIndexY;
	this->mapIncX = mapIncX;
	this->mapIncY = mapIncY;
}

void Player::SetBeginningCoordinates(float x, float y) {
	this->playerBeginningCoordinates.x = x;
	this->playerBeginningCoordinates.y = y;
	this->playerCoordinates.x = this->playerBeginningCoordinates.x;
	this->playerCoordinates.y = this->playerBeginningCoordinates.y;
}

void Player::SetExits(std::vector<sf::Vector2f> leftExits, std::vector<sf::Vector2f> rightExits, std::vector<sf::Vector2f> upExits, std::vector<sf::Vector2f> downExits) {
	this->leftExits = leftExits;
	this->rightExits = rightExits;
	this->topExits = upExits;
	this->bottomExits = downExits;
}

void Player::SetWindow(sf::RenderWindow* window) {
	this->window = window;
}

sf::Vector2i Player::getMapIndexes() {
	return sf::Vector2i(this->mapIndexX, this->mapIndexY);
}

sf::Vector2i Player::getMapIncrements() {
	return sf::Vector2i(this->mapIncX, this->mapIncY);
}

Player::Player() {
	this->InitVariables();
	this->InitPlayerTexture();
	this->InitPlayerSprite();
}

Player::~Player(){

}

void Player::InitVariables() {
	this->ParseJSON();
	this->moveSpeed = 4;
	this->jumpSpeed = 14;
	this->goingLeft = false;
	this->goingRight = false;
	this->canJump = false;
	this->GravitationalForce = 0.5f;
	this->spaceBarPressed = false;
	this->cameraFrame.x = 0;
	this->cameraFrame.y = 0;
	this->cameraReturnSpeed = 0;
	this->accelerationSpeed = 1;
	this->stopSpeed = 0.5f;
	this->canSlide = true;
	this->sliding = false;
	this->movementLocked = false;
}




void Player::Move() {
	this->Input();
	this->playerCoordinates.x += this->vectorX;
	this->Horizontal_Collisions();
	this->ApplyGravity();
	this->Vertical_Collisions();

	if (this->playerCoordinates.y > this->YLevelLimit) {
		this->Death();
		std::cout << "fell down";
	}

	
	this->playerHitbox.setPosition(this->playerCoordinates.x, this->playerCoordinates.y);
	
	if (!this->vectorY == 0) {
		this->groundTimer->Tick();
	}

	if (!this->canJump) {
		this->jumpTimer->Tick();
		//std::cout << this->jumpTimer->DeltaTime()<<"\n";
	}
}


void Player::Input() {
	
	this->CheckWalking();
	this->CheckJumping();
	this->CheckSliding();

}

void Player::CheckSliding() {
	if (this->sliding) {
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
			this->DisableSliding();
			this->vectorX = 0;
		}
		else {
			if (this->vectorY > 0) {
				this->DisableSliding();
				this->vectorX = 0;
			}
			if (this->vectorX != 0) {
				//this->vectorX > 0 ? this->vectorX -= 0.1f : this->vectorX += 0.1f;
				if (this->direction == 1) {
					this->vectorX -= 0.02f;
					if (this->vectorX <= 0) {
						this->vectorX = 0;
					}
				}
				else {
					this->vectorX += 0.02f;
					if (this->vectorX >= 0) {
						this->vectorX = 0;
					}
				}
			}
		}
	}
}

void Player::CheckJumping() {


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->canJump && this->vectorY == 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->groundTimer->DeltaTime() <= 0.1 && this->vectorY > 0 && !this->movementLocked) {
		if (!this->spaceBarPressed) {

			this->canJump = false;
			this->vectorY -= this->jumpSpeed;
			this->spaceBarPressed = true;

			if (this->sliding) {
				this->DisableSliding();
				this->canJump = false;
				this->vectorY += 4;
				if (this->vectorX < 6 && this->vectorX>-6) {
					this->vectorX *= 4;
				}
			}
		}




	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->canJump == true) {
		this->spaceBarPressed = false;

	}



	if (this->vectorY < 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		this->vectorY = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		this->Death();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) && this->canSlide && this->canJump) {
		this->EnableSliding();
	}
}

void Player::CheckWalking() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !this->movementLocked) {
		this->goingLeft = true;
		if (!this->direction == 0 && !this->goingRight && !this->sliding)
			this->direction = 0;



	}
	else {
		this->goingLeft = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !this->movementLocked) {
		this->goingRight = true;

		if (!this->goingLeft && !this->direction == 1 && !this->sliding)
			this->direction = 1;



	}
	else {
		this->goingRight = false;
	}



	if (this->goingLeft) {

		if (this->vectorX > -this->moveSpeed && !this->sliding) {
			this->vectorX -= this->accelerationSpeed;

		}

		if (this->vectorX < -this->moveSpeed) {
			this->vectorX += 0.25;
			if (this->vectorX > -this->moveSpeed) {
				this->vectorX = -this->moveSpeed;
			}
		}
	}

	if (this->goingRight) {


		if (this->vectorX < this->moveSpeed && !this->sliding) {
			this->vectorX += this->accelerationSpeed;
		}

		if (this->vectorX > this->moveSpeed) {
			this->vectorX -= 0.25;
			if (this->vectorX < this->moveSpeed) {
				this->vectorX = this->moveSpeed;
			}
		}
	}

	if (!this->goingRight && !this->goingLeft) {
		if (this->vectorX > 0) {
			this->vectorX -= this->stopSpeed;
			if (this->vectorX < 0) {
				this->vectorX = 0;
			}
		}
		if (this->vectorX < 0) {
			this->vectorX += this->stopSpeed;
			if (this->vectorX > 0) {
				this->vectorX = 0;
			}
		}
	}

	if (this->goingRight && this->goingLeft) {
		if (this->vectorX > 0) {
			this->vectorX -= this->stopSpeed;
		}
		if (this->vectorX < 0 && !this->sliding) {
			this->vectorX += this->stopSpeed;
		}
	}
}

void Player::EnableSliding() {
	this->sliding = true;
	this->canSlide = false;
	this->playerSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(48, 36)));
	this->height = 36;
	this->playerCoordinates.y += 12;
}

void Player::DisableSliding() {
	this->sliding = false;
	this->canSlide = true;
	this->height = 48;
	this->playerCoordinates.y -= 12;
	this->playerSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(36, 48)));
	this->slidingAnimation.reset();
}

void Player::ApplyGravity() {
	if (this->vectorY < 20)
		this->vectorY += this->GravitationalForce;
	this->playerCoordinates.y += this->vectorY;
}

bool Player::Collide(float x1, float x2, float y1, float y2, int width1, int width2, int height1, int height2) {
	return (x1 + width1 > x2 && x1<x2 + width2 && y1 + height1>y2 && y1 < y2 + height2);
}

void Player::Horizontal_Collisions() {
	for (auto& tile : this->hitboxSprites) {
		
		if (this->Collide(this->playerCoordinates.x, tile.getPosition().x, this->playerCoordinates.y, tile.getPosition().y, this->width, this->tileSize, this->height, this->tileSize)) {

			if (this->vectorX > 0) {
				this->playerCoordinates.x = tile.getPosition().x - this->width;
			}

			if (this->vectorX < 0) {
				this->playerCoordinates.x = tile.getPosition().x + this->tileSize;
			}

			if (tile.getTexture() == this->spikeTxt) {
				this->Death();
			}
			

		}
	}
	
}

void Player::Vertical_Collisions() {
	for (auto& tile : this->hitboxSprites) {
		
		if (this->Collide(this->playerCoordinates.x, tile.getPosition().x, this->playerCoordinates.y, tile.getPosition().y, this->width, this->tileSize, this->height, this->tileSize)) {

			if (this->vectorY > 0) {
				this->playerCoordinates.y = tile.getPosition().y - this->height;
				this->vectorY = 0;
				this->canJump = true;
				this->groundTimer->Reset();
				if (this->cameraFrame.y > 0) {
					this->cameraFrame.y -= cameraReturnSpeed;
					this->cameraReturnSpeed += 0.5;
				}
				else {
					this->cameraFrame.y = 0;
					this->cameraReturnSpeed = 0;
				}

			}

			if (this->vectorY < 0) {
				this->playerCoordinates.y = tile.getPosition().y + this->tileSize;
				this->vectorY = 0;
			}

			if (tile.getTexture() == this->spikeTxt) {
				this->Death();
			}
			

		}
		
	}
}

void Player::Draw() {
	this->window->draw(this->playerSprite);
}


void Player::InitPlayerTexture() {
	if (!this->playerTexture.loadFromFile("graphics/character_frames/right_idle/velvet_idle1.png")) {
		std::cout << "error";
	}
}

void Player::InitPlayerSprite() {
	this->playerSprite.setTexture(this->playerTexture);
}

bool Player::CheckForIdle() {
	if (this->vectorY == 0 && this->vectorX == 0)
		return true;
	else
		return false;
}

void Player::ChangeTexture() {


	if (this->CheckForIdle() && this->vectorY == 0 && !this->sliding) {
		this->playerTexture.loadFromFile(this->idle.changeFrame(this->direction));
	}

	if (!this->CheckForIdle() && this->vectorY == 0&& !this->sliding) {
		this->playerTexture.loadFromFile(this->walking.changeFrame(this->direction));
	}

	if (this->sliding) {
		this->playerTexture.loadFromFile(this->slidingAnimation.changeFrame(this->direction));
	}

	if (this->vectorY > 0) {
		this->playerTexture.loadFromFile(this->fallAnimation.changeFrame(this->direction));
	}
	else {
		this->fallAnimation.reset();
	}

	if (this->vectorY < 0) {
		this->playerTexture.loadFromFile(this->jumpAnimation.changeFrame(this->direction));
	}
	else {
		this->jumpAnimation.reset();
	}

}

void Player::Update() {
	this->Move();
	this->ChangeTexture();
	this->UpdateCamera();
}

void Player::MoveCamera() {
	this->cameraFrame.x = this->vectorX/2.5;

	if (this->vectorY > 0) {
		this->cameraFrame.y += 0.1f;//sqrt(sqrt(this->vectorY));
	}

	if (this->vectorY < 0) {
		//this->cameraFrame.y -= 0.25f;
		this->cameraFrame.y = sqrt((this->vectorY + (this->jumpSpeed / 2)) * (this->vectorY + (this->jumpSpeed / 2)))/5;
	}
	
}

void Player::UpdateCamera() {
	
	this->MoveCamera();
	
	
	
	
	this->offsetPos.x = this->playerHitbox.getPosition().x - this->halfWidth + this->cameraFrame.x;
	this->offsetPos.y = this->playerHitbox.getPosition().y - this->halfHeight - this->cameraFrame.y;

	
	
	

	this->playerSprite.setPosition(this->playerCoordinates.x - this->offsetPos.x, this->playerCoordinates.y - this->offsetPos.y);


}

bool Player::CheckExits() {

	for (auto& exit : this->leftExits) {
		if (this->Collide(this->playerCoordinates.x, exit.x, this->playerCoordinates.y, exit.y, this->width, this->tileSize, this->height, this->tileSize)) {
			this->mapIncX = -1;
			this->mapIndexX += this->mapIncX;
			this->playerCoordinates = this->playerBeginningCoordinates;
			return true;
		}
	}

	for (auto& exit : this->rightExits) {
		if (this->Collide(this->playerCoordinates.x, exit.x, this->playerCoordinates.y, exit.y, this->width, this->tileSize, this->height, this->tileSize)) {
			this->mapIncX = 1;
			this->mapIndexX += this->mapIncX;
			this->playerCoordinates = this->playerBeginningCoordinates;
			return true;

		}
	}

	for (auto& exit : this->topExits) {
		if (this->Collide(this->playerCoordinates.x, exit.x, this->playerCoordinates.y, exit.y, this->width, this->tileSize, this->height, this->tileSize)) {
			this->mapIncY = -1;
			this->mapIndexY += this->mapIncY;
			this->playerCoordinates = this->playerBeginningCoordinates;
			this->vectorY -= (this->jumpSpeed / 2);
			return true;

		}
	}

	for (auto& exit : this->bottomExits) {
		if (this->Collide(this->playerCoordinates.x, exit.x, this->playerCoordinates.y, exit.y, this->width, this->tileSize, this->height, this->tileSize)) {
			this->mapIncY = 1;
			this->mapIndexY += this->mapIncY;
			this->playerCoordinates = this->playerBeginningCoordinates;
			return true;
		}
	}

	return false;

}

void Player::ParseJSON() {
	this->dataFile = std::ifstream("GameData.json");

	jsonReader.parse(this->dataFile, this->jsonData);
	
	/*
	Json::Value event;
	Json::Value vec(Json::arrayValue);
	vec.append(Json::Value(1));
	vec.append(Json::Value(2));
	vec.append(Json::Value(3));

	event["competitors"]["home"]["name"] = "Liverpool";
	event["competitors"]["away"]["code"] = 89223;
	event["competitors"]["away"]["name"] = "Aston Villa";
	event["competitors"]["away"]["code"] = vec;

	std::ofstream file_id;
	file_id.open("GameData.json");

	

	Json::StyledWriter styledWriter;
	file_id << styledWriter.write(event);

	file_id.close();

	std::cout << event << std::endl;
	
	*/

	
	
}

void Player::Death() {
	this->playerCoordinates.x = this->playerBeginningCoordinates.x;
	this->playerCoordinates.y = this->playerBeginningCoordinates.y;
}

void Player::LockMovement(bool x) {
	x ? this->movementLocked = true : this->movementLocked = false;
}