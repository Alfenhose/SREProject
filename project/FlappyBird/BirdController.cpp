//
// Created by Morten Nobel-Jørgensen on 19/10/2017.
//

#include <SDL_events.h>
#include <iostream>
#include "BirdController.hpp"
#include "GameObject.hpp"
#include "SpriteComponent.hpp"
#include "PhysicsComponent.hpp"
#include "BirdGame.hpp"
#include "SpriteComponent.hpp"

std::shared_ptr<PhysicsComponent> phys;
bool buttonDown = false;

BirdController::BirdController(GameObject *gameObject) : Component(gameObject) {
    // initiate bird physics
	phys = gameObject->getComponent <PhysicsComponent>();
	phys->setLinearVelocity(glm::vec2(1, 0));
	alive = true;
}

void BirdController::update(float DeltaTime) {

}

bool BirdController::onKey(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN){
        std::cout << "some key pressed" << std::endl;
		if (event.key.keysym.sym == SDLK_SPACE) {
			if (!buttonDown) {
				phys->addImpulse(glm::vec2(0, 0.12f));
				buttonDown = true;
			}
		}
    } else if (event.type == SDL_KEYUP){
        std::cout << "some key released" << std::endl;
		if (event.key.keysym.sym == SDLK_SPACE) {
			buttonDown = false;
		}
    }
    return false;
}

void BirdController::onCollisionStart(PhysicsComponent *comp) {
	if (comp->getGameObject()->name == "Wall top" || comp->getGameObject()->name == "Wall bottom") {
		alive = false;
	}
	if (comp->getGameObject()->name == "Coin") {
		auto sprite = comp->getGameObject()->getComponent<SpriteComponent>();
		comp->getGameObject()->removeComponent(sprite);
		//auto physics = comp->getGameObject()->getComponent<PhysicsComponent>();
		//comp->getGameObject()->removeComponent(physics);
	}
    std::cout << "bird collided with something" << std::endl;
}

void BirdController::onCollisionEnd(PhysicsComponent *comp) {

}


