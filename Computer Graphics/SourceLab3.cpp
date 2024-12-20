//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
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
//void renderSquare() {
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
//    // Шейдеры(кал калыч)
//    const char* vertex_shader =
//        "#version 330 core\n"
//        "layout (location = 0) in vec3 aPos;\n"
//        "layout (location = 1) in vec3 aColor;\n"
//        "out vec3 ourColor;\n"
//        "void main() {\n"
//        "    gl_Position = vec4(aPos, 1.0);\n"
//        "    ourColor = aColor;\n"
//        "}\n";
//
//    const char* fragment_shader =
//        "#version 330 core\n"
//        "in vec3 ourColor;\n"
//        "out vec4 fragColor;\n"
//        "void main() {\n"
//        "    fragColor = vec4(ourColor, 1.0);\n"
//        "}\n";
//
//    // Компйл шейдеров
//    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vs, 1, &vertex_shader, NULL);
//    glCompileShader(vs);
//
//    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fs, 1, &fragment_shader, NULL);
//    glCompileShader(fs);
//
//    // Это вроде создание и линковка шейдерной
//    GLuint shader_program = glCreateProgram();
//    glAttachShader(shader_program, vs);
//    glAttachShader(shader_program, fs);
//    glLinkProgram(shader_program);
//
//    // А это как я понял использование шейдерной программы
//    glUseProgram(shader_program);
//
//    // Удаление шейдеров т.к. они уже не нужны, откомпили будьте добры почистить
//    glDeleteShader(vs);
//    glDeleteShader(fs);
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
//    // Мейн цикл
//    while (!glfwWindowShouldClose(window)) {
//        processInput(window);
//
//        // Чистим скрин
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // Рендринг квадратика
//        renderSquare();
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
