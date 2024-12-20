#include "Transform.h"
#include "AffineTransform3D.h"

Transform::Transform()
    : m_position(0.0f, 0.0f, 0.0f),
    m_rotation(0.0f, 0.0f, 0.0f),
    m_scale(1.0f, 1.0f, 1.0f),
    m_rotationSpeed(0.02f),  // Начальная скорость вращения
    m_scaleSpeed(1.0f)      // Начальная скорость масштабирования(сразу применится к модели при инициализации)
{}

void Transform::setRotationSpeed(float speed) {
    m_rotationSpeed = speed;
}

void Transform::setScaleSpeed(float speed) {
    m_scaleSpeed = speed;
}

void Transform::setPosition(const glm::vec3& position) {
    m_position = position;
}

void Transform::setRotation(const glm::vec3& rotation) {
    m_rotation = rotation;
}

void Transform::setScale(const glm::vec3& scale) {
    m_scale = scale;
}

const glm::vec3& Transform::position() const {
    return m_position;
}

const glm::vec3& Transform::rotation() const {
    return m_rotation;
}

const glm::vec3& Transform::scale() const {
    return m_scale;
}

// Метод для вычисления итоговой матрицы трансформации
glm::mat4 Transform::transformMatrix() const {
    // Перемещение остается без изменений
    glm::mat4 translationMatrix = AffineTransform3D::translate(m_position);  // Перемещение

    // Вращение с учетом скорости
    glm::mat4 rotationMatrix = AffineTransform3D::rotate(m_rotation * m_rotationSpeed);  // Вращение
    // Масштабирование с учетом скорости
    glm::mat4 scaleMatrix = AffineTransform3D::scale(m_scale * m_scaleSpeed);  // Масштабирование

    // Возвращаем итоговую матрицу: сначала масштабирование, затем вращение, и в конце перемещение
    return translationMatrix * rotationMatrix * scaleMatrix;
}
