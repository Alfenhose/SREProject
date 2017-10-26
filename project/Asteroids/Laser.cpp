//
// Created by Morten Nobel-Jørgensen on 12/09/2017.
//

#include <glm/gtx/rotate_vector.hpp>
#include "Laser.hpp"
#include "sre/Renderer.hpp"

Laser::Laser(const sre::Sprite &sprite, glm::vec2 pos, float _rotation) : GameObject(sprite) {
	scale = glm::vec2(1.f, 1.f);
	radius = 12;
	velocity = glm::vec2(cos(glm::radians(_rotation+90)) * 500, sin(glm::radians(_rotation+90)) * 500);
	rotation = _rotation;
	position = pos;
	lifeTime = 1.f;
	type = type_laser;
}

void Laser::update(float deltaTime) {
	if (lifeTime < 0)
	{
		alive = false;
	}
	position += velocity * deltaTime;
	lifeTime -= deltaTime;

}

void Laser::onCollision(std::shared_ptr<GameObject> other) {
	if (other->alive) {
		switch (other->type) {
		case type_asteroidBig:
		case type_asteroidMed:
		case type_asteroidSmall:
			other->alive = false;
			alive = false;
			break;
		default:
			break;
		}
	}
}