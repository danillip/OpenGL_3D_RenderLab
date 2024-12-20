#pragma once

#include "Shader.h"
#include <string>
#include <glm.hpp>
#include <glad/glad.h>

class GLShader : public Shader
{
public:
    GLShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    virtual ~GLShader();

    void bind() const override;
    void release() const override;

    void setInt(const std::string& name, int value) override;
    void setIntArray(const std::string& name, int* values, uint32_t count) override;
    void setFloat(const std::string& name, float value) override;
    void setVec2(const std::string& name, const glm::vec2& value) override;
    void setVec3(const std::string& name, const glm::vec3& value) override;
    void setVec4(const std::string& name, const glm::vec4& value) override;
    void setMat3(const std::string& name, const glm::mat3& matrix) override;
    void setMat4(const std::string& name, const glm::mat4& matrix) override;

    int attributeLocation(const std::string& attributeName);
    void enableAttributeArray(const int attributeLocation);
    void disableAttributeArray(const int attributeLocation);
    void setAttributeBuffer(const int attributeLocation, const int size, const GLenum& type, GLsizei stride, const void* pointer);

    GLuint getID() const;

    void setBool(const std::string& name, bool value) const {
        glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
    }

private:

    GLuint shaderID;

    unsigned int m_shaderId;

    bool isShaderProgramCompiledSuccess(const unsigned int shader);
    bool isCompiledShaders(const std::string& vertexSource, const std::string& fragmentSource);
    std::string loadShaderSource(const std::string& filePath);
    GLuint compileShader(GLenum shaderType, const std::string& shaderSource);
    bool m_isValid;    // флаг для проверки валидности шейдера
};
