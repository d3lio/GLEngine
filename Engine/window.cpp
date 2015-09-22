#include "window.h"

void errorCallback (int error, const char* description)
{
    fputs (description, stderr);
}

namespace Engine
{
    uint Window::refCount = 0;

    Window::Window()
    {
        if (!glfwInit())
        {
            fputs("Failed to initialize GLFW.", stderr);
            abort();
        }

        if (!refCount) {
            glfwSetErrorCallback(errorCallback);
        }

        window = NULL;
        refCount++;
    }
    Window::~Window()
    {
        glfwDestroyWindow(window);
        refCount--;
        
        if (!refCount) {
            glfwTerminate();
        }
    }

    inline GLFWwindow* Window::getHandle() const
    {
        //__pragma (message("Warning: This function is unsafe due to giving direct access to private members."));
        return window;
    }

    void Window::antialiasing(int hint)
    {
        glfwWindowHint(GLFW_SAMPLES, hint);
    }

    void Window::resizable(int hint)
    {
        glfwWindowHint (GLFW_RESIZABLE, hint);
    }

    void Window::setOpenGL(int majorVersion, int minorVersion, int profile)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
        glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
    }

    bool Window::create(const char* windowName, bool isWindowed, GLFWvidmode vm)
    {
        glfwDestroyWindow(window);

        if (vm.redBits)
        {
            glfwWindowHint(GLFW_ACCUM_RED_BITS, vm.redBits);
        }
        if (vm.greenBits)
        {
            glfwWindowHint(GLFW_ACCUM_GREEN_BITS, vm.greenBits);
        }
        if (vm.blueBits)
        {
            glfwWindowHint(GLFW_ACCUM_BLUE_BITS, vm.blueBits);
        }

        if (!vm.width || !vm.height)
            vm = *const_cast<GLFWvidmode*>(glfwGetVideoMode(glfwGetPrimaryMonitor()));

        window = glfwCreateWindow(vm.width, vm.height, windowName, (isWindowed? NULL: glfwGetPrimaryMonitor()), NULL);

        return true;
    }
}