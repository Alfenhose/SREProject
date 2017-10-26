//
// Created by Morten Nobel-Jørgensen on 12/09/2017.
//

#include <glm/gtx/rotate_vector.hpp>
#include "SpaceShip.hpp"
#include "sre/Renderer.hpp"
#include "GameObject.hpp"
#include "Laser.hpp"
#include "AsteroidsGame.hpp"
#include "Bang.hpp"
using namespace sre;


SpaceShip::SpaceShip(const sre::Sprite &sprite, AsteroidsGame* _game) : GameObject(sprite) {
    scale = glm::vec2(0.5f,0.5f);
    winSize = sre::Renderer::instance->getWindowSize();
    radius = 23;
    position = winSize * 0.5f;
	cooldown = 0;
	cooldownMax = 1;
	type = type_ship;
	game = _game;
	game->shipAlive = true;
}

void SpaceShip::update(float deltaTime) {
    if (thrust){
        float acceleration = deltaTime*thrustPower;
        glm::vec2 direction = glm::rotateZ(glm::vec3(0,acceleration,0), glm::radians(rotation));
        velocity += direction;
        float speed = glm::length(velocity);
        if (speed > maxSpeed){
            velocity = velocity * (maxSpeed / speed);
        }
    } else {
        velocity = velocity * (1.0f - drag*deltaTime);
    }
	cooldown -= deltaTime;
    position += velocity * deltaTime;
    if (rotateCCW){
        rotation += deltaTime * rotationSpeed;
    }
    if (rotateCW){
        rotation -= deltaTime * rotationSpeed;
    }

    // wrap around
    if (position.x < 0){
        position.x += winSize.x;
    } else if (position.x > winSize.x){
        position.x -= winSize.x;
    }
    if (position.y < 0){
        position.y += winSize.y;
    } else if (position.y > winSize.y){
        position.y -= winSize.y;
    }
}

void SpaceShip::onCollision(std::shared_ptr<GameObject> other) {
	if (other->alive) {
		switch (other->type) {
		case type_asteroidBig:
		case type_asteroidMed:
		case type_asteroidSmall:
			//other->alive = false;
			alive = false;
			game->gameObjectsToBeAdded.push_back(std::make_shared<Bang>(game->bangSprite, position));
			break;
		default:
			break;
		}
	}
	
}
SpaceShip::~SpaceShip() {
	game->shipAlive = false;
}

void SpaceShip::onKey(SDL_Event &keyEvent) {
    if (keyEvent.key.keysym.sym == SDLK_UP){
        thrust = keyEvent.type == SDL_KEYDOWN;
    }
    if (keyEvent.key.keysym.sym == SDLK_LEFT){
        rotateCCW = keyEvent.type == SDL_KEYDOWN;
    }
    if (keyEvent.key.keysym.sym == SDLK_RIGHT){
        rotateCW = keyEvent.type == SDL_KEYDOWN;
    }
	if (keyEvent.key.keysym.sym == SDLK_SPACE) {
		if (cooldown < 0) {

			std::shared_ptr<GameObject> temp = std::make_shared<Laser>(game->laserSprite, position, rotation);
			game->gameObjectsToBeAdded.push_back(temp);
			cooldown = cooldownMax;
		}
	}
	
	
}
