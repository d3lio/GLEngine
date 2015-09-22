#ifndef CONTROLS_HPP
#define CONTROLS_HPP

void computeMatricesFromInputs(GLFWwindow* window, int monitorWidth, int monitorHeight);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif