#include "Render3D.h"
#include <iostream>

// ������
Render3D::Render3D() {}

// �����
Render3D::~Render3D() {
    // ������� ��� ������ �� ������
    for (auto model : m_models) {
        delete model;
    }
}

// 3� ������ � ������
void Render3D::addObject(GLModel* model) {
    m_models.push_back(model);
}

// ������ 3� ������
void Render3D::draw() const {
    for (const auto& model : m_models) {
        model->draw(); // ��� ���������
    }
}

// ���������� ������� ������
int Render3D::getModelCount() const {
    return static_cast<int>(m_models.size());
}

// ������ �� ��������
void Render3D::drawCurrentModel(int index) const {
    if (index >= 0 && index < static_cast<int>(m_models.size())) {
        m_models[index]->draw();
    }
    else {
        std::cerr << "������: ������ " << index << " ��� ���������." << std::endl;
    }
}
