#include "QGLFWWindow.h"

#include "GLFW/glfw3.h"

static bool glfw_initialized = false;

void QGLFWWindow::on_create()
{
    if(!glfw_initialized)
    {
        if (!glfwInit())
        {
            // Initialization failed
            return;
        }
        glfw_initialized = true;
    }

    window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
}

void QGLFWWindow::run()
{
    if (window)
    {
        glfwMakeContextCurrent(window);
        while (!glfwWindowShouldClose(window))
        {
            // Render here
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
}
