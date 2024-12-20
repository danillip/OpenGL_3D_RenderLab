#include "Render2D.h"
#include <iostream>

// �����������
Render2D::Render2D() {}

// ����������
Render2D::~Render2D() {
    // ������������ ������, ���� ����������
    for (auto model : m_models) {
        delete model;
    }
}

// ����� ��� ���������� ������ � ��������
void Render2D::addObject(Model2D* model) {
    m_models.push_back(model);
}

// ����� ��� ��������� ���� �������
void Render2D::draw() const {
    for (const auto& model : m_models) {
        model->draw(); // ������������ ������ ������
    }
}
