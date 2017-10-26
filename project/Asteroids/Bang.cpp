//
// Created by Morten Nobel-Jørgensen on 12/09/2017.
//

#include <glm/gtx/rotate_vector.hpp>
#include "Bang.hpp"
#include "sre/Renderer.hpp"

Bang::Bang(const sre::Sprite &sprite, glm::vec2 pos) : GameObject(sprite) {
	scale = glm::vec2(1.f, 1.f);
	position = pos;
}

void Bang::update(float deltaTime) {
	
}