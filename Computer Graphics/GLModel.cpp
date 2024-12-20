#include "GLModel.h"
#include <iostream>

GLModel::GLModel(const std::vector<VertexData>& vertices, const std::vector<int>& indices)
    : m_vertices(vertices), m_indices(indices) {
    initialize();
}

GLModel::~GLModel() {
    if (m_indexBuffer.isCreated()) {
        m_indexBuffer.destroy();
        std::cout << "Index buffer destroyed." << std::endl;
    }

    if (m_vertexBuffer.isCreated()) {
        m_vertexBuffer.destroy();
        std::cout << "Vertex buffer destroyed." << std::endl;
    }

    delete m_modelShaderProgram;
    std::cout << "Shader program deleted." << std::endl;
}

void GLModel::setTexture(GLTexture* texture) {
    this->m_texture = m_texture;
}


void GLModel::draw() {
    if (!m_modelShaderProgram) {
        std::cerr << "Shader program is not initialized!" << std::endl;
        return;
    }

    // Привязка текстуры (если задана)
    if (m_texture) {
        m_texture->bind();
    }

    m_modelShaderProgram->bind();
    m_vertexBuffer.bind();

    // Настройка атрибутов вершин
    m_modelShaderProgram->enableAttributeArray(0); // Позиция
    m_modelShaderProgram->setAttributeBuffer(0, 3, GL_FLOAT, sizeof(VertexData), (void*)offsetof(VertexData, position));

    m_modelShaderProgram->enableAttributeArray(1); // Текстурные координаты
    m_modelShaderProgram->setAttributeBuffer(1, 2, GL_FLOAT, sizeof(VertexData), (void*)offsetof(VertexData, texCoord));

    m_modelShaderProgram->enableAttributeArray(2); // Нормаль
    m_modelShaderProgram->setAttributeBuffer(2, 3, GL_FLOAT, sizeof(VertexData), (void*)offsetof(VertexData, normal));

    m_indexBuffer.bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
    m_indexBuffer.release();

    // Отключение атрибутов вершин
    m_modelShaderProgram->disableAttributeArray(0);
    m_modelShaderProgram->disableAttributeArray(1);
    m_modelShaderProgram->disableAttributeArray(2);

    m_vertexBuffer.release();
    m_modelShaderProgram->release();

    // Отвязка текстуры (если задана)
    if (m_texture) {
        m_texture->unbind();
    }

    //// Диагностика нормалей
    //for (const auto& vertex : m_vertices) {
    //    std::cout << "Normal: " << vertex.normal.x << ", " << vertex.normal.y << ", " << vertex.normal.z << std::endl;
    //}
}

void GLModel::updateModelData(const std::vector<VertexData>& newVertices, const std::vector<int>& newIndices) {
    m_vertices = newVertices;
    m_indices = newIndices;

    // Обновляем вершинный и индексный буферы
    m_vertexBuffer.bind();
    m_vertexBuffer.allocate(m_vertices.data(), static_cast<uint32_t>(m_vertices.size() * sizeof(VertexData)));
    m_vertexBuffer.release();

    m_indexBuffer.bind();
    m_indexBuffer.allocate(m_indices.data(), static_cast<uint32_t>(m_indices.size() * sizeof(int)));
    m_indexBuffer.release();

    std::cout << "Model data updated." << std::endl;
}


void GLModel::initialize() {
    // Создание и настройка вершинного буфера
    m_vertexBuffer.create();
    m_vertexBuffer.bind();
    m_vertexBuffer.allocate(m_vertices.data(), static_cast<uint32_t>(m_vertices.size() * sizeof(VertexData)));
    m_vertexBuffer.release();

    std::cout << "Vertex buffer created and data allocated." << std::endl;

    // Создание и настройка индексного буфера
    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(m_indices.data(), static_cast<uint32_t>(m_indices.size() * sizeof(int)));
    m_indexBuffer.release();

    std::cout << "Index buffer created and data allocated." << std::endl;

    // инициализация шейдерной программы
    if (m_modelShaderProgram) {
        delete m_modelShaderProgram; // Удаление предыдущего шейдера если он конечно есть, надеюсь что нет
    }
    m_modelShaderProgram = new GLShader("vertex_shader.vs", "fragment_shader.fs");
    if (m_modelShaderProgram) {
        std::cout << "Shader program initialized." << std::endl;
    }
    else {
        std::cerr << "Failed to initialize shader program!" << std::endl;
    }
}

GLShader* GLModel::getShader() const {
    return m_modelShaderProgram;
}


