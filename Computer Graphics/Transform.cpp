#include "Transform.h"
#include "AffineTransform3D.h"

Transform::Transform()
    : m_position(0.0f, 0.0f, 0.0f),
    m_rotation(0.0f, 0.0f, 0.0f),
    m_scale(1.0f, 1.0f, 1.0f),
    m_rotationSpeed(0.02f),  // ��������� �������� ��������
    m_scaleSpeed(1.0f)      // ��������� �������� ���������������(����� ���������� � ������ ��� �������������)
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

// ����� ��� ���������� �������� ������� �������������
glm::mat4 Transform::transformMatrix() const {
    // ����������� �������� ��� ���������
    glm::mat4 translationMatrix = AffineTransform3D::translate(m_position);  // �����������

    // �������� � ������ ��������
    glm::mat4 rotationMatrix = AffineTransform3D::rotate(m_rotation * m_rotationSpeed);  // ��������
    // ��������������� � ������ ��������
    glm::mat4 scaleMatrix = AffineTransform3D::scale(m_scale * m_scaleSpeed);  // ���������������

    // ���������� �������� �������: ������� ���������������, ����� ��������, � � ����� �����������
    return translationMatrix * rotationMatrix * scaleMatrix;
}
