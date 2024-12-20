//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
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
//void renderSquare() {
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
//    // �������(��� �����)
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
//    // ������ ��������
//    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vs, 1, &vertex_shader, NULL);
//    glCompileShader(vs);
//
//    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fs, 1, &fragment_shader, NULL);
//    glCompileShader(fs);
//
//    // ��� ����� �������� � �������� ���������
//    GLuint shader_program = glCreateProgram();
//    glAttachShader(shader_program, vs);
//    glAttachShader(shader_program, fs);
//    glLinkProgram(shader_program);
//
//    // � ��� ��� � ����� ������������� ��������� ���������
//    glUseProgram(shader_program);
//
//    // �������� �������� �.�. ��� ��� �� �����, ��������� ������ ����� ���������
//    glDeleteShader(vs);
//    glDeleteShader(fs);
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
//    // ���� ����
//    while (!glfwWindowShouldClose(window)) {
//        processInput(window);
//
//        // ������ �����
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // �������� ����������
//        renderSquare();
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
