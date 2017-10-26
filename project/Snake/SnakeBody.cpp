//
// Created by Morten Nobel-Jørgensen on 04/09/2017.
//

#include "SnakeBody.hpp"

int SnakeBody::totalSnakeBodies = 0;

SnakeBody::SnakeBody(int x, int y) {
    this->x = x;
    this->y = y;

    totalSnakeBodies++;                                 // incremented every time a new SnakeBody is created
}

SnakeBody::~SnakeBody() {
    totalSnakeBodies--;                                 // decremented every time a new SnakeBody is created
}

void SnakeBody::moveTo(int x, int y) {
	if (next != nullptr) {
		next->moveTo(this->x, this->y);
	}
	this->x = x;
	this->y = y;
}
