#include "Asteroid.h"

#include <iostream>
#include <math.h>

Asteroid::Asteroid(double offset) : offset(offset) {
}

Asteroid::~Asteroid() {
}

void Asteroid::init() {
	setSpawnWall();//randomly choose top/left/bottom/right window border
	setSpawnPoint();//choose random location on the spawn wall
	setMoveVector();//set a random vector that travels at some angle into the room
	circleShape = sf::CircleShape(35.0f);
	circleShape.setFillColor(sf::Color::White);
	circleShape.setPosition(mSpawnPoint);
	circleShape.setOrigin(
		circleShape.getRadius(),
		circleShape.getRadius()
	);
}

void Asteroid::update(double deltaTime) {
	offset += deltaTime;
	float sin = sinf(offset);
	float cos = cosf(offset);

	circleShape.move(mMoveVector);

	sf::Color color = circleShape.getFillColor();
	color.r = (int)(255 * abs(sin));
	color.g = (int)(255 * abs(cos));
	color.b = (int)(255 * abs(sin));
	circleShape.setFillColor(color);

	draw(circleShape);
}

void Asteroid::setMoveVector()
{
	//the ratio of the first term in each vector value (x,y) determines the angle, second term sets the speed
	//and randomSigned() allows the angle to randomly be up/down or left/right depending on the wall spawning the object
	
	const int asteroidSpeed = 2000; // use to adjust asteroid speed, larger speed value = slower asteroid movement speed
	int asteroidAngle = (rand() % 4) + 1;//sets a random trajectory for the asteroid

	switch (mSpawnWall)
	{
	case 0://spawn from left wall
		mMoveVector = sf::Vector2f((asteroidAngle)*(1 / asteroidSpeed + 1),
			(asteroidAngle)*(1 / asteroidSpeed + 1)*(randomSigned()));
		break;
	case 1://spawn from top wall
		mMoveVector = sf::Vector2f((asteroidAngle)*(1 / asteroidSpeed + 1)*(randomSigned()),
			(asteroidAngle)*(1 / asteroidSpeed + 1));
		break;
	case 2://spawn from right wall
		mMoveVector = sf::Vector2f((asteroidAngle)*(1 / asteroidSpeed + 1)* -1 ,
			(asteroidAngle)*(1 / asteroidSpeed + 1)*(randomSigned()));
		break;
	case 3://spawn from bottom wall
		mMoveVector = sf::Vector2f((asteroidAngle)*(1 / asteroidSpeed + 1)*(randomSigned()),
			(asteroidAngle)*(1 / asteroidSpeed + 1) * -1);
		break;
	default:
		mMoveVector = sf::Vector2f(0, 0);
		break;
	}
}

void Asteroid::setSpawnPoint()
{
	sf::Vector2u windowSize = this->getGame()->getWindow()->getSize();

	switch (mSpawnWall)
	{
	case 0://spawn from left wall
		mSpawnPoint = sf::Vector2f(0, rand() % windowSize.y);
		break;
	case 1://spawn from top wall
		mSpawnPoint = sf::Vector2f(rand() % windowSize.x , 0);
		break;
	case 2://spawn from right wall
		mSpawnPoint = sf::Vector2f(windowSize.x, rand() % windowSize.y);
		break;
	case 3://spawn from bottom wall
		mSpawnPoint = sf::Vector2f(rand() % windowSize.x, windowSize.y);
		break;
	default:
		mSpawnPoint = sf::Vector2f(0, 0);
		break;
	}
}

void Asteroid::setSpawnWall() {
	mSpawnWall = rand() % 4;
}

void Asteroid::setOutOfBounds()
{
	const sf::Vector2f currentPos = this->circleShape.getPosition();
	const sf::Vector2u windowBounds = this->getGame()->getWindow()->getSize();
	const int offset = 10;

	if (currentPos.x < 0 - offset)
	{
		mOutOfBounds = true;
	}
	else if (currentPos.x > windowBounds.x + offset)
	{
		mOutOfBounds = true;
	}
	else if (currentPos.y < 0 - offset)
	{
		mOutOfBounds = true;
	}
	else if (currentPos.y > windowBounds.y + offset)
	{
		mOutOfBounds = true;
	}

}

int Asteroid::randomSigned() {
	int flip = rand() % 2;

	if (flip == 0)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}
