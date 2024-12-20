#include "Camera3D.h"
#include <gtc/matrix_transform.hpp>

Camera3D::Camera3D(float fov, float aspectRatio, float near, float far)
    : position(0.0f, 0.0f, 3.0f), front(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f), yaw(-90.0f), pitch(0.0f), fov(fov), speed(2.5f) {}

glm::mat4 Camera3D::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera3D::getProjectionMatrix(float aspectRatio) {
    return glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
}

void Camera3D::updateYawPitch(float xOffset, float yOffset) {
    const float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);
}

void Camera3D::moveForward(float velocity) {
    position += velocity * front;
}

void Camera3D::moveBackward(float velocity) {
    position -= velocity * front;
}

void Camera3D::moveLeft(float velocity) {
    position -= glm::normalize(glm::cross(front, up)) * velocity;
}

void Camera3D::moveRight(float velocity) {
    position += glm::normalize(glm::cross(front, up)) * velocity;
}

void Camera3D::moveUp(float velocity) {
    position.y += velocity;
}

void Camera3D::moveDown(float velocity) {
    position.y -= velocity;
}

glm::vec3 Camera3D::getPosition() const {
    return position; // Возвращаем позицию камеры
}