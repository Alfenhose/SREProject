//
// Created by Morten Nobel-Jørgensen on 12/09/2017.
//

#include "GameObject.hpp"

GameObject::GameObject(sre::Sprite sprite)
:position(0,0),
 rotation(0),
 scale(1,1),
 sprite(sprite)
{
	alive = true;
}

GameObject::~GameObject(){
}

void GameObject::update(float deltaTime) {
}

void GameObject::render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder) {
    sprite.setPosition(position);
    sprite.setRotation(rotation);
    sprite.setScale(scale);
    spriteBatchBuilder.addSprite(sprite);
}

void GameObject::onKey(SDL_Event &keyEvent) {

}

