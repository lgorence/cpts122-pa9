#include "GameObject.h"
#include "Game.h"

GameObject::GameObject() {
	mOutOfBounds = false;
}

GameObject::~GameObject() {
}

void GameObject::initInternal() {
	init();

	for (auto child : children) {
		child->initInternal();
	}
}

bool GameObject::getOutOfBounds()
{
	return mOutOfBounds;
}

void GameObject::updateInternal(double deltaTime) {
	update(deltaTime);

	for (auto child : children) {
		if (!child->isDisposed()) {
			child->updateInternal(deltaTime);
		} else {
			delete child;
		}
	}
}

void GameObject::draw(sf::Drawable &drawable) {
	game->getWindow()->draw(drawable);
}

Game *GameObject::getGame() {
	return game;
}

void GameObject::setGame(Game *game) {
	this->game = game;
}

void GameObject::addChildGameObject(GameObject *gameObject) {
	gameObject->setGame(game);
	gameObject->init();
	children.push_back(gameObject);
}

void GameObject::dispose() {
	disposed = true;
}

bool GameObject::isDisposed() {
	return disposed;
}
