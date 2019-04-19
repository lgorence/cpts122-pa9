#pragma once

#include "GameObject.h"
#include "Game.h"
#include "Enemies.h"

/**********************************************************
*  ASTEROID CLASS
* GameObject -> Enemies -> Asteroid
* This class is used for the Asteroid-type enemy.  They spawn at an
* increasing rate from any window border, travel at varying speeds
* across the screen. Collision with the player destroys the
* player.  Collision with "friendly"-type bullets destroys
* the asteroid and grants points to the player.
**********************************************************/

class Asteroid : public Enemies
{
	sf::Vector2f mMoveVector;
	sf::Vector2f mSpawnPoint;
	int mSpawnWall;
	sf::Texture asteroidTexture;
	sf::Sprite asteroidSprite;
	double offset = 0;
	bool spinDirection;
	int spinScale;

	int randomSigned();

public:
	Asteroid();
	~Asteroid();

	void init();
	void update(double deltaTime);
	void setOutOfBounds();
	void setMoveVector();
	void setSpawnPoint();
	void setSpawnWall();
};
