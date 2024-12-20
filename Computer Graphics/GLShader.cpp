#include "GLShader.h"
#include <fstream>
#include <sstream>
#include <iostream>

GLShader::GLShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    // –идер и компайл шедеров
    std::string vertexSource = loadShaderSource(vertexShaderPath);
    std::string fragmentSource = loadShaderSource(fragmentShaderPath);

    // компил€ци€ шейдеров
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    // создание шейдерной проги
    m_shaderId = glCreateProgram();
    glAttachShader(m_shaderId, vertexShader);
    glAttachShader(m_shaderId, fragmentShader);
    glLinkProgram(m_shaderId);

    // ќшибка на линковку, чекер
    if (!isShaderProgramCompiledSuccess(m_shaderId)) {
        std::cerr << "Shader program linking failed!" << std::endl;
    }

    // делитаем исходники после линковки
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLShader::~GLShader()
{
    if (m_shaderId) {
        glDeleteProgram(m_shaderId);
    }
}

void GLShader::bind() const
{
    glUseProgram(m_shaderId);
}

void GLShader::release() const
{
    glUseProgram(0);
}

void GLShader::setInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(m_shaderId, name.c_str()), value);
}

void GLShader::setIntArray(const std::string& name, int* values, uint32_t count)
{
    glUniform1iv(glGetUniformLocation(m_shaderId, name.c_str()), count, values);
}

void GLShader::setFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(m_shaderId, name.c_str()), value);
}

void GLShader::setVec2(const std::string& name, const glm::vec2& value)
{
    glUniform2fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, &value[0]);
}

void GLShader::setVec3(const std::string& name, const glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, &value[0]);
}

void GLShader::setVec4(const std::string& name, const glm::vec4& value)
{
    glUniform4fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, &value[0]);
}

void GLShader::setMat3(const std::string& name, const glm::mat3& matrix)
{
    glUniformMatrix3fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void GLShader::setMat4(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

int GLShader::attributeLocation(const std::string& attributeName)
{
    return glGetAttribLocation(m_shaderId, attributeName.c_str());
}

void GLShader::enableAttributeArray(const int attributeLocation)
{
    glEnableVertexAttribArray(attributeLocation);
}

void GLShader::disableAttributeArray(const int attributeLocation)
{
    glDisableVertexAttribArray(attributeLocation);
}

void GLShader::setAttributeBuffer(const int attributeLocation, const int size, const GLenum& type, GLsizei stride, const void* pointer)
{
    glVertexAttribPointer(attributeLocation, size, type, GL_FALSE, stride, pointer);
}

std::string GLShader::loadShaderSource(const std::string& filePath)
{
    std::ifstream shaderFile(filePath);
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}

GLuint GLShader::compileShader(GLenum shaderType, const std::string& shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    const char* source = shaderSource.c_str();
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    // „екер ошибок компил€ции
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed\n" << infoLog << std::endl;
    }
    return shader;
}

bool GLShader::isShaderProgramCompiledSuccess(const unsigned int shader)
{
    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    return success;
}

GLuint GLShader::getID() const {
    return shaderID; // ¬озвращаем ID шейдера
}