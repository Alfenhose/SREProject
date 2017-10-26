//
// Created by Morten Nobel-Jørgensen on 12/09/2017.
//

#include <ctime>
#include <glm/gtc/constants.hpp>
#include "AsteroidsGame.hpp"
#include "GameObject.hpp"
#include "SpaceShip.hpp"
#include "Asteroid.hpp"
#include "Laser.hpp"



using namespace sre;


AsteroidsGame::AsteroidsGame() {
    r.setWindowTitle("Asteroids");
    r.init(SDL_INIT_EVERYTHING,       // Create the window and the graphics context (instantiates the sre::Renderer). Note that most
           SDL_WINDOW_OPENGL        // created before `init()`).
           );

    time_t t;                                               // random seed based on time
    srand((unsigned) time(&t));
	gameObjectCount = 0;
    atlas = SpriteAtlas::create("asteroids.json","asteroids.png");

    spaceshipSprite = atlas->get("playerShip2_orange.png");
	bigAsteroidSprite = atlas->get("meteorBrown_big1.png");
	medAsteroidSprite = atlas->get("meteorBrown_med1.png");
	smallAsteroidSprite = atlas->get("meteorBrown_small1.png");
	bangSprite = atlas->get("bang.png");
	laserSprite = atlas->get("laserBlue04.png");
	
	reset();

    camera.setWindowCoordinates();

    r.frameUpdate = [&](float deltaTime){
        update(deltaTime);
    };

    r.keyEvent = [&](SDL_Event& event){
        keyEvent(event);
    };

    r.frameRender = [&](){
        render();
    };

    r.startEventLoop();
}
void AsteroidsGame::reset() {
	
	gameObjects.clear();
	gameObjectsToBeAdded.push_back(std::make_shared<SpaceShip>(spaceshipSprite, this));
	gameObjectsToBeAdded.push_back(std::make_shared<Asteroid>(bigAsteroidSprite, this));
	gameObjectsToBeAdded.push_back(std::make_shared<Asteroid>(bigAsteroidSprite, this));
	gameObjectsToBeAdded.push_back(std::make_shared<Asteroid>(bigAsteroidSprite, this));
	gameObjectsToBeAdded.push_back(std::make_shared<Asteroid>(bigAsteroidSprite, this));
	gameObjectsToBeAdded.push_back(std::make_shared<Asteroid>(bigAsteroidSprite, this));
	shipAlive = true;
}
void AsteroidsGame::update(float deltaTime) {
	//collisions
	{
		for (int i = 0; i < gameObjects.size(); i++) {
			for (int j = i; j < gameObjects.size(); j++) {
				if (i != j) {
					float collisionDistance = 0;
					auto distance = glm::distance(gameObjects[i]->position, gameObjects[j]->position);
					auto a = dynamic_cast<Collidable*>(gameObjects[i].get());
					auto b = dynamic_cast<Collidable*>(gameObjects[j].get());
					if (a != nullptr && b != nullptr) {
						collisionDistance = a->getRadius() + b->getRadius();
						if (collisionDistance > distance) {
							a->onCollision(gameObjects[j]);
							b->onCollision(gameObjects[i]);
						}
					}
				}
			}
		}
		for (int i = 0; i < gameObjects.size(); i++) {
			if (gameObjects[i]->alive == true) {
				gameObjects[i]->update(deltaTime);
			}
			else {
				gameObjects[i] = nullptr;
				gameObjectCount--;
				gameObjects.erase(gameObjects.begin() + i);
				i--;
			}
		}
		for (int i = 0; i < gameObjectsToBeAdded.size(); i++) {
			gameObjects.push_back(gameObjectsToBeAdded[i]);
			gameObjectsToBeAdded.erase(gameObjectsToBeAdded.begin() + i);
			gameObjectCount++;
			i--;
		}
	}

}

void drawCircle(std::vector<glm::vec3>& lines, glm::vec2 position, float radius){
    float quaterPi = glm::quarter_pi<float>();
    for (float f = 0;f<glm::two_pi<float>();f += quaterPi){
        // line from
        lines.push_back(glm::vec3{position.x + cosf(f)*radius,
                                  position.y + sinf(f)*radius,
                                  0
        });
        // line to
        lines.push_back(glm::vec3{position.x + cosf(f+quaterPi)*radius,
                                  position.y + sinf(f+quaterPi)*radius,
                                  0
        });
    }
}

void AsteroidsGame::render() {
    auto renderPass = RenderPass::create()
            .withCamera(camera)
            .withClearColor(true, {.20, .60, .86, 1})
            .build();
    auto spriteBatchBuilder = SpriteBatch::create();
    for (auto & go : gameObjects){
        go->render(spriteBatchBuilder);
    }
    auto spriteBatch = spriteBatchBuilder.build();
    renderPass.draw(spriteBatch);

    if (debugCollisionCircles){
        std::vector<glm::vec3> lines;
        for (auto & go : gameObjects){
            auto col = dynamic_cast<Collidable*>(go.get());
            if (col != nullptr){
                drawCircle(lines, go->position, col->getRadius());
            }
        }
        renderPass.drawLines(lines);
    }
	ImGui::SetNextWindowPos(ImVec2((Renderer::instance->getWindowSize().x - 150)*0.5f, .0f), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(150, 70), ImGuiSetCond_Always);
	ImGui::Begin("", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	//ImGui::LabelText("Rendered objects", "%i", gameObjects.end-gameObjects.begin);
	ImGui::LabelText("GameObjectCount", "%i", gameObjectCount);
	ImGui::End();
}

void AsteroidsGame::keyEvent(SDL_Event &event) {
    for (auto & go : gameObjects){
        go->onKey(event);
    }
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d){
        debugCollisionCircles = !debugCollisionCircles;
    }
	if (event.key.keysym.sym == SDLK_SPACE) {
		if (event.type == SDL_KEYDOWN) {
			if (shipAlive == false) {
				reset();
			}
		}
	}
}

int main(){
    new AsteroidsGame();
    return 0;
}