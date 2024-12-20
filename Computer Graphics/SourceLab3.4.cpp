#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>
#include "GLModel.h"
#include "ModelLoader.h"
#include "GLFWWindowImpl.h"
#include "Camera3D.h"
#include "Transform.h"
#include "KeyCode.h"
#include "ControlManager.h"
#include "stb_image.h"
#include "GLTexture.h"

// ������� ����
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// ������
Camera3D camera(45.0f, static_cast<float>(SCR_WIDTH) / SCR_HEIGHT);

// ������ ����������
bool isCameraMode = true; // ����� � ��������� �������
int currentModelIndex = 0; // ������ ��������� ������ (0 - ���, 1 - ��������, 2 - �������� 8-��������(�� ���� ��� �������� :) ))

//// ������� ��� ��������� ������� ����
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//    glViewport(0, 0, width, height);
//}
//
//// ������� ��� ��������� �������� ����
//void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//    static float lastX = SCR_WIDTH / 2.0f, lastY = SCR_HEIGHT / 2.0f;
//    static bool firstMouse = true;
//
//    if (firstMouse) {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos;
//    lastX = xpos;
//    lastY = ypos;
//
//    camera.updateYawPitch(xoffset, yoffset);
//}

int main() {
    setlocale(LC_ALL, "Ru");

    // ������� ����
    GLFWWindowImpl::WindowData windowData{ "3D Rendering", SCR_WIDTH, SCR_HEIGHT };
    GLFWWindowImpl window(windowData);

    // ��������� callback-������� ��� ��������� �������
    window.setEventCallback([&](Event& e) {
        // ��������� ������� ����� ������� �����
        if (e.eventType() == EventType::MouseMoved) {
            auto& mouseEvent = static_cast<MouseMovedEvent&>(e);

            static float lastX = SCR_WIDTH / 2.0f, lastY = SCR_HEIGHT / 2.0f;
            static bool firstMouse = true;

            if (firstMouse) {
                lastX = mouseEvent.getX();
                lastY = mouseEvent.getY();
                firstMouse = false;
            }

            float xoffset = mouseEvent.getX() - lastX;
            float yoffset = lastY - mouseEvent.getY(); // ����������� ��� ����������� ��������
            lastX = mouseEvent.getX();
            lastY = mouseEvent.getY();

            camera.updateYawPitch(xoffset, yoffset);
        }

        if (e.eventType() == EventType::WindowResize) {
            auto& resizeEvent = static_cast<WindowResizeEvent&>(e);

            // ��������� OpenGL viewport ��� ��������� ������� ����
            glViewport(0, 0, resizeEvent.getWidth(), resizeEvent.getHeight());
        }

        // �������� ��������� ������ ������� ��� �������������
        });

    // ������������� GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST); // ��� �������

    // �������� �������
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<int> indices;

    // �������� ������ ������ �� ������
    std::vector<VertexData> cubeVertices = loadModelFromFile("CubeObj.txt", indices, texCoords, normals);
    GLModel cubeModel(cubeVertices, indices);

    std::vector<VertexData> piramideVertices = loadModelFromFile("PiramideObj.txt", indices, texCoords, normals);
    GLModel piramideModel(piramideVertices, indices);

    std::vector<VertexData> piramida8Vertices = loadModelFromFile("Piramida8CornerObj.txt", indices, texCoords, normals);
    GLModel piramida8Model(piramida8Vertices, indices);

    // �������� �������
    GLTexture piramida8Texture;
    std::cout << "Loading textures..." << std::endl;
    if (!piramida8Texture.loadFromFile("piramide.jpg")) {
        std::cerr << "Failed to load piramide.jpg!" << std::endl;
        return -1;
    }
    std::cout << "Loaded piramide.jpg successfully!" << std::endl;

    GLTexture piramidaTexture;
    if (!piramidaTexture.loadFromFile("piramida8.jpg")) {
        std::cerr << "Failed to load piramida8.jpg!" << std::endl;
        return -1;
    }
    std::cout << "Loaded piramida8.jpg successfully!" << std::endl;

    // ����������� �������� � �������
    cubeModel.setTexture(&piramida8Texture);  // CubeObj.txt ����� ������������ piramide.jpg
    piramideModel.setTexture(&piramidaTexture);  // PiramideObj.txt ����� ������������ piramida8.jpg
    piramida8Model.setTexture(&piramida8Texture);  // Piramida8CornerObj.txt ����� ������������ piramide.jpg

    // ��������� ������
    glm::vec3 viewPos = camera.getPosition();
    glm::mat4 projection = camera.getProjectionMatrix(static_cast<float>(SCR_WIDTH) / SCR_HEIGHT);

    // ������������� ������ ����
    glfwSetInputMode(static_cast<GLFWwindow*>(window.nativeWindow()), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwSetCursorPosCallback(static_cast<GLFWwindow*>(window.nativeWindow()), mouse_callback);
    //glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(window.nativeWindow()), framebuffer_size_callback);

    // ������ ������� � �� ������ ������
    GLModel* models[] = { &cubeModel, &piramideModel, &piramida8Model };
    glm::mat4 modelMatrices[] = { glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f) };

    // ������� ������ ��� �������������
    Transform transforms[3] = { Transform(), Transform(), Transform() };

    // �������� ���� ����������
    float lastFrame = 0.0f;

    bool vKeyPressed = false;
    bool cKeyPressed = false;

    while (!glfwWindowShouldClose(static_cast<GLFWwindow*>(window.nativeWindow()))) {
        float currentFrame = (float)glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // ��������� ����� ����� ControlManager
        ControlManager::processInput(static_cast<GLFWwindow*>(window.nativeWindow()), deltaTime, models, transforms, vKeyPressed, currentModelIndex, isCameraMode, camera, cKeyPressed);

        // ��������� ������� ������ ��� ������ ������
        for (int i = 0; i < 3; ++i) {
            modelMatrices[i] = transforms[i].transformMatrix(); // �������� ������� ������������� �� ������� Transform
        }

        // ���������� ���� ������
        glm::mat4 viewMatrix = camera.getViewMatrix();

        // ���������
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ���������� ��������� �����
        glm::vec3 lightColor = glm::vec3(1.0f, 0.95f, 0.8f); // ���� �����
        glm::vec3 lightDirection = glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f)); // ����������� �����

        // �������
        for (int i = 0; i < 3; ++i) {
            GLModel* model = models[i];
            GLShader* shader = model->getShader();
            shader->bind();

            // �������� �������
            shader->setMat4("view", viewMatrix);
            shader->setMat4("model", modelMatrices[i]);
            shader->setMat4("projection", projection);

            // ����������� �������� ���������� ���� ����� ���������
            if (i == 0 || i == 2) {
                glActiveTexture(GL_TEXTURE0); // ���������� ���������� ���� 0
                glBindTexture(GL_TEXTURE_2D, 0); // ������� ��������
                piramidaTexture.bind(0);  // ����������� �������� � ����������� ����� 0
                shader->setInt("texture1", 0);  // ������������� ���������� ���� � ������
            }
            else if (i == 1) {
                glActiveTexture(GL_TEXTURE1); // ���������� ���������� ���� 1
                glBindTexture(GL_TEXTURE_2D, 0); // ������� ��������
                piramida8Texture.bind(1); // ����������� �������� � ����������� ����� 1
                shader->setInt("texture1", 1);  // ������������� ���������� ���� � ������
            }

            // �������� ��������� �����
            shader->setVec3("lightColor", lightColor);
            shader->setVec3("lightDirection", lightDirection);  // ����������� �����
            shader->setVec3("viewPos", camera.getPosition());  // ������� ������

            // ������ ������
            model->draw();
        }

        window.update();
    }

    return 0;
}
