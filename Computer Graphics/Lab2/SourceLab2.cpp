//#include "../pch.h"
//#include "Render2D.h"
//#include "Loader.h"
//#include "Model2D.h"
//#include "AffineTransform.h"
//#include <vector>
//
//const int NUM_MODELS = 3;
//std::vector<Model2D*> models;
//int currentModelIndex = 0; // Индекс текущей модели
//
//// Переменная для отслеживания текущего типа преобразования (1 - масштаб, 2 - перенос, 3 - поворот)
//int currentTransformation = 0;
//
//void applyTransformation(Model2D* model) {
//    // Определение шага преобразования
//    const float scaleStep = 1.1f;
//    const float translateStep = 0.1f;
//    const float rotateStep = 5.0f;
//
//    // В зависимости от текущего преобразования и нажатой клавиши, выполняем действие
//    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
//        if (currentTransformation == 1) model->scale(scaleStep);                // Увеличение
//        if (currentTransformation == 2) model->translate(glm::vec2(0.0f, translateStep)); // Перемещение вверх
//        if (currentTransformation == 3) model->rotate(rotateStep);              // Поворот по часовой
//    }
//    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
//        if (currentTransformation == 1) model->scale(1.0f / scaleStep);         // Уменьшение
//        if (currentTransformation == 2) model->translate(glm::vec2(0.0f, -translateStep)); // Перемещение вниз
//        if (currentTransformation == 3) model->rotate(-rotateStep);             // Поворот против часовой
//    }
//    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
//        if (currentTransformation == 2) model->translate(glm::vec2(-translateStep, 0.0f)); // Перемещение влево
//        if (currentTransformation == 3) model->rotate(rotateStep);              // Поворот по часовой
//    }
//    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
//        if (currentTransformation == 2) model->translate(glm::vec2(translateStep, 0.0f)); // Перемещение вправо
//        if (currentTransformation == 3) model->rotate(-rotateStep);             // Поворот против часовой
//    }
//}
//
//void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//    if (action == GLFW_PRESS) {
//        // Обработка переключения моделей по клавише C
//        if (key == GLFW_KEY_C) {
//            currentModelIndex = (currentModelIndex + 1) % NUM_MODELS;
//        }
//        // Обработка выбора типа преобразования
//        if (key == GLFW_KEY_1) currentTransformation = 1; // Масштабирование
//        if (key == GLFW_KEY_2) currentTransformation = 2; // Трансляция
//        if (key == GLFW_KEY_3) currentTransformation = 3; // Поворот
//    }
//}
//
//void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
//    // Заглушка
//}
//
//void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
//    // Заглушка
//}
//
//int main() {
//    // Инициализация GLFW
//    if (!glfwInit()) {
//        return -1;
//    }
//
//    // Создание окна
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
//    // Создание рендерера
//    Render2D renderer;
//
//    // Загрузка моделей
//    models.push_back(new Model2D(Loader("model1.txt").vertices(), Loader("model1.txt").indices()));
//    models.push_back(new Model2D(Loader("model2.txt").vertices(), Loader("model2.txt").indices()));
//    models.push_back(new Model2D(Loader("model3.txt").vertices(), Loader("model3.txt").indices()));
//
//    // Добавление первой модели в рендерер
//    renderer.addObject(models[currentModelIndex]);
//
//    // Главный цикл
//    while (!glfwWindowShouldClose(window)) {
//        // Очистка окна
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // Применяем преобразования к текущей модели
//        applyTransformation(models[currentModelIndex]);
//
//        // Отрисовка текущей модели
//        renderer.draw();
//
//        // Обработка событий
//        glfwPollEvents();
//
//        // Проверка нажатия клавиши C для переключения модели
//        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
//            renderer = Render2D(); // Сбрасываем рендерер
//            renderer.addObject(models[currentModelIndex]); // Добавляем новую модель
//        }
//
//        // Обновление окна
//        glfwSwapBuffers(window);
//    }
//
//    // Освобождение ресурсов
//    for (auto model : models) {
//        delete model; // Освобождение памяти для каждой модели
//    }
//
//    glfwDestroyWindow(window);
//    glfwTerminate();
//    return 0;
//}
