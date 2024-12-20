#include "ControlManager.h"
#include "KeyCode.h"
#include <iostream>
#include "Transform.h"

void ControlManager::toggleControlMode(GLFWwindow* window, bool& isCameraMode, bool& cKeyPressed) {
    // ���� ������� C ���� ������ (� ���� cKeyPressed ��� �� ����������)
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !cKeyPressed) {
        isCameraMode = !isCameraMode;
        std::cout << (isCameraMode ? "����������� �� ���������� �������" : "����������� �� ���������� �������") << std::endl;
        cKeyPressed = true;  // ������������� ����, ��� ������� ���� ������
    }
    // ���� ������� C ���� ��������
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE) {
        cKeyPressed = false; // ���������� ����
    }
}

void ControlManager::processInput(GLFWwindow* window, float deltaTime, GLModel* models[], Transform transforms[], bool& vKeyPressed, int& currentModelIndex, bool& isCameraMode, Camera3D& camera, bool& cKeyPressed) {
    float velocity = 5.0f * deltaTime;

    // ��������� ������������ ����� �������� � ������� ������� V
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS && !vKeyPressed) {
        currentModelIndex = (currentModelIndex + 1) % 3; // ������������ �������
        vKeyPressed = true; // ������������� ����
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_RELEASE) {
        vKeyPressed = false; // ���������� ����
    }

    // ������������ ����� �������� ���������� (������/������)
    toggleControlMode(window, isCameraMode, cKeyPressed);

    if (isCameraMode) {
        // ���������� �������
        float cameraSpeed = camera.speed * deltaTime;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.moveForward(cameraSpeed);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.moveBackward(cameraSpeed);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.moveLeft(cameraSpeed);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.moveRight(cameraSpeed);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            camera.moveUp(cameraSpeed); // ������
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.moveDown(cameraSpeed); // �����
    }
    else {
        // ���������� �������
        GLModel* currentModel = models[currentModelIndex];
        Transform& currentTransform = transforms[currentModelIndex];

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            glm::vec3 newPosition = currentTransform.position() + glm::vec3(0.0f, 0.0f, -velocity);
            currentTransform.setPosition(newPosition);
            std::cout << "Position: " << newPosition.x << ", " << newPosition.y << ", " << newPosition.z << std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // s
            currentTransform.setPosition(currentTransform.position() + glm::vec3(0.0f, 0.0f, velocity)); // ������� ����� �� ��� Z
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // a
            currentTransform.setPosition(currentTransform.position() + glm::vec3(-velocity, 0.0f, 0.0f)); // ������� ����� �� ��� X
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // d
            currentTransform.setPosition(currentTransform.position() + glm::vec3(velocity, 0.0f, 0.0f)); // ������� ������ �� ��� X

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) // q
            currentTransform.setRotation(currentTransform.rotation() + glm::vec3(0.0f, velocity * 10.0f, 0.0f)); // ������� �� ��� Y
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) // e
            currentTransform.setRotation(currentTransform.rotation() + glm::vec3(0.0f, -velocity * 10.0f, 0.0f)); // ������� �� ��� Y � ������ �������

        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) // r
            currentTransform.setScale(currentTransform.scale() * 1.1f); // ����������� ������
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) // f
            currentTransform.setScale(currentTransform.scale() * 0.9f); // ��������� ������
    }
}
