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
        /**
         * @brief Init the Core engine object with a main window name and a path to a settings file
         */
        ENGINE_APIENTRY Core(const char* mainWindowName = NULL, const char* settingsPath = NULL);
        ENGINE_APIENTRY ~Core();

    private:
        /**
         * Avoid using more than one Core object at a time.
         * In the future this will be a singleton class.
         */

        ENGINE_APIENTRY __declspec(deprecated) Core(const Core& other);
        ENGINE_APIENTRY __declspec(deprecated) Core& operator=(const Core& other);

    public:
        /**
         * @brief The render loop
         */
        ENGINE_APIENTRY int render();

    public:
        ENGINE_APIENTRY inline Window* getMainWindow() const;

    private:

        bool update();
        bool draw();

    private:
        Window* mainWindow;

        Settings* settings;

        static uint objCount;
    };
}

#endif