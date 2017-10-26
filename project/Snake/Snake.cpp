#include "Snake.hpp"
#include "SnakeBody.hpp"

Snake::Snake() {
	snakeHead = nullptr;
}

void Snake::move(){                                                 // This is called every time the snake should move.
    int currentHeadPosX = snakeHead->x;
    int currentHeadPosY = snakeHead->y;

	snakeHead->moveTo(currentHeadPosX + moveX, currentHeadPosY + moveY);
}

void Snake::setMoveDirection(int moveX, int moveY) {               // This is called whenever one arrow key is pressed. Values are [-1,0,1] for x and y.
	if (moveX*this->moveX == 0 || moveY*this->moveY == 0) {
		this->moveX = moveX;
		this->moveY = moveY;
	}
}

void Snake::init(int initialLength, int x, int y, int moveX, int moveY) {   // This is called every time the game starts or restarts. Make sure not to leak resources.
	length = initialLength;
    this->moveX = moveX;
    this->moveY = moveY;
    snakeHead = std::make_shared<SnakeBody>(x,y);
	std::shared_ptr<SnakeBody> s = snakeHead;
	while (length > 1) {
		s->next = std::make_shared<SnakeBody>(s->x - moveX, s->y - moveY);
		s = s->next;
		length--;
	}
}

void Snake::grow() {                                               // Should increment the length and append a SnakeBody
	std::shared_ptr<SnakeBody> s = snakeHead;
	while (s->next != nullptr) {
		s = s->next;
	}
	s->next =  std::make_shared<SnakeBody>(s->x, s->y);
}

bool Snake::collide(int x, int y) {                                 // Returns true if one of the SnakeBody objects has the position (x,y)
	std::shared_ptr<SnakeBody> s = snakeHead;
	while (s->next != nullptr) {
		s = s->next;
		if (s->x == x && s->y == y) {
			return true;
		}
	}
	return false;
}
