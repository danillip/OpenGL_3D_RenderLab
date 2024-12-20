//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include "GLShader.h"
//
//using namespace std;
//
//// Callback ��� ��������� ��������� ������
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//    glViewport(0, 0, width, height);
//}
//
//// ������
//void processInput(GLFWwindow* window) {
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//        glfwSetWindowShouldClose(window, true);
//    }
//}
//
//void renderSquare(GLShader& shader) {
//    // ������ ��������: ���������� + ����
//    float points[] = {
//        // ���������� X, Y, Z       ���� R, G, B
//        -0.5f, -0.5f, 0.0f,         1.0f, 0.0f, 0.0f, // ����� ������ �������
//         0.5f, -0.5f, 0.0f,         0.0f, 1.0f, 0.0f, // ������ ������ �������
//         0.5f,  0.5f, 0.0f,         0.0f, 0.0f, 1.0f, // ������ ������� �������
//        -0.5f,  0.5f, 0.0f,         1.0f, 1.0f, 0.0f  // ����� ������� �������
//    };
//
//    // ������� ������� EBO
//    unsigned int indices[] = {
//        0, 1, 2, // ������ �����������
//        0, 2, 3  // ������ �����������
//    };
//
//    GLuint vao, vbo, ebo;
//
//    // �������� � �������� VAO
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//
//    // �������� � �������� VBO
//    glGenBuffers(1, &vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
//
//    // �������� � �������� EBO
//    glGenBuffers(1, &ebo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    // �������� � �� ��������
//    // ������� 0: ����������
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // ������� 1: ����
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//    // ������������� ������� ����� GLShader
//    shader.bind();
//
//    // ������
//    glBindVertexArray(vao);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//    // ������ ���� ��
//    glDeleteVertexArrays(1, &vao);
//    glDeleteBuffers(1, &vbo);
//    glDeleteBuffers(1, &ebo);
//}
//
//int main() {
//    // ������������� GLFW
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    // ����� ����
//    GLFWwindow* window = glfwCreateWindow(800, 600, "2D Square", NULL, NULL);
//    if (window == NULL) {
//        cout << "Failed to create GLFW window" << endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//
//    // ������������� GLAD
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        cout << "Failed to initialize GLAD" << endl;
//        return -1;
//    }
//
//    // ������������� � ��������� ����
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    // �������� ������� ������� � ������ � ������ ��������
//    GLShader shader("vertex_shader.glsl", "fragment_shader.glsl");
//
//    // ���� ����
//    while (!glfwWindowShouldClose(window)) {
//        processInput(window);
//
//        // ������ �����
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // ������ ����������
//        renderSquare(shader);
//
//        // ���������� �������
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // Power off
//    glfwTerminate();
//    return 0;
//}
