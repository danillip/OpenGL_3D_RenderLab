#include "GLVertexBuffer.h"

GLVertexBuffer::~GLVertexBuffer() {
    destroy();
}

bool GLVertexBuffer::isCreated() {
    return m_isCreated;
}

void GLVertexBuffer::destroy() {
    if (!m_isAlreadyDestroyed) {
        if (m_VBO) {
            glDeleteBuffers(1, &m_VBO);
            m_VBO = 0;
        }
        if (m_VAO) {
            glDeleteVertexArrays(1, &m_VAO);
            m_VAO = 0;
        }
        m_isAlreadyDestroyed = true;
        m_isCreated = false;
    }
}

void GLVertexBuffer::create() {
    if (!m_isCreated) {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        m_isCreated = true;
        m_isAlreadyDestroyed = false;
    }
}

void GLVertexBuffer::bind() {
    if (m_isCreated) {
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    }
}

void GLVertexBuffer::release() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLVertexBuffer::allocate(void* data, uint32_t size) {
    if (m_isCreated) {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
}
