#pragma once

#include "Buffer.h"
#include <glad/glad.h>

class GLIndexBuffer : public Buffer
{
public:
    virtual ~GLIndexBuffer();

    bool isCreated() override;

    void destroy() override;

    void create() override;

    void bind() override;
    void release() override;

    void allocate(void* data, uint32_t size) override;

private:
    unsigned int m_indexBufferId = 0; // ID буфера
    bool m_isCreated = false;        // Флаг создан ли буфер
};
