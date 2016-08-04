#include <iostream>
#include <vector>
#include <fstream>

#include "SRE/Texture.h"
#include "SRE/SimpleRenderEngine.h"
#include "SRE/Camera.h"
#include "SRE/Mesh.h"
#include "SRE/Shader.h"
#include "SDL.h"

#include <glm/glm.hpp>

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace SRE;

namespace {
static std::vector<char> ReadAllBytes(char const* filename)
{
    using namespace std;
    ifstream ifs(filename, std::ios::binary|std::ios::ate);
    ifstream::pos_type pos = ifs.tellg();

    std::vector<char>  result(pos);

    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);

    return result;
}
}

int main() {
    std::cout << "Spinning cube" << std::endl;
    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
            "An SDL2 window",                  // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            640,                               // width, in pixels
            480,                               // height, in pixels
            SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully made
    if (window == NULL) {
        // In the event that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SimpleRenderEngine r{window};

    r.getCamera()->lookAt({0,0,3},{0,0,0},{0,1,0});
    r.getCamera()->setPerspectiveProjection(60,640,480,0.1,100);
    Shader* shader = Shader::createUnlitColor();
    Mesh* mesh = Mesh::createCube();
    shader->setVector("color", {0,1,0,1});

    float duration = 10000;
    for (float i=0;i<duration ;i+=16){
        r.clearScreen({1,0,0,1});
        r.render(mesh, glm::eulerAngleY(glm::radians(360*i/duration)),shader);
        r.swapWindow();
        SDL_Delay(16);
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();

    return 0;
}

