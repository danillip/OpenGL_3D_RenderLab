#pragma once

#include "Buffer.h"
#include <glad/glad.h>

class GLVertexBuffer : public Buffer {
public:
    virtual ~GLVertexBuffer();

    bool isCreated() override;

    void destroy() override;

    void create() override;

    void bind() override;
    void release() override;

    void allocate(void* data, uint32_t size) override;

private:
    unsigned int m_VAO = 0; // ID вершинного массива
    unsigned int m_VBO = 0; // ID вершинного буфера

    bool m_isCreated = false;           // флаг создания буфера
    bool m_isAlreadyDestroyed = false; // флаг удаления буфера
};
