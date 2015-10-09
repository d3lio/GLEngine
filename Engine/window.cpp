#include "window.h"
#include <cstring>

void errorCallback (int error, const char* description)
{
    fputs (description, stderr);
}

namespace Engine
{
    uint Window::objCount = 0;

    Window::Window(const char* _name)
    {
        if (!glfwInit())
        {
            fputs("Failed to initialize GLFW.", stderr);
            abort();
        }

        if (!objCount) {
            glfwSetErrorCallback(errorCallback);
        }

        if (_name) {
            name = new char[strlen(_name)+1];
            strcpy(name, _name);
        }
        else {
            name = new char[11];
            strcpy(name, "New window");
        }

        window = NULL;

        antialiasingSamples = (int)Hints::MSAA_4;
        _isResizable = false;
        _isWindowed = false;

        OpenGLHints.majorVersion = 3;
        OpenGLHints.minorVersion = 3;
        OpenGLHints.profile = GLFW_OPENGL_CORE_PROFILE;

        objCount++;
    }
    Window::~Window()
    {
        glfwDestroyWindow(window);

        objCount--;
        
        if (!objCount) {
            glfwTerminate();
        }

        delete name;
    }

    Window::operator GLFWwindow*() const
    {
        //__pragma (message("Warning: This function is unsafe due to giving direct access to private members."));
        return window;
    }

    inline const char* Window::getTitle() const
    {
        return name;
    }

    inline GLFWwindow* Window::getHandle() const
    {
        //__pragma (message("Warning: This function is unsafe due to giving direct access to private members."));
        return window;
    }

    inline int Window::getAntSamples() const
    {
        return antialiasingSamples;
    }

    inline bool Window::isResizable() const
    {
        return _isResizable;
    }

    inline bool Window::isWindowed() const
    {
        return _isWindowed;
    }
    
    inline Window::OGH Window::getOpenGL() const
    {
        return OpenGLHints;
    }

    void Window::antialiasing(Hints hint)
    {
        antialiasingSamples = (int)hint;
    }

    void Window::resizable(Hints hint)
    {
        _isResizable = (bool)((int)hint&1);
    }
    
    void Window::windowed(Hints hint)
    {
        _isWindowed = (bool)((int)hint&1);
    }

    void Window::setOpenGL(int majorVersion, int minorVersion, int profile)
    {
        OpenGLHints.majorVersion = majorVersion;
        OpenGLHints.minorVersion = minorVersion;
        OpenGLHints.profile = profile;
    }

    bool Window::create(const GLFWvidmode* vm)
    {
        glfwDestroyWindow(window);

        if (!vm || !vm->width || !vm->height)
            vm = glfwGetVideoMode(glfwGetPrimaryMonitor());

        glfwWindowHint(GLFW_SAMPLES, antialiasingSamples);
        glfwWindowHint(GLFW_RESIZABLE, _isResizable);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLHints.majorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLHints.minorVersion);
        glfwWindowHint(GLFW_OPENGL_PROFILE, OpenGLHints.profile);

        if (vm->redBits)
        {
            glfwWindowHint(GLFW_ACCUM_RED_BITS, vm->redBits);
        }
        if (vm->greenBits)
        {
            glfwWindowHint(GLFW_ACCUM_GREEN_BITS, vm->greenBits);
        }
        if (vm->blueBits)
        {
            glfwWindowHint(GLFW_ACCUM_BLUE_BITS, vm->blueBits);
        }

        window = glfwCreateWindow(
            vm->width,
            vm->height,
            name,
            (_isWindowed? NULL: glfwGetPrimaryMonitor()),
            NULL
        );

        if (!window)
        {
            fputs("Failed to open GLFW window.", stderr);
            return false;
        }
        else return true;
    }
}