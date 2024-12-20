// VertexData.h
#pragma once

#include <glm.hpp>

// Структура данных о вершине
struct VertexData {
    glm::vec3 position;  // Координаты вершины
    glm::vec2 texCoord;  // Текстурные координаты
    glm::vec3 normal;    // Нормаль
};
