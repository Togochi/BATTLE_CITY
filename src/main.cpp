#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

#include <iostream>
#include <chrono>

#include "Game/Game.h"
#include "Resources/ResourceManager.h"


glm::ivec2 g_WindowSize(640, 480);
Game g_game (g_WindowSize);


void glfwWindowsizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_WindowSize.x = width;
    g_WindowSize.y = height;
    glViewport(0, 0, width, height);
}


void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }

    g_game.setKey(key, action);
}

int main(int argc, char** argv)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "glfwInit failed" << std::endl;
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_WindowSize.x, g_WindowSize.y, "BATTLE CITY", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed" << std::endl;
        glfwTerminate();
        return -1;
    }


    glfwSetWindowSizeCallback(pWindow, glfwWindowsizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);
	
	
	if (!gladLoadGL())
	{
		std::cout << "Can't load GLAD" << '\n';
		return -1;
	}

    std::cout << "Renderer " << glGetString(GL_RENDERER) << '\n';
    std::cout << "OpenGL " << glGetString(GL_VERSION) << '\n';
	
	
	glClearColor(0, 0, 0, 1);

  
    {
        ResourceManager::setExecutablePath(argv[0]);
        g_game.init();

        auto lastTime = std::chrono::high_resolution_clock::now();
        
        while (!glfwWindowShouldClose(pWindow))
        {

   

            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;

            g_game.update(duration);

           
            glClear(GL_COLOR_BUFFER_BIT);

            g_game.render();
            
            glfwSwapBuffers(pWindow);

            glfwPollEvents();
        }
        ResourceManager::unloadAllResources();
    }

    glfwTerminate();
    return 0;
}