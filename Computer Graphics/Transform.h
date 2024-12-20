#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>

class Transform
{
public:
    Transform();
    ~Transform() = default;

    // ������ ��������� ����������
    void setPosition(const glm::vec3& position);
    void setRotation(const glm::vec3& rotation);
    void setScale(const glm::vec3& scale);

    // ������ ��������� ����������
    const glm::vec3& position() const;
    const glm::vec3& rotation() const;
    const glm::vec3& scale() const;

    // ������ ��� ��������� ��������
    void setRotationSpeed(float speed);
    void setScaleSpeed(float speed);

    // ������ �������� ������� �������������
    glm::mat4 transformMatrix() const;

private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
    float m_rotationSpeed;  // ���������� ��� �������� ��������
    float m_scaleSpeed;     // ���������� ��� �������� ���������������
};
