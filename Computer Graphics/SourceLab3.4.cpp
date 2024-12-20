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

// размеры окна
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// камера
Camera3D camera(45.0f, static_cast<float>(SCR_WIDTH) / SCR_HEIGHT);

// режимы управления
bool isCameraMode = true; // старт с упрвления камерой
int currentModelIndex = 0; // индекс выбранной модели (0 - куб, 1 - пирамида, 2 - пирамида 8-угольная(ну типо там трапеция :) ))

//// коллбэк для изменения размера окна
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//    glViewport(0, 0, width, height);
//}
//
//// коллбэк для обработки движения мыши
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

    // Создаем окно
    GLFWWindowImpl::WindowData windowData{ "3D Rendering", SCR_WIDTH, SCR_HEIGHT };
    GLFWWindowImpl window(windowData);

    // Установка callback-функции для обработки событий
    window.setEventCallback([&](Event& e) {
        // Обработка событий через систему типов
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
            float yoffset = lastY - mouseEvent.getY(); // инвертируем для корректного движения
            lastX = mouseEvent.getX();
            lastY = mouseEvent.getY();

            camera.updateYawPitch(xoffset, yoffset);
        }

        if (e.eventType() == EventType::WindowResize) {
            auto& resizeEvent = static_cast<WindowResizeEvent&>(e);

            // Обновляем OpenGL viewport при изменении размера окна
            glViewport(0, 0, resizeEvent.getWidth(), resizeEvent.getHeight());
        }

        // Добавьте обработку других событий при необходимости
        });

    // инициализация GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST); // ВКЛ глубину

    // загрузка моделей
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<int> indices;

    // загрузка каждой модели из файлов
    std::vector<VertexData> cubeVertices = loadModelFromFile("CubeObj.txt", indices, texCoords, normals);
    GLModel cubeModel(cubeVertices, indices);

    std::vector<VertexData> piramideVertices = loadModelFromFile("PiramideObj.txt", indices, texCoords, normals);
    GLModel piramideModel(piramideVertices, indices);

    std::vector<VertexData> piramida8Vertices = loadModelFromFile("Piramida8CornerObj.txt", indices, texCoords, normals);
    GLModel piramida8Model(piramida8Vertices, indices);

    // загрузка текстур
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

    // привязываем текстуры к моделям
    cubeModel.setTexture(&piramida8Texture);  // CubeObj.txt будет использовать piramide.jpg
    piramideModel.setTexture(&piramidaTexture);  // PiramideObj.txt будет использовать piramida8.jpg
    piramida8Model.setTexture(&piramida8Texture);  // Piramida8CornerObj.txt будет использовать piramide.jpg

    // установка камеры
    glm::vec3 viewPos = camera.getPosition();
    glm::mat4 projection = camera.getProjectionMatrix(static_cast<float>(SCR_WIDTH) / SCR_HEIGHT);

    // устанавливаем захват мыши
    glfwSetInputMode(static_cast<GLFWwindow*>(window.nativeWindow()), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwSetCursorPosCallback(static_cast<GLFWwindow*>(window.nativeWindow()), mouse_callback);
    //glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(window.nativeWindow()), framebuffer_size_callback);

    // массив моделей и их матриц модели
    GLModel* models[] = { &cubeModel, &piramideModel, &piramida8Model };
    glm::mat4 modelMatrices[] = { glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f) };

    // создаем массив для трансформаций
    Transform transforms[3] = { Transform(), Transform(), Transform() };

    // основной цикл рендеринга
    float lastFrame = 0.0f;

    bool vKeyPressed = false;
    bool cKeyPressed = false;

    while (!glfwWindowShouldClose(static_cast<GLFWwindow*>(window.nativeWindow()))) {
        float currentFrame = (float)glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Обработка ввода через ControlManager
        ControlManager::processInput(static_cast<GLFWwindow*>(window.nativeWindow()), deltaTime, models, transforms, vKeyPressed, currentModelIndex, isCameraMode, camera, cKeyPressed);

        // Обновляем матрицу модели для каждой модели
        for (int i = 0; i < 3; ++i) {
            modelMatrices[i] = transforms[i].transformMatrix(); // Получаем матрицу трансформации из объекта Transform
        }

        // Обновление вида камеры
        glm::mat4 viewMatrix = camera.getViewMatrix();

        // Рендеринг
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // определяем параметры света
        glm::vec3 lightColor = glm::vec3(1.0f, 0.95f, 0.8f); // цвет света
        glm::vec3 lightDirection = glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f)); // направление света

        // шейдинг
        for (int i = 0; i < 3; ++i) {
            GLModel* model = models[i];
            GLShader* shader = model->getShader();
            shader->bind();

            // передаем матрицы
            shader->setMat4("view", viewMatrix);
            shader->setMat4("model", modelMatrices[i]);
            shader->setMat4("projection", projection);

            // переключаем активный текстурный юнит перед привязкой
            if (i == 0 || i == 2) {
                glActiveTexture(GL_TEXTURE0); // активируем текстурный юнит 0
                glBindTexture(GL_TEXTURE_2D, 0); // очистка текстуры
                piramidaTexture.bind(0);  // привязываем текстуру к текстурному юниту 0
                shader->setInt("texture1", 0);  // устанавливаем текстурный юнит в шейдер
            }
            else if (i == 1) {
                glActiveTexture(GL_TEXTURE1); // активируем текстурный юнит 1
                glBindTexture(GL_TEXTURE_2D, 0); // очистка текстуры
                piramida8Texture.bind(1); // привязываем текстуру к текстурному юниту 1
                shader->setInt("texture1", 1);  // устанавливаем текстурный юнит в шейдер
            }

            // Передаем параметры света
            shader->setVec3("lightColor", lightColor);
            shader->setVec3("lightDirection", lightDirection);  // Направление света
            shader->setVec3("viewPos", camera.getPosition());  // Позиция камеры

            // рендер модели
            model->draw();
        }

        window.update();
    }

    return 0;
}
