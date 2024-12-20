#pragma once

#include <vector>
#include <vec2.hpp>
#include <mat3x3.hpp>
#include "AffineTransform.h" // Подключаем файл с аффинными преобразованиями

class Model2D {
public:
    Model2D(const std::vector<glm::vec2>& vertices, const std::vector<int>& indices);

    void draw() const; // Метод для отрисовки модели
    void translate(const glm::vec2& translation); // Применение трансляции
    void rotate(float angle); // Применение поворота
    void scale(float factor); // Применение масштабирования
    void applyTransformation(const glm::mat3& transformation); // Применение составного преобразования

private:
    std::vector<glm::vec2> m_vertices; // Вершины модели
    std::vector<int> m_indices; // Индексы соединений
    glm::mat3 m_transformationMatrix; // Матрица преобразования
};
