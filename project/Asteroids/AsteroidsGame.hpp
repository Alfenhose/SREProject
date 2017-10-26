#pragma once

#include <vector>
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

class GameObject;

class AsteroidsGame {
public:
    AsteroidsGame();
	sre::Sprite bigAsteroidSprite;
	sre::Sprite medAsteroidSprite;
	sre::Sprite smallAsteroidSprite;
	sre::Sprite spaceshipSprite;
	sre::Sprite laserSprite;
	sre::Sprite bangSprite;
	std::vector<std::shared_ptr<GameObject>> gameObjectsToBeAdded;
	bool shipAlive = false;
	int gameObjectCount;
	
private:
    void update(float deltaTime);
    void render();
    void keyEvent(SDL_Event &event);

    sre::Camera camera;
    sre::SDLRenderer r;
    std::shared_ptr<sre::SpriteAtlas> atlas;
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	void AsteroidsGame::reset();
	
    bool debugCollisionCircles = false;
};


