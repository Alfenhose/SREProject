#pragma once

#include <SDL_events.h>
#include "sre/Sprite.hpp"
#include "sre/SpriteBatch.hpp"
enum ObjectType{type_ship,type_laser, type_asteroidBig, type_asteroidMed, type_asteroidSmall, type_bang};

class GameObject {
public:
    explicit GameObject(sre::Sprite sprite);
    virtual ~GameObject();
    virtual void render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);
    virtual void update(float deltaTime);
    virtual void onKey(SDL_Event& keyEvent);
	bool alive;
	ObjectType type;
	float rotation;
protected:
    glm::vec2 position;
    glm::vec2 scale;
    sre::Sprite sprite;
	

    friend class AsteroidsGame;
};
