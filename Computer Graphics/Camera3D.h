#ifndef CAMERA3D_H
#define CAMERA3D_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera3D {
public:
    // ��������� ������
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    float yaw;
    float pitch;
    float fov;
    float speed;

    // �����������
    Camera3D(float fov = 45.0f, float aspectRatio = 1.0f, float near = 0.1f, float far = 100.0f);

    // ���������� ������
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix(float aspectRatio);

    // ���������� ����� ������
    void updateYawPitch(float xOffset, float yOffset);

    // ����������� ������
    void moveForward(float velocity);
    void moveBackward(float velocity);
    void moveLeft(float velocity);
    void moveRight(float velocity);
    void moveUp(float velocity);
    void moveDown(float velocity);

    glm::vec3 getPosition() const;

private:

};

#endif
