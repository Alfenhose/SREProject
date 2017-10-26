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

BirdController::BirdController(GameObject *gameObject) : Component(gameObject) {
    // initiate bird physics
	phys = gameObject->getComponent <PhysicsComponent>();
	phys->setLinearVelocity(glm::vec2(0.5, 0));
	
}

bool BirdController::onKey(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN){
        std::cout << "some key pressed" << std::endl;
		if (event.key.keysym.sym == SDLK_SPACE) {
			phys->addImpulse(glm::vec2(0, 0.5f));
		}
    } else if (event.type == SDL_KEYUP){
        std::cout << "some key released" << std::endl;
    }
    return false;
}

void BirdController::onCollisionStart(PhysicsComponent *comp) {
    std::cout << "bird collided with something" << std::endl;
}

void BirdController::onCollisionEnd(PhysicsComponent *comp) {

}


