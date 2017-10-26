#pragma once

#include "GameObject.hpp"
#include "Collidable.hpp"

enum sizeEnum { big, med, small };

class Asteroid : public GameObject, public Collidable {
public:

	Asteroid(const sre::Sprite &sprite, AsteroidsGame* _game);
	Asteroid(const sre::Sprite &sprite, AsteroidsGame* _game, sizeEnum size, glm::vec2 position);
	~Asteroid();
	void update(float deltaTime) override;

	void onCollision(std::shared_ptr<GameObject> other) override;
	
	glm::vec2 velocity;
private:
	float rotationSpeed;
	glm::vec2 winSize;
	sizeEnum size;
	AsteroidsGame* game;
};


