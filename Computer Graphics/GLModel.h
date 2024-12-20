#pragma once

#include "GLIndexBuffer.h"
#include "GLVertexBuffer.h"
#include "GLShader.h"
#include <vector>
#include "VertexData.h"
#include "GLTexture.h"

//struct VertexData {
//    glm::vec3 position; // ѕозици€ вершины
//    glm::vec2 uv;       // “екстурные координаты
//    glm::vec3 normal;   // Ќормаль вершины
//};

class GLModel {
public:
    GLModel() = default;
    GLModel(const std::vector<VertexData>& vertices, const std::vector<int>& indices);
    ~GLModel();

    // метод дл€ обновлени€ данных модели
    void updateModelData(const std::vector<VertexData>& newVertices, const std::vector<int>& newIndices);

    void draw();
    GLShader* getShader() const; // метод дл€ получени€ указател€ на шейдер

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

