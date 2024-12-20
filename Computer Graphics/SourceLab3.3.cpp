//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <gtc/type_ptr.hpp>
//#include <vector>
//#include "GLModel.h"
//#include "ModelLoader.h"
//#include <iostream>
//
//// ��������� ��� ����
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// ������� ��� ��������� ������� ����
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//    glViewport(0, 0, width, height);
//}
//
//int main() {
//    // ������������� GLFW
//    if (!glfwInit()) {
//        std::cerr << "Failed to initialize GLFW" << std::endl;
//        return -1;
//    }
//
//    // ��������� ���������� GLFW
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    // �������� ����
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "3D Rendering", nullptr, nullptr);
//    if (!window) {
//        std::cerr << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    // �������� ������� OpenGL � ������� GLAD
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        std::cerr << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // ��� ����� �������
//    glEnable(GL_DEPTH_TEST);
//
//    // ����� ������
//    std::vector<glm::vec2> texCoords;
//    std::vector<glm::vec3> normals;
//    std::vector<int> indices;
//    std::vector<VertexData> vertices = loadModelFromFile("CubeObj.txt", indices, texCoords, normals);
//    GLModel model(vertices, indices);
//
//    // ������� �������������
//    glm::vec3 lightPos1 = glm::vec3(8.0f, 8.0f, 2.0f);  // (�������� 1)
//    glm::vec3 lightPos2 = glm::vec3(-8.0f, 8.0f, 2.0f); // (�������� 2)
//    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f); // ����� ����
//    glm::vec3 objectColor = glm::vec3(0.6f, 0.2f, 0.2f); // ������� ������
//
//    glm::mat4 modelMatrix = glm::mat4(1.0f); // ������� ����
//    glm::mat4 viewMatrix = glm::lookAt(
//        glm::vec3(0.0f, 0.0f, 3.0f),  // ��� ������
//        glm::vec3(0.0f, 0.0f, 0.0f),  // ����� ������ ������
//        glm::vec3(0.0f, 1.0f, 0.0f)   // ������ ����
//    );
//    glm::mat4 projectionMatrix = glm::perspective(
//        glm::radians(45.0f),          // FOW
//        (float)SCR_WIDTH / SCR_HEIGHT, // ����������� �����
//        0.1f,                         // ������ ��������� ���������
//        100.0f                        // ������� ��������� ���������
//    );
//
//    // ������ ������� � �������� ������
//    GLShader* shader = model.getShader();
//    shader->bind();
//    shader->setMat4("view", viewMatrix);
//    shader->setMat4("projection", projectionMatrix);
//
//    // ������� ����� � ������
//    shader->setVec3("lightPos1", lightPos1);
//    shader->setVec3("lightPos2", lightPos2);
//    shader->setVec3("lightColor", lightColor);
//    shader->setVec3("objectColor", objectColor);
//
//    shader->release();
//
//    // ������� �������
//    enum class ModelType {
//        Cube,
//        Piramide,
//        Circle
//    };
//
//    ModelType currentModel = ModelType::Cube; // ������ ���
//    bool spacePressed = false; // ������ �� ��������
//
//    // ���� �����������
//    while (!glfwWindowShouldClose(window)) {
//        // ��������� �����
//        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spacePressed) {
//            // ������� ��������
//            switch (currentModel) {
//            case ModelType::Cube:
//                currentModel = ModelType::Piramide;
//                break;
//            case ModelType::Piramide:
//                currentModel = ModelType::Circle;
//                break;
//            case ModelType::Circle:
//                currentModel = ModelType::Cube;
//                break;
//            }
//
//            // ������ ������� � �� ����� �� ������ �����
//            indices.clear();
//            texCoords.clear();
//            normals.clear();
//
//            // ����������� �������
//            switch (currentModel) {
//            case ModelType::Cube:
//                vertices = loadModelFromFile("CubeObj.txt", indices, texCoords, normals);
//                break;
//            case ModelType::Piramide:
//                vertices = loadModelFromFile("PiramideObj.txt", indices, texCoords, normals);
//                break;
//            case ModelType::Circle:
//                vertices = loadModelFromFile("Piramida8CornerObj.txt", indices, texCoords, normals);
//                break;
//            }
//
//            // �������� ��������
//            model.updateModelData(vertices, indices);
//            spacePressed = true; // ���� ����� �� �������� ������
//        }
//
//        // ����� ���������� ������� = ����� ������ ������
//        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
//            spacePressed = false;
//        }
//
//        // ������� �������
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // ����� ����� ���
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // �������� 3D
//        float angle = (float)glfwGetTime(); // ��� �� ���� ���� �������
//        // �������� ����������� ������� �������� ������ Y
//        float cosTheta = cos(angle);
//        float sinTheta = sin(angle);
//
//        glm::mat4 rotationMatrix = {
//            {cosTheta, 0.0f, sinTheta, 0.0f},  // ������ �������
//            {0.0f, 1.0f, 0.0f, 0.0f},         // ������ �������
//            {-sinTheta, 0.0f, cosTheta, 0.0f},// ������ �������
//            {0.0f, 0.0f, 0.0f, 1.0f}          // �������� �������
//        };
//
//        modelMatrix = rotationMatrix; // ����������� ������� ������
//
//
//        // ����� ������� � ������
//        shader->bind();
//        shader->setMat4("model", modelMatrix);
//
//        // ������ ��������
//        model.draw();
//        shader->release();
//
//        // ������ �������
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // ���������� ������ GLFW
//    glfwDestroyWindow(window);
//    glfwTerminate();
//
//    return 0;
//}
