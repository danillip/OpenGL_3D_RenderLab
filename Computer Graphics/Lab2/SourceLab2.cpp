//#include "../pch.h"
//#include "Render2D.h"
//#include "Loader.h"
//#include "Model2D.h"
//#include "AffineTransform.h"
//#include <vector>
//
//const int NUM_MODELS = 3;
//std::vector<Model2D*> models;
//int currentModelIndex = 0; // ������ ������� ������
//
//// ���������� ��� ������������ �������� ���� �������������� (1 - �������, 2 - �������, 3 - �������)
//int currentTransformation = 0;
//
//void applyTransformation(Model2D* model) {
//    // ����������� ���� ��������������
//    const float scaleStep = 1.1f;
//    const float translateStep = 0.1f;
//    const float rotateStep = 5.0f;
//
//    // � ����������� �� �������� �������������� � ������� �������, ��������� ��������
//    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
//        if (currentTransformation == 1) model->scale(scaleStep);                // ����������
//        if (currentTransformation == 2) model->translate(glm::vec2(0.0f, translateStep)); // ����������� �����
//        if (currentTransformation == 3) model->rotate(rotateStep);              // ������� �� �������
//    }
//    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
//        if (currentTransformation == 1) model->scale(1.0f / scaleStep);         // ����������
//        if (currentTransformation == 2) model->translate(glm::vec2(0.0f, -translateStep)); // ����������� ����
//        if (currentTransformation == 3) model->rotate(-rotateStep);             // ������� ������ �������
//    }
//    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
//        if (currentTransformation == 2) model->translate(glm::vec2(-translateStep, 0.0f)); // ����������� �����
//        if (currentTransformation == 3) model->rotate(rotateStep);              // ������� �� �������
//    }
//    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
//        if (currentTransformation == 2) model->translate(glm::vec2(translateStep, 0.0f)); // ����������� ������
//        if (currentTransformation == 3) model->rotate(-rotateStep);             // ������� ������ �������
//    }
//}
//
//void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//    if (action == GLFW_PRESS) {
//        // ��������� ������������ ������� �� ������� C
//        if (key == GLFW_KEY_C) {
//            currentModelIndex = (currentModelIndex + 1) % NUM_MODELS;
//        }
//        // ��������� ������ ���� ��������������
//        if (key == GLFW_KEY_1) currentTransformation = 1; // ���������������
//        if (key == GLFW_KEY_2) currentTransformation = 2; // ����������
//        if (key == GLFW_KEY_3) currentTransformation = 3; // �������
//    }
//}
//
//void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
//    // ��������
//}
//
//void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
//    // ��������
//}
//
//int main() {
//    // ������������� GLFW
//    if (!glfwInit()) {
//        return -1;
//    }
//
//    // �������� ����
//    GLFWwindow* window = glfwCreateWindow(800, 600, "2D Model Renderer", nullptr, nullptr);
//    if (!window) {
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//    glfwSetKeyCallback(window, keyCallback);
//    glfwSetMouseButtonCallback(window, mouseButtonCallback);
//    glfwSetCursorPosCallback(window, cursorPosCallback);
//
//    // �������� ���������
//    Render2D renderer;
//
//    // �������� �������
//    models.push_back(new Model2D(Loader("model1.txt").vertices(), Loader("model1.txt").indices()));
//    models.push_back(new Model2D(Loader("model2.txt").vertices(), Loader("model2.txt").indices()));
//    models.push_back(new Model2D(Loader("model3.txt").vertices(), Loader("model3.txt").indices()));
//
//    // ���������� ������ ������ � ��������
//    renderer.addObject(models[currentModelIndex]);
//
//    // ������� ����
//    while (!glfwWindowShouldClose(window)) {
//        // ������� ����
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // ��������� �������������� � ������� ������
//        applyTransformation(models[currentModelIndex]);
//
//        // ��������� ������� ������
//        renderer.draw();
//
//        // ��������� �������
//        glfwPollEvents();
//
//        // �������� ������� ������� C ��� ������������ ������
//        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
//            renderer = Render2D(); // ���������� ��������
//            renderer.addObject(models[currentModelIndex]); // ��������� ����� ������
//        }
//
//        // ���������� ����
//        glfwSwapBuffers(window);
//    }
//
//    // ������������ ��������
//    for (auto model : models) {
//        delete model; // ������������ ������ ��� ������ ������
//    }
//
//    glfwDestroyWindow(window);
//    glfwTerminate();
//    return 0;
//}
