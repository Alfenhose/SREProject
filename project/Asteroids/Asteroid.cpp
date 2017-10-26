//
// Created by Morten Nobel-Jørgensen on 12/09/2017.
//

#include <glm/gtx/rotate_vector.hpp>
#include "Asteroid.hpp"
#include "sre/Renderer.hpp"
#include "AsteroidsGame.hpp"

Asteroid::Asteroid(const sre::Sprite &sprite, AsteroidsGame* _game) : GameObject(sprite) {
	game = _game;
	scale = glm::vec2(1.f, 1.f);
	winSize = sre::Renderer::instance->getWindowSize();
	radius = 50;
	type = type_asteroidBig;
	size = big;
	velocity = glm::vec2(rand() % 50 - 25, rand() % 50 - 25);
	rotationSpeed = rand() % 40 - 20;
	position = glm::vec2(rand() % (int)(winSize.x), rand() % (int)(winSize.y));
}
Asteroid::Asteroid(const sre::Sprite &sprite, AsteroidsGame* _game,sizeEnum _size, glm::vec2 pos) : GameObject(sprite) {
	game = _game;
	winSize = sre::Renderer::instance->getWindowSize();
	size = _size;
	switch (size) {
	case small:
		type = type_asteroidSmall;
		
		velocity = glm::vec2(rand() % 100 - 50, rand() % 100 - 50);
		rotationSpeed = rand() % 60 - 30;
		radius = 12;
		break;
	case med:
		type = type_asteroidMed;
		
		velocity = glm::vec2(rand() % 50 - 25, rand() % 50 - 25);
		rotationSpeed = rand() % 40 - 20;
		radius = 23;
		break;
	case big:
		type = type_asteroidBig;
		
		velocity = glm::vec2(rand() % 40 - 20, rand() % 40 - 20);
		rotationSpeed = rand() % 30 - 15;
		radius = 50;
		break;
	}
	
	
	position = pos;
}

Asteroid::~Asteroid() {
	if (game->shipAlive)
	switch (size) {
	case big:
		game->gameObjectsToBeAdded.push_back(std::make_shared<Asteroid>(game->medAsteroidSprite, game, med, position));
		game->gameObjectsToBeAdded.push_back(std::make_shared<Asteroid>(game->medAsteroidSprite, game, med, position));
		break;
	case med:
		game->gameObjectsToBeAdded.push_back(std::make_shared<Asteroid>(game->smallAsteroidSprite, game, small, position));
		game->gameObjectsToBeAdded.push_back(std::make_shared<Asteroid>(game->smallAsteroidSprite, game, small, position));
		break;
	}
}

void Asteroid::update(float deltaTime) {

	position += velocity * deltaTime;
	rotation += deltaTime * rotationSpeed;

	// wrap around
	if (position.x < 0) {
		position.x += winSize.x;
	}
	else if (position.x > winSize.x) {
		position.x -= winSize.x;
	}
	if (position.y < 0) {
		position.y += winSize.y;
	}
	else if (position.y > winSize.y) {
		position.y -= winSize.y;
	}
}

void Asteroid::onCollision(std::shared_ptr<GameObject> other) {

}