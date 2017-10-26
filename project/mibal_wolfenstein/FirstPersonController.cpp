//
// Created by Morten Nobel-Jørgensen on 29/09/2017.
//

#include <glm/gtx/rotate_vector.hpp>
#include "FirstPersonController.hpp"

using namespace sre;
using namespace glm;


FirstPersonController::FirstPersonController(sre::Camera * camera)
:camera(camera)
{
    camera->setPerspectiveProjection(45,0.1f,1000);
    position = vec3(0,0,0);
}


void FirstPersonController::update(float deltaTime){
    // todo implement
    //camera->lookAt(vec3(0,0,0), vec3(0,0,-1), vec3{0,1,0});
	glm::mat4 translationMatrix = glm::translate(position);
	glm::mat4 rotationMatrix = glm::rotate(glm::radians(rotation),glm::vec3(0,1,0));
	glm::mat4 transform = rotationMatrix * translationMatrix;
	camera->setViewTransform(transform);
	this->deltaTime = deltaTime;

	if (fwd) {
		position += vec3(-sin(radians(rotation))*speed*deltaTime, 0, cos(radians(rotation))*speed*deltaTime);
	}
	if (bwd) {
		position += vec3(sin(radians(rotation))*speed*deltaTime, 0, -cos(radians(rotation))*speed*deltaTime);
	}
	if (left) {
		position += vec3(cos(radians(rotation))*speed*deltaTime, 0, sin(radians(rotation))*speed*deltaTime);
	}
	if (right) {
		position += vec3(-cos(radians(rotation))*speed*deltaTime, 0, -sin(radians(rotation))*speed*deltaTime);
	}



}

void FirstPersonController::onKey(SDL_Event &event) {
    // Todo implement
	if (event.key.keysym.sym == SDLK_w) {
		if (event.type == SDL_KEYDOWN) {
			fwd = true;
		}
		if (event.type == SDL_KEYUP) {
			fwd = false;
		}
		//position += vec3(-sin(radians(rotation))*speed*deltaTime, 0, cos(radians(rotation))*speed*deltaTime);
	}
	if (event.key.keysym.sym == SDLK_s) {
		if (event.type == SDL_KEYDOWN) {
			bwd = true;
		}
		if (event.type == SDL_KEYUP) {
			bwd = false;
		}
		//position += vec3(sin(radians(rotation))*speed*deltaTime, 0, -cos(radians(rotation))*speed*deltaTime);
	}
	if (event.key.keysym.sym == SDLK_a) {
		if (event.type == SDL_KEYDOWN) {
			left = true;
		}
		if (event.type == SDL_KEYUP) {
			left = false;
		}
		//position += vec3(cos(radians(rotation))*speed*deltaTime, 0, sin(radians(rotation))*speed*deltaTime);
	}
	if (event.key.keysym.sym == SDLK_d) {
		if (event.type == SDL_KEYDOWN) {
			right = true;
		}
		if (event.type == SDL_KEYUP) {
			right = false;
		}
		//position += vec3(-cos(radians(rotation))*speed*deltaTime, 0, -sin(radians(rotation))*speed*deltaTime);
	}
}

void FirstPersonController::onMouse(SDL_Event &event) {
    // Todo implement
	if (event.type == SDL_MOUSEMOTION) {
		rotation += event.motion.xrel;
	}
}

void FirstPersonController::setInitialPosition(glm::vec2 position, float rotation) {
    this->position = glm::vec4(position.x,0,position.y,1);
    this->rotation = rotation;
}
