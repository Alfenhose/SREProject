#pragma once
#include "GameObject.hpp"

class Collidable {
public:
    virtual void onCollision(std::shared_ptr<GameObject> other) = 0;

    float getRadius() const;

    void setRadius(float radius);

protected:
    float radius = 0;
};


