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
    class Window
    {
    public:

        Window();
        ~Window();

    private:

        // Disable copying the window.

        Window(const Window& other);
        Window& operator=(const Window& other);

    public:

        /**
         ! @brief Gives direct access to the underlying GLFWwindow pointer.
         * Is used for giving the GLFWwindow pointer to glfw functions.
         *
         * @return GLFWwindow* A pointer to the underlying GLFWwindow.
         * @remarks Unsafe, use with caution.
         */
        inline GLFWwindow* getHandle() const;

    public:

        static enum class Hints: int
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
         ! @brief Sets window sampling.
         *
         * @param[in] hint The MSAA value of the window.
         * @optins MSAA_2, MSAA_4, MSAA_8, MSAA_16
         */
        void antialiasing(int hint);

        /**
         ! @brief Sets whether the window will be resizable or not.
         *
         * @param[in] hint The value to be passed (true/false).
         */
        void resizable(int hint);
        
        /**
         ! @brief Sets OpenGL version and profile.
         *
         * @param[in] majorVersion The major version of OpenGL.
         * @param[in] minorVersion The minor version of OpenGL.
         * @param[in] profile OpenGL profile.
         */
        void setOpenGL(int majorVersion, int minorVersion, int profile);

        /**
         ! @brief Creates the window based on previously given hints(options).
         * Any hint given after the calling of this function will not affect
         * the window in any way unless create() is called again.
         *
         * @param[in] windowName The name of the window.
         * @param[in] isWindowed Whether the window is in windowed mode.
         * @param[in] vm GLFW video mode.
         * @return bool If successful returns true otherwise false.
         */
        bool create(const char* windowName, bool isWindowed, GLFWvidmode vm);

    private:
        
        GLFWwindow* window;
        static uint refCount;
    };
}

#endif