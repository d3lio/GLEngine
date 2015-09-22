#include "engine.h"

#include "commons/shader.hpp"
#include "commons/texture.hpp"
#include "commons/controls.hpp"
#include "commons/objloader.hpp"
#include "commons/vboindexer.hpp"

namespace Engine
{
    uint Core::objCount = 0;

    Core::Core(const char* mainWindowName, const char* settingsPath)
    {
        assert(objCount == 0);
        // need default values to remove this assertion
        assert(settingsPath != NULL);

        settings = new Settings(settingsPath);

        #pragma region GLFW

        mainWindow = new Window(mainWindowName);
        
        mainWindow->antialiasing((Window::Hints) settings->getAntialiasing());
        mainWindow->resizable((Window::Hints) settings->getWindowed());
        mainWindow->windowed((Window::Hints) settings->getWindowed());
        //mainWindow->setOpenGL(3, 3, GLFW_OPENGL_CORE_PROFILE);
	    //glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // So that glBegin/glVertex/glEnd work

        Resolution res;
        if (settings->getFullscreen()) {
            res = settings->getFullscreenResolution();
        }
        else {
            res = settings->getWindowedResolution();
        }

        if (!res.width || !res.height)
        {
            const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            res.width = mode->width;
            res.height = mode->height;
        }

        mainWindow->create();

        glfwMakeContextCurrent(mainWindow->getHandle());
        glfwSwapInterval(settings->getVsync());
        glfwSetInputMode(mainWindow->getHandle(), GLFW_STICKY_KEYS, GL_TRUE);
        glfwSetCursorPos(mainWindow->getHandle(), res.width/2, res.height/2);

        #pragma endregion GLFW
        #pragma region GLEW
        
        if (glfwGetWindowAttrib(mainWindow->getHandle(), GLFW_OPENGL_PROFILE) == GLFW_OPENGL_CORE_PROFILE)
        {
            glewExperimental = true; // Needed in core profile
        }
        
        if (glewInit() != GLEW_OK)
        {
            fputs("Failed to initialize GLEW.", stderr);
            glfwTerminate();
            abort();
        }
        
        printf("Renderer:\t%s\n", glGetString (GL_RENDERER));
        printf("OpenGL: \t%s\n", glGetString (GL_VERSION));
        printf("\n");

        glEnable(GL_DEPTH_TEST);   // Enable depth test
        glDepthFunc(GL_LESS);      // Accept fragment if it closer to the camera than the former one
	    glEnable(GL_CULL_FACE);    // Cull triangles which normal is not towards the camera
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Background color

        #pragma endregion GLEW

        objCount++;
    }

    Core::~Core()
    {
        delete settings;
        delete mainWindow;
    }

    inline Window* Core::getMainWindow() const
    {
        return mainWindow;
    }

    int Core::render()
    {
        GLuint vertexArrayID;
        glGenVertexArrays (1, &vertexArrayID);
        glBindVertexArray (vertexArrayID);

        std::vector <glm::vec3> vertices;
        std::vector <glm::vec2> uvs;
        std::vector <glm::vec3> normals;
        loadOBJ ("resources/suzanne.obj", vertices, uvs, normals);
    
        std::vector <unsigned short> indices;

        std::vector <glm::vec3> indexedVertices;
        std::vector <glm::vec2> indexedUvs;
        std::vector <glm::vec3> indexedNormals;
        indexVBO(
            vertices, uvs, normals,
            indices,
            indexedVertices, indexedUvs, indexedNormals
        );

        GLuint textureID = loadDDS ("resources/suzanne.dds");

        GLuint vertexBuffer;
        glGenBuffers (1, &vertexBuffer);
        glBindBuffer (GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData (GL_ARRAY_BUFFER, indexedVertices.size() * sizeof (glm::vec3), &indexedVertices[0], GL_STATIC_DRAW);

        GLuint uvBuffer;
        glGenBuffers (1, &uvBuffer);
        glBindBuffer (GL_ARRAY_BUFFER, uvBuffer);
        glBufferData (GL_ARRAY_BUFFER, indexedUvs.size() * sizeof (glm::vec2), &indexedUvs[0], GL_STATIC_DRAW);

        GLuint normalBuffer;
        glGenBuffers (1, &normalBuffer);
        glBindBuffer (GL_ARRAY_BUFFER, normalBuffer);
        glBufferData (GL_ARRAY_BUFFER, indexedNormals.size() * sizeof(glm::vec3), &indexedNormals[0], GL_STATIC_DRAW);

        GLuint elementBuffer;
        glGenBuffers (1, &elementBuffer);
        glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glBufferData (GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof (unsigned short), &indices[0], GL_STATIC_DRAW);

        glm::mat4 projMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 modelMatrix;
        glm::mat4 mvpMatrix;

        GLuint programID = LoadShaders ("shaders/vs_lighting.glsl", "shaders/fs_lighting.glsl");

        GLuint modelMatrixUniformID     = glGetUniformLocation (programID, "modelMatrix");
        GLuint viewMatrixUniformID      = glGetUniformLocation (programID, "viewMatrix");
        GLuint mvpMatrixUniformID       = glGetUniformLocation (programID, "mvpMatrix");
        GLuint textureUniformID         = glGetUniformLocation (programID, "textureSampler");
        GLuint lightPositionUniformID   = glGetUniformLocation (programID, "lightPosition_ws");
        GLuint lightColorUniformID      = glGetUniformLocation (programID, "lightColor");
        GLuint lightPowerUniformID      = glGetUniformLocation (programID, "lightPower");

        glUseProgram (programID);
        /// The tutorial can run without binding the texture
        /// This can be added in the code in Tutorial 5 aswell
        /// I assume this is so because in the loadDDS function the texture is binded and the shader uses the texture unit 0 by default
	    glActiveTexture (GL_TEXTURE0);              // Activate Texture Unit 0
	    glBindTexture (GL_TEXTURE_2D, textureID);   // Bind our texture in Texture Unit 0
	    glUniform1i (textureUniformID, 0);          // Set our "myTextureSampler" sampler to user Texture Unit 0

        glm::vec3 lightPosition(5.0f, 0.0f, 5.0f);
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
        float lightPower = 60.0f;

        double stime = glfwGetTime();
        unsigned short nbFrames = 0;

        // Main loop
        do
        {
		    double etime = glfwGetTime();
		    nbFrames++;
		    if (etime - stime >= 1.0)
            {
                printf("%.4f ms/frame | %d FPS\n", 1000.0/(double)nbFrames, nbFrames);
			    nbFrames = 0;
			    //stime += 1.0;
                stime = glfwGetTime();
		    }

            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            computeMatricesFromInputs (
                mainWindow->getHandle(),
                glfwGetVideoMode(glfwGetPrimaryMonitor())->width,
                glfwGetVideoMode(glfwGetPrimaryMonitor())->height
            );
            projMatrix  = getProjectionMatrix ();
            viewMatrix  = getViewMatrix ();
            modelMatrix = glm::mat4 (1.0f);
            mvpMatrix   = projMatrix * viewMatrix * modelMatrix;

            glUniformMatrix4fv (modelMatrixUniformID, 1, GL_FALSE, &modelMatrix[0][0]);
            glUniformMatrix4fv (viewMatrixUniformID, 1, GL_FALSE, &viewMatrix[0][0]);
            glUniformMatrix4fv (mvpMatrixUniformID, 1, GL_FALSE, &mvpMatrix[0][0]);

            glUniform3fv (lightPositionUniformID, 1, &lightPosition[0]);
            glUniform3fv (lightColorUniformID, 1, &lightColor[0]);
            glUniform1f (lightPowerUniformID, lightPower);

            glEnableVertexAttribArray (0);
            glBindBuffer (GL_ARRAY_BUFFER, vertexBuffer);
            glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
 
            glEnableVertexAttribArray (1);
            glBindBuffer (GL_ARRAY_BUFFER, uvBuffer);
            glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

            glEnableVertexAttribArray (2);
            glBindBuffer (GL_ARRAY_BUFFER, normalBuffer);
            glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

            glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

            glDrawElements (GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_SHORT, (void*) 0);

            /** Rendering second object using the same shader, so some of the stuff stay the same (no rebind)**/
        
            glm::mat4 model2Matrix = glm::translate(glm::mat4 (1.0f), glm::vec3(-3.0f, 0.0f, 0.0f));
            glm::mat4 mvp2Matrix   = projMatrix * viewMatrix * model2Matrix;

            glUniformMatrix4fv (modelMatrixUniformID, 1, GL_FALSE, &model2Matrix[0][0]);
            glUniformMatrix4fv (mvpMatrixUniformID, 1, GL_FALSE, &mvp2Matrix[0][0]);

            glEnableVertexAttribArray (0);
            glBindBuffer (GL_ARRAY_BUFFER, vertexBuffer);
            glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
 
            glEnableVertexAttribArray (1);
            glBindBuffer (GL_ARRAY_BUFFER, uvBuffer);
            glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

            glEnableVertexAttribArray (2);
            glBindBuffer (GL_ARRAY_BUFFER, normalBuffer);
            glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

            glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

            glDrawElements (GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_SHORT, (void*) 0);

            glDisableVertexAttribArray (0);
            glDisableVertexAttribArray (1);
            glDisableVertexAttribArray (2);

            glfwSwapBuffers (mainWindow->getHandle());
            glfwPollEvents ();
        }
        while (glfwGetKey (mainWindow->getHandle(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
               glfwWindowShouldClose (mainWindow->getHandle()) == GL_FALSE);
    
	    // Cleanup VBO
	    glDeleteBuffers(1, &vertexBuffer);
	    glDeleteBuffers(1, &uvBuffer);

        glDeleteTextures (1, &textureID);

        glDeleteProgram (programID);

        glDeleteVertexArrays (1, &vertexArrayID);
        //glfwDestroyWindow (mainWindow->getHandle());

        //glfwTerminate ();

        return 0;
    }
}
