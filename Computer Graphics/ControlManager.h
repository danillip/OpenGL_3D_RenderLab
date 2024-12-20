#pragma once

#include <glm.hpp>
#include "Camera3D.h"
#include "GLModel.h"
#include "Transform.h"
#include <GLFW/glfw3.h>

class ControlManager {
public:
    static void toggleControlMode(GLFWwindow* window, bool& isCameraMode, bool& cKeyPressed);
    static void processInput(GLFWwindow* window, float deltaTime, GLModel* models[], Transform transforms[], bool& vKeyPressed, int& currentModelIndex, bool& isCameraMode, Camera3D& camera, bool& cKeyPressed);
};