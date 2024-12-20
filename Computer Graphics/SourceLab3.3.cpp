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
//// Константы для окна
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// Коллбэк для изменения размера окна
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//    glViewport(0, 0, width, height);
//}
//
//int main() {
//    // Инициализация GLFW
//    if (!glfwInit()) {
//        std::cerr << "Failed to initialize GLFW" << std::endl;
//        return -1;
//    }
//
//    // Установка параметров GLFW
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    // Создание окна
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
//    // Загрузка функций OpenGL с помощью GLAD
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        std::cerr << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // ВКЛ теста глубины
//    glEnable(GL_DEPTH_TEST);
//
//    // Креэт модели
//    std::vector<glm::vec2> texCoords;
//    std::vector<glm::vec3> normals;
//    std::vector<int> indices;
//    std::vector<VertexData> vertices = loadModelFromFile("CubeObj.txt", indices, texCoords, normals);
//    GLModel model(vertices, indices);
//
//    // Матрицы трансформации
//    glm::vec3 lightPos1 = glm::vec3(8.0f, 8.0f, 2.0f);  // (лампочка 1)
//    glm::vec3 lightPos2 = glm::vec3(-8.0f, 8.0f, 2.0f); // (лампочка 2)
//    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f); // белый свет
//    glm::vec3 objectColor = glm::vec3(0.6f, 0.2f, 0.2f); // красный объект
//
//    glm::mat4 modelMatrix = glm::mat4(1.0f); // Мировая матр
//    glm::mat4 viewMatrix = glm::lookAt(
//        glm::vec3(0.0f, 0.0f, 3.0f),  // Поз камеры
//        glm::vec3(0.0f, 0.0f, 0.0f),  // точка обзора камеры
//        glm::vec3(0.0f, 1.0f, 0.0f)   // вектор верх
//    );
//    glm::mat4 projectionMatrix = glm::perspective(
//        glm::radians(45.0f),          // FOW
//        (float)SCR_WIDTH / SCR_HEIGHT, // соотношение стоон
//        0.1f,                         // бизкая плоскость отсечения
//        100.0f                        // дальняя плоскость отсечения
//    );
//
//    // Инстал шедеров и передача матриц
//    GLShader* shader = model.getShader();
//    shader->bind();
//    shader->setMat4("view", viewMatrix);
//    shader->setMat4("projection", projectionMatrix);
//
//    // Позиции света в шейдер
//    shader->setVec3("lightPos1", lightPos1);
//    shader->setVec3("lightPos2", lightPos2);
//    shader->setVec3("lightColor", lightColor);
//    shader->setVec3("objectColor", objectColor);
//
//    shader->release();
//
//    // Свитчер моделей
//    enum class ModelType {
//        Cube,
//        Piramide,
//        Circle
//    };
//
//    ModelType currentModel = ModelType::Cube; // начало Куб
//    bool spacePressed = false; // слежка за пробелом
//
//    // МЕЙН ОТРОСОВОЧКА
//    while (!glfwWindowShouldClose(window)) {
//        // Считываем клаву
//        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spacePressed) {
//            // свичуем модельки
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
//            // чистка векторо а то могет за предел выйти
//            indices.clear();
//            texCoords.clear();
//            normals.clear();
//
//            // подгрузочка моделей
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
//            // андейтим модельку
//            model.updateModelData(vertices, indices);
//            spacePressed = true; // чтоб много не нажимать пробел
//        }
//
//        // чекер отпускания клавиши = можно тыкать дальеш
//        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
//            spacePressed = false;
//        }
//
//        // очистка буферов
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Вроде серый фон
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // ротатион 3D
//        float angle = (float)glfwGetTime(); // что то типо угла времени
//        // создание собственной матрицы поворота вокруг Y
//        float cosTheta = cos(angle);
//        float sinTheta = sin(angle);
//
//        glm::mat4 rotationMatrix = {
//            {cosTheta, 0.0f, sinTheta, 0.0f},  // Первый столбец
//            {0.0f, 1.0f, 0.0f, 0.0f},         // Второй столбец
//            {-sinTheta, 0.0f, cosTheta, 0.0f},// Третий столбец
//            {0.0f, 0.0f, 0.0f, 1.0f}          // Четвёртый столбец
//        };
//
//        modelMatrix = rotationMatrix; // Присваиваем матрицу модели
//
//
//        // новая матрица в шейдер
//        shader->bind();
//        shader->setMat4("model", modelMatrix);
//
//        // рисуем модельку
//        model.draw();
//        shader->release();
//
//        // обнова буферов
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // Завершение работы GLFW
//    glfwDestroyWindow(window);
//    glfwTerminate();
//
//    return 0;
//}
