#pragma once

#include <vector>
#include <vec2.hpp>
#include <mat3x3.hpp>
#include "AffineTransform.h" // ���������� ���� � ��������� ����������������

class Model2D {
public:
    Model2D(const std::vector<glm::vec2>& vertices, const std::vector<int>& indices);

    void draw() const; // ����� ��� ��������� ������
    void translate(const glm::vec2& translation); // ���������� ����������
    void rotate(float angle); // ���������� ��������
    void scale(float factor); // ���������� ���������������
    void applyTransformation(const glm::mat3& transformation); // ���������� ���������� ��������������

private:
    std::vector<glm::vec2> m_vertices; // ������� ������
    std::vector<int> m_indices; // ������� ����������
    glm::mat3 m_transformationMatrix; // ������� ��������������
};
