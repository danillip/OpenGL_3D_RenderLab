#include "GLIndexBuffer.h"

// Деструктор: Уничтожает буфер если он создан
GLIndexBuffer::~GLIndexBuffer() {
    if (m_isCreated) {
        destroy();
    }
}

// Проверка, создан ли буфер
bool GLIndexBuffer::isCreated() {
    return m_isCreated;
}

// Уничтожение буфера
void GLIndexBuffer::destroy() {
    if (m_isCreated) {
        glDeleteBuffers(1, &m_indexBufferId);
        m_isCreated = false;
    }
}

// Создание буфера
void GLIndexBuffer::create() {
    if (!m_isCreated) {
        glGenBuffers(1, &m_indexBufferId);
        m_isCreated = true;
    }
}

// Привязка буфера
void GLIndexBuffer::bind() {
    if (m_isCreated) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
    }
}

// Освобождение буфера
void GLIndexBuffer::release() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Выделение данных для буфера
void GLIndexBuffer::allocate(void* data, uint32_t size) {
    if (m_isCreated) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
}
