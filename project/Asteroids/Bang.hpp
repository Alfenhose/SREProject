#pragma once

#include "GameObject.hpp"

class Bang : public GameObject {
public:

	Bang(const sre::Sprite &sprite, glm::vec2 pos);
	void update(float deltaTime) override;

//private:
	
};


