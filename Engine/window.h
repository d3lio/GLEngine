#pragma once
#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <cstdio> // puts
#include <cstdlib> // abort
//#define GLFW_INCLUDE_GLU
#include <glfw/glfw3.h>

#include "utils/engine_defines.h"

namespace Engine
{
    /**
     * TODO:
     * Getters for the various options.
     */
    class Window
    {
    public:

        /**
         * @brief Create a window with a name.
         * Init glfw and error callback as well.
         */
        ENGINE_APIENTRY Window(const char* _name = NULL);
        /**
         * @brief Free the GLFWwindow*
         * Terminate glfw when all Window object are destroyed.
         */
        ENGINE_APIENTRY ~Window();

        ENGINE_APIENTRY operator GLFWwindow*() const;

    private:

        /**
         * Avoid using more than one Window object at a time.
         * When referring a Window object use a smart pointer
         * since the dtor will terminate glfw.
         */

        ENGINE_APIENTRY Window(const Window& other);
        ENGINE_APIENTRY Window& operator=(const Window& other);

    public:

        /**
         * @brief Get the window title;
         */
        ENGINE_APIENTRY inline const char* getTitle() const;

        /**
         * @brief Gives direct access to the underlying GLFWwindow pointer.
         * Is used for giving the GLFWwindow pointer to glfw functions.
         *
         * @return GLFWwindow* A pointer to the underlying GLFWwindow.
         * @remarks Unsafe, use with caution.
         */
        ENGINE_APIENTRY inline GLFWwindow* getHandle() const;

    public:

        static enum class Hints
        {
            FALSE = 0x00,
            TRUE = 0x01,
            MSAA_2 = 0x02,
            MSAA_4 = 0x04,
            MSAA_8 = 0x08,
            MSAA_16 = 0x10
        };

    public:

        /**
         * @brief Sets window sampling.
         *
         * @param[in] hint The MSAA value of the window.
         * @optins MSAA_2, MSAA_4, MSAA_8, MSAA_16
         */
        ENGINE_APIENTRY void antialiasing(Hints hint);

        /**
         * @brief Sets whether the window will be resizable or not.
         *
         * @param[in] hint The value to be passed (true/false).
         */
        ENGINE_APIENTRY void resizable(Hints hint);
        
        /**
         * @brief Sets whether the window is in windowed mode.
         *
         * @param[in] hint The value to be passed (true/false).
         */
        ENGINE_APIENTRY void windowed(Hints hint);

        /**
         * @brief Sets OpenGL version and profile.
         *
         * @param[in] majorVersion The major version of OpenGL.
         * @param[in] minorVersion The minor version of OpenGL.
         * @param[in] profile OpenGL profile.
         */
        ENGINE_APIENTRY void setOpenGL(int majorVersion, int minorVersion, int profile);

        /**
         * @brief Creates the window based on previously given hints(options).
         * Call again to recreate based on newly given hints.
         *
         * @param[in] vm GLFW video mode.
         * @return bool If successful returns true otherwise false.
         */
        ENGINE_APIENTRY bool create(const GLFWvidmode* vm = NULL);

    private:
        
        char* name;
        GLFWwindow* window;

        int antialiasingSamples;

        struct {
            int majorVersion;
            int minorVersion;
            int profile;
        } OpenGLHints;
        
        bool isResizable;
        bool isWindowed;
    
    private:

        static uint objCount;
    };
}

#endif