#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <glew/glew.h>
//#define GLFW_INCLUDE_GLU
// TODO: remove
#include <glfw/glfw3.h>
#include "window.h"

#include "utils/engine_defines.h"
#include "utils/engine_math.h"
#include "settings/settings.h"

#include <string>
#include <vector>

namespace Engine
{
    class Core
    {
    public:
        ENGINE_APIENTRY Core(const char* settingsPath = NULL);
        ENGINE_APIENTRY ~Core();

    private:
        ENGINE_APIENTRY Core(const Core& other);
        ENGINE_APIENTRY Core& operator=(const Core& other);

    public:
        ENGINE_APIENTRY int initGLFW();
        ENGINE_APIENTRY int initGLEW();
        ENGINE_APIENTRY int renderLoop();

    public:
        ENGINE_APIENTRY void setWindowName(const char* name);

        ENGINE_APIENTRY inline GLFWwindow* getRenderWindowHandler() const;
        ENGINE_APIENTRY inline std::string getWindowName() const;

    private:

        bool update();
        bool draw();

    private:
        GLFWwindow* renderWindow;
        std::string windowName;

        Settings* settings;
    };
}

#endif