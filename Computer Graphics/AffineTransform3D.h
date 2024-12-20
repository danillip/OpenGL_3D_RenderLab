#pragma once

#include <glm.hpp>
#include <cmath>

namespace AffineTransform3D {

    // ����������: ������� ��� ����������� ����� ����
    inline glm::mat4 translate(const glm::vec3& position) {
        glm::mat4 translation = glm::mat4(1.0f); // ��������� �������
        translation[3] = glm::vec4(position, 1.0f); // ����������� �������
        return translation;
    }

    // ���������������: ������� ��� ��������������� ����� ���� X, Y, Z
    inline glm::mat4 scale(const glm::vec3& scale) {
        glm::mat4 scaling = glm::mat4(1.0f); // ��������� �������

        // ��������� ������ ������� �������
        scaling[0] = glm::vec4(scale.x, 0.0f, 0.0f, 0.0f);  // ��������������� �� ��� X
        scaling[1] = glm::vec4(0.0f, scale.y, 0.0f, 0.0f);  // ��������������� �� ��� Y
        scaling[2] = glm::vec4(0.0f, 0.0f, scale.z, 0.0f);  // ��������������� �� ��� Z
        return scaling;
    }

    // �������� ������ ��� X: ������� �������� �� ���� 'angle' ������ X
    inline glm::mat4 rotateX(float angle) {
        float cosA = cos(angle);
        float sinA = sin(angle);

        // ������� �������� ������ ��� X
        glm::mat4 rotation = glm::mat4(1.0f);
        rotation[1] = glm::vec4(0.0f, cosA, sinA, 0.0f);  // �������� �� Y
        rotation[2] = glm::vec4(0.0f, -sinA, cosA, 0.0f); // �������� �� Z
        return rotation;
    }

    // �������� ������ ��� Y: ������� �������� �� ���� 'angle' ������ Y
    inline glm::mat4 rotateY(float angle) {
        float cosA = cos(angle);
        float sinA = sin(angle);

        // ������� �������� ������ ��� Y
        glm::mat4 rotation = glm::mat4(1.0f);
        rotation[0] = glm::vec4(cosA, 0.0f, -sinA, 0.0f); // �������� �� X
        rotation[2] = glm::vec4(sinA, 0.0f, cosA, 0.0f);  // �������� �� Z
        return rotation;
    }

    // �������� ������ ��� Z: ������� �������� �� ���� 'angle' ������ Z
    inline glm::mat4 rotateZ(float angle) {
        float cosA = cos(angle);
        float sinA = sin(angle);

        // ������� �������� ������ ��� Z
        glm::mat4 rotation = glm::mat4(1.0f);
        rotation[0] = glm::vec4(cosA, sinA, 0.0f, 0.0f);  // �������� �� X
        rotation[1] = glm::vec4(-sinA, cosA, 0.0f, 0.0f); // �������� �� Y
        return rotation;
    }

    // �������� �� ���� ����: ��������������� ������� ��������
    inline glm::mat4 rotate(const glm::vec3& rotation) {
        // �������� ������� �������� ��� ���� ����
        glm::mat4 rotX = rotateX(rotation.x);
        glm::mat4 rotY = rotateY(rotation.y);
        glm::mat4 rotZ = rotateZ(rotation.z);

        // ���������� �� ����� ��������� ������ (������� �������� �� Z, ����� Y, ����� X)
        return rotZ * rotY * rotX;
    }
}
