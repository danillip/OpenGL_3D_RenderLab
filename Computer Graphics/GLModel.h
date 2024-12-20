#pragma once

#include "GLIndexBuffer.h"
#include "GLVertexBuffer.h"
#include "GLShader.h"
#include <vector>
#include "VertexData.h"
#include "GLTexture.h"

//struct VertexData {
//    glm::vec3 position; // ������� �������
//    glm::vec2 uv;       // ���������� ����������
//    glm::vec3 normal;   // ������� �������
//};

class GLModel {
public:
    GLModel() = default;
    GLModel(const std::vector<VertexData>& vertices, const std::vector<int>& indices);
    ~GLModel();

    // ����� ��� ���������� ������ ������
    void updateModelData(const std::vector<VertexData>& newVertices, const std::vector<int>& newIndices);

    void draw();
    GLShader* getShader() const; // ����� ��� ��������� ��������� �� ������

    const std::vector<glm::vec3>& getNormals() const {
        return normals;
    }

    void setTexture(GLTexture* m_texture);

private:
    void initialize();

    GLShader* m_modelShaderProgram = nullptr;

    std::vector<VertexData> m_vertices;
    std::vector<int> m_indices;

    GLIndexBuffer m_indexBuffer;
    GLVertexBuffer m_vertexBuffer;

    std::vector<glm::vec3> normals;

    GLTexture* m_texture;
};

