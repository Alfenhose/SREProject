#pragma once

#include "GameObject.hpp"
#include "Collidable.hpp"

class Laser : public GameObject, public Collidable {
public:

	Laser(const sre::Sprite &sprite, glm::vec2 pos, float _rotation);
	void update(float deltaTime) override;

	void onCollision(std::shared_ptr<GameObject> other) override;
	
	glm::vec2 velocity;
private:
	float lifeTime;
};


