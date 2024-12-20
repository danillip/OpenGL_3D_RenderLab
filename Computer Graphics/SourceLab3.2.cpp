//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include "GLShader.h"
//
//using namespace std;
//
//// Callback для настройки изменения окошка
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//    glViewport(0, 0, width, height);
//}
//
//// Вводим
//void processInput(GLFWwindow* window) {
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//        glfwSetWindowShouldClose(window, true);
//    }
//}
//
//void renderSquare(GLShader& shader) {
//    // Данные квадрата: координаты + цвет
//    float points[] = {
//        // Координаты X, Y, Z       Цвет R, G, B
//        -0.5f, -0.5f, 0.0f,         1.0f, 0.0f, 0.0f, // Левая нижняя вершина
//         0.5f, -0.5f, 0.0f,         0.0f, 1.0f, 0.0f, // Правая нижняя вершина
//         0.5f,  0.5f, 0.0f,         0.0f, 0.0f, 1.0f, // Правая верхняя вершина
//        -0.5f,  0.5f, 0.0f,         1.0f, 1.0f, 0.0f  // Левая верхняя вершина
//    };
//
//    // Индексы рендера EBO
//    unsigned int indices[] = {
//        0, 1, 2, // Первый треугольник
//        0, 2, 3  // Второй треугольник
//    };
//
//    GLuint vao, vbo, ebo;
//
//    // Гынерейт и привязка VAO
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//
//    // Гынерейт и привязка VBO
//    glGenBuffers(1, &vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
//
//    // Гынерейт и привязка EBO
//    glGenBuffers(1, &ebo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    // Атрибуты и их указания
//    // Атрибут 0: координаты
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // Атрибут 1: цвет
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//    // Использование шейдера через GLShader
//    shader.bind();
//
//    // Рендер
//    glBindVertexArray(vao);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//    // Чистим ресы пк
//    glDeleteVertexArrays(1, &vao);
//    glDeleteBuffers(1, &vbo);
//    glDeleteBuffers(1, &ebo);
//}
//
//int main() {
//    // Инициализация GLFW
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    // Креэт окна
//    GLFWwindow* window = glfwCreateWindow(800, 600, "2D Square", NULL, NULL);
//    if (window == NULL) {
//        cout << "Failed to create GLFW window" << endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//
//    // Инициализация GLAD
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        cout << "Failed to initialize GLAD" << endl;
//        return -1;
//    }
//
//    // Инициализация с размерами окна
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    // Создание объекта шейдера с путями к файлам шейдеров
//    GLShader shader("vertex_shader.glsl", "fragment_shader.glsl");
//
//    // Мейн цикл
//    while (!glfwWindowShouldClose(window)) {
//        processInput(window);
//
//        // Чистим экран
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // Рендер квадратика
//        renderSquare(shader);
//
//        // Обновление баффера
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // Power off
//    glfwTerminate();
//    return 0;
//}
