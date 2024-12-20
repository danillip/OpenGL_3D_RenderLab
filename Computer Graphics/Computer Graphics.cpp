//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//
//using namespace std;
//
//// Переменные для хранения начала и конца линии
//bool isDrawing = false;
//float startX = 0.0f, startY = 0.0f;
//float endX = 0.0f, endY = 0.0f;
//
//// Цвет линии
//float lineColor[3] = { 1.0f, 1.0f, 1.0f };
//
//// Drawing the primitive
//void renderPrimitives();
//// Handle user input
//void processInput(GLFWwindow* window);
//void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
//
//int main()
//{
//    // Initialize GLFW
//    if (!glfwInit()) {
//        std::cerr << "Не удалось инициализировать GLFW" << std::endl;
//        return -1;
//    }
//
//    // Create a GLFW window
//    GLFWwindow* window = glfwCreateWindow(800, 600, "Test OpenGL", nullptr, nullptr);
//    if (!window) {
//        std::cerr << "Не удалось создать окно GLFW" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//
//    // Button mouse callback
//    glfwSetMouseButtonCallback(window, mouseButtonCallback);
//
//    // Main loop
//    while (!glfwWindowShouldClose(window)) {
//        // Input processing
//        processInput(window);
//
//        // Drawing the primitive
//        renderPrimitives();
//
//        // Window update
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // Destroying a window and freeing resources
//    glfwDestroyWindow(window);
//    glfwTerminate();
//    return 0;
//}
//
//void renderPrimitives() {
//    glClear(GL_COLOR_BUFFER_BIT);
//    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
//
//    if (isDrawing) {
//        glColor3f(lineColor[0], lineColor[1], lineColor[2]);
//        glBegin(GL_LINES);
//        glVertex2f(startX, startY);
//        glVertex2f(endX, endY);
//        glEnd();
//    }
//}
//
//void processInput(GLFWwindow* window)
//{
//    // Изменение цвета линии при нажатии на 'C'
//    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
//    {
//        // Генерация случайного цвета для линии
//        lineColor[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//        lineColor[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//        lineColor[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//    }
//}
//
//void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
//{
//    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
//    {
//        // Получаем координаты мыши
//        double xpos, ypos;
//        glfwGetCursorPos(window, &xpos, &ypos);
//
//        // Преобразуем координаты в OpenGL (-1 до 1 по осям X и Y)
//        int width, height;
//        glfwGetWindowSize(window, &width, &height);
//        xpos = (xpos / width) * 2.0 - 1.0;
//        ypos = 1.0 - (ypos / height) * 2.0;
//
//        // Если линия еще не рисуется, задаем начало, иначе конец
//        if (!isDrawing) {
//            startX = static_cast<float>(xpos);
//            startY = static_cast<float>(ypos);
//            isDrawing = true;
//        }
//        else {
//            endX = static_cast<float>(xpos);
//            endY = static_cast<float>(ypos);
//            isDrawing = true; // Линия завершена
//        }
//    }
//}
