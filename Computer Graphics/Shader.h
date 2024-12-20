#pragma once

#include <string>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>  // получение указателей на матрицы и вектора

class Shader
{
public:
    virtual ~Shader() = default;

    // привязка и освобождение шейдера
    virtual void bind() const = 0;
    virtual void release() const = 0;

    // установка значений для различных типов данных
    virtual void setInt(const std::string& name, int value) = 0;
    virtual void setIntArray(const std::string& name, int* values, uint32_t count) = 0;
    virtual void setFloat(const std::string& name, float value) = 0;
    virtual void setVec2(const std::string& name, const glm::vec2& value) = 0;
    virtual void setVec3(const std::string& name, const glm::vec3& value) = 0;
    virtual void setVec4(const std::string& name, const glm::vec4& value) = 0;
    virtual void setMat3(const std::string& name, const glm::mat3& matrix) = 0;
    virtual void setMat4(const std::string& name, const glm::mat4& matrix) = 0;

protected:
    // перечисление типов шейдеров
    enum class ShaderType
    {
        Vertex = 0,
        Fragment
    };
};
