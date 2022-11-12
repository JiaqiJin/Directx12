#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Core/Application.h"
#include "Demo/TestDemo.h"

#include <iostream>

using namespace Kawaii;

int main()
{
    std::shared_ptr<Application> app = std::make_shared<TestDemos>();
    app->init(WINDOW_WIDTH, WINDOW_HEIGHT, "Test - 1D Demo" , 60.0);
    app->start();

    return 0;
}
