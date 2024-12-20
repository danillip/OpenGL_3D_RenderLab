#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

inline glm::mat3 Translation(double x, double y) {
    glm::mat3 translation = glm::mat3(
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        x, y, 1.0f);
    return translation;
}

inline glm::mat3 Rotation(double angle) {
    float radians = glm::radians(angle);
    glm::mat3 rotation = glm::mat3(
        cos(radians), -sin(radians), 0.0f,
        sin(radians), cos(radians), 0.0f,
        0.0f, 0.0f, 1.0f);
    return rotation;
}

inline glm::mat3 Scaling(double scaleX, double scaleY) {
    glm::mat3 scaling = glm::mat3(
        scaleX, 0.0f, 0.0f,
        0.0f, scaleY, 0.0f,
        0.0f, 0.0f, 1.0f);
    return scaling;
}

inline glm::mat3 Identity() {
    return glm::mat3(
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f);
}

#endif // AFFINE_TRANSFORM_H
