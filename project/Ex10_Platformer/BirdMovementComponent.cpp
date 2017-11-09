//
// Created by Morten Nobel-Jørgensen on 11/6/17.
//

#include <iostream>
#include "BirdMovementComponent.hpp"
#include "GameObject.hpp"

BirdMovementComponent::BirdMovementComponent(GameObject *gameObject) : Component(gameObject) {}

void BirdMovementComponent::update(float deltaTime) {
    time += deltaTime;
    gameObject->setPosition(computePositionAtTime(time));
}

glm::vec2 BirdMovementComponent::computePositionAtTime(float time) {
	int A = (int)fmod(time, getNumberOfSegments())*2;
    
    float t = fmod(time,1.0f);

    // todo use Quadratic Bézier spline instead
	//return positions[startSegment];
	//return glm::mix(positions[segment],positions[segment+1],t);
	return pow(1 - t, 2)*positions[A]
			+ (2 * t*(1 - t)) * positions[A+1]
			+ pow(t, 2) * positions[A+2];
}

const std::vector<glm::vec2> &BirdMovementComponent::getPositions() {
    return positions;
}

void BirdMovementComponent::setPositions(std::vector<glm::vec2> positions) {
    this->positions = std::move(positions);
}

int BirdMovementComponent::getNumberOfSegments() {
    // todo return number of Quadratic Bézier spline segments instead
    return (positions.size()-1)/2;
}

