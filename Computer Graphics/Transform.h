#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>

class Transform
{
public:
    Transform();
    ~Transform() = default;

    // Методы установки параметров
    void setPosition(const glm::vec3& position);
    void setRotation(const glm::vec3& rotation);
    void setScale(const glm::vec3& scale);

    // Методы получения параметров
    const glm::vec3& position() const;
    const glm::vec3& rotation() const;
    const glm::vec3& scale() const;

    // Методы для настройки скорости
    void setRotationSpeed(float speed);
    void setScaleSpeed(float speed);

    // Расчет итоговой матрицы трансформации
    glm::mat4 transformMatrix() const;

private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
    float m_rotationSpeed;  // Переменная для скорости вращения
    float m_scaleSpeed;     // Переменная для скорости масштабирования
};
