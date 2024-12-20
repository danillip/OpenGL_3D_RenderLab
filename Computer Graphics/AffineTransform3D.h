#pragma once

#include <glm.hpp>
#include <cmath>

namespace AffineTransform3D {

    // Трансляция: матрица для перемещения вдоль осей
    inline glm::mat4 translate(const glm::vec3& position) {
        glm::mat4 translation = glm::mat4(1.0f); // Единичная матрица
        translation[3] = glm::vec4(position, 1.0f); // Перемещение вектора
        return translation;
    }

    // Масштабирование: матрица для масштабирования вдоль осей X, Y, Z
    inline glm::mat4 scale(const glm::vec3& scale) {
        glm::mat4 scaling = glm::mat4(1.0f); // Единичная матрица

        // Заполняем каждый столбец матрицы
        scaling[0] = glm::vec4(scale.x, 0.0f, 0.0f, 0.0f);  // Масштабирование по оси X
        scaling[1] = glm::vec4(0.0f, scale.y, 0.0f, 0.0f);  // Масштабирование по оси Y
        scaling[2] = glm::vec4(0.0f, 0.0f, scale.z, 0.0f);  // Масштабирование по оси Z
        return scaling;
    }

    // Вращение вокруг оси X: матрица вращения на угол 'angle' вокруг X
    inline glm::mat4 rotateX(float angle) {
        float cosA = cos(angle);
        float sinA = sin(angle);

        // Матрица вращения вокруг оси X
        glm::mat4 rotation = glm::mat4(1.0f);
        rotation[1] = glm::vec4(0.0f, cosA, sinA, 0.0f);  // Вращение по Y
        rotation[2] = glm::vec4(0.0f, -sinA, cosA, 0.0f); // Вращение по Z
        return rotation;
    }

    // Вращение вокруг оси Y: матрица вращения на угол 'angle' вокруг Y
    inline glm::mat4 rotateY(float angle) {
        float cosA = cos(angle);
        float sinA = sin(angle);

        // Матрица вращения вокруг оси Y
        glm::mat4 rotation = glm::mat4(1.0f);
        rotation[0] = glm::vec4(cosA, 0.0f, -sinA, 0.0f); // Вращение по X
        rotation[2] = glm::vec4(sinA, 0.0f, cosA, 0.0f);  // Вращение по Z
        return rotation;
    }

    // Вращение вокруг оси Z: матрица вращения на угол 'angle' вокруг Z
    inline glm::mat4 rotateZ(float angle) {
        float cosA = cos(angle);
        float sinA = sin(angle);

        // Матрица вращения вокруг оси Z
        glm::mat4 rotation = glm::mat4(1.0f);
        rotation[0] = glm::vec4(cosA, sinA, 0.0f, 0.0f);  // Вращение по X
        rotation[1] = glm::vec4(-sinA, cosA, 0.0f, 0.0f); // Вращение по Y
        return rotation;
    }

    // Вращение по всем осям: комбинированная матрица вращения
    inline glm::mat4 rotate(const glm::vec3& rotation) {
        // Получаем матрицы вращения для всех осей
        glm::mat4 rotX = rotateX(rotation.x);
        glm::mat4 rotY = rotateY(rotation.y);
        glm::mat4 rotZ = rotateZ(rotation.z);

        // Объединяем их путем умножения матриц (сначала вращение по Z, затем Y, потом X)
        return rotZ * rotY * rotX;
    }
}
