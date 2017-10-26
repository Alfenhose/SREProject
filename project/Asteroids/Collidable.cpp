
//
// Created by Morten Nobel-Jørgensen on 19/09/2017.
//

#include "Collidable.hpp"

float Collidable::getRadius() const {
    return radius;
}

void Collidable::setRadius(float radius) {
    Collidable::radius = radius;
}
