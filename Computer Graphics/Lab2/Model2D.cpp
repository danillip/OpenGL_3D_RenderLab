#include "Model2D.h"
#include "../pch.h"
#include <iostream>
#include <gtc/matrix_transform.hpp> // ��� ������������� ��������� ��������������
#include <gtc/type_ptr.hpp> // ��� �������������� ������ � �������

// �����������
Model2D::Model2D(const std::vector<glm::vec2>& vertices, const std::vector<int>& indices)
    : m_vertices(vertices), m_indices(indices), m_transformationMatrix(Identity()) {}

// ����� ��� ��������� ������
void Model2D::draw() const {
    // ��������� �������������� � �������� ����� ����������
    std::vector<glm::vec2> transformedVertices;

    for (const auto& vertex : m_vertices) {
        glm::vec3 homogenousVertex(vertex, 1.0f); // ������� � ��������� ������� ���������
        glm::vec3 transformedVertex = m_transformationMatrix * homogenousVertex; // ��������� ������� ��������������
        transformedVertices.emplace_back(transformedVertex.x, transformedVertex.y); // ��������� ��������������� �������
    }

    // ������ ������
    glBegin(GL_TRIANGLES); // ��� GL_LINES, � ����������� �� ����, ��� �� ������ ����������
    for (const auto& index : m_indices) {
        const glm::vec2& vertex = transformedVertices[index];
        glVertex2f(vertex.x, vertex.y);
    }
    glEnd();
}

// ����� ��� ���������� ����������
void Model2D::translate(const glm::vec2& translation) {
    glm::mat3 translationMatrix = Translation(translation.x, translation.y);
    applyTransformation(translationMatrix);
}

// ����� ��� ���������� ��������
void Model2D::rotate(float angle) {
    float radians = glm::radians(angle); // ����������� ���� � �������
    glm::mat3 rotationMatrix = glm::mat3(
        cos(radians), -sin(radians), 0.0f,
        sin(radians), cos(radians), 0.0f,
        0.0f, 0.0f, 1.0f
    );
    applyTransformation(rotationMatrix);
}

// ����� ��� ���������� ���������������
void Model2D::scale(float factor) {
    glm::mat3 scalingMatrix = glm::mat3(
        factor, 0.0f, 0.0f,
        0.0f, factor, 0.0f,
        0.0f, 0.0f, 1.0f
    );
    applyTransformation(scalingMatrix);
}

// ����� ��� ���������� ���������� ��������������
void Model2D::applyTransformation(const glm::mat3& transformation) {
    m_transformationMatrix = transformation * m_transformationMatrix; // ��������� ������� ��������������
}
