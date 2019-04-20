#pragma once

#include "GameObject.h"
#include <math.h>

class Ship : public GameObject
{
	float mFacing;
	float mMoveSpeed;
	float x = 0;
	float y = 0;
	sf::Vector2f mBoundary;

	sf::Sprite shipSprite;
	sf::Texture shipTexture;
	sf::Clock shootClock;

public:
	Ship();
	~Ship();

	void moveForward(double deltaTime);
	void turnLeft();
	void turnRight();
	void fire();

	void init();
	void update(double deltaTime);
	void setOutOfBounds();
	sf::FloatRect getBounds();

	/*=====================
	Notes:
	* Does control input need to be in here? If so should they be in update or the functions themselves?
	* Need information on setOutOfBounds
	* Where do we initialize the ship and other objects?
	* DeltaTime * moving X and Y?
	=====================*/
};