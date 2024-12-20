#include "Model2D.h"
#include "../pch.h"
#include <iostream>
#include <gtc/matrix_transform.hpp> // Для использования матричных преобразований
#include <gtc/type_ptr.hpp> // Для преобразования матриц в массивы

// Конструктор
Model2D::Model2D(const std::vector<glm::vec2>& vertices, const std::vector<int>& indices)
    : m_vertices(vertices), m_indices(indices), m_transformationMatrix(Identity()) {}

// Метод для отрисовки модели
void Model2D::draw() const {
    // Применяем преобразования к вершинам перед отрисовкой
    std::vector<glm::vec2> transformedVertices;

    for (const auto& vertex : m_vertices) {
        glm::vec3 homogenousVertex(vertex, 1.0f); // Переход к гомогеной системе координат
        glm::vec3 transformedVertex = m_transformationMatrix * homogenousVertex; // Применяем матрицу преобразования
        transformedVertices.emplace_back(transformedVertex.x, transformedVertex.y); // Сохраняем преобразованную вершину
    }

    // Рисуем модель
    glBegin(GL_TRIANGLES); // Или GL_LINES, в зависимости от того, как ты хочешь отрисовать
    for (const auto& index : m_indices) {
        const glm::vec2& vertex = transformedVertices[index];
        glVertex2f(vertex.x, vertex.y);
    }
    glEnd();
}

// Метод для применения трансляции
void Model2D::translate(const glm::vec2& translation) {
    glm::mat3 translationMatrix = Translation(translation.x, translation.y);
    applyTransformation(translationMatrix);
}

// Метод для применения поворота
void Model2D::rotate(float angle) {
    float radians = glm::radians(angle); // Преобразуем угол в радианы
    glm::mat3 rotationMatrix = glm::mat3(
        cos(radians), -sin(radians), 0.0f,
        sin(radians), cos(radians), 0.0f,
        0.0f, 0.0f, 1.0f
    );
    applyTransformation(rotationMatrix);
}

// Метод для применения масштабирования
void Model2D::scale(float factor) {
    glm::mat3 scalingMatrix = glm::mat3(
        factor, 0.0f, 0.0f,
        0.0f, factor, 0.0f,
        0.0f, 0.0f, 1.0f
    );
    applyTransformation(scalingMatrix);
}

// Метод для применения составного преобразования
void Model2D::applyTransformation(const glm::mat3& transformation) {
    m_transformationMatrix = transformation * m_transformationMatrix; // Обновляем матрицу преобразования
}
