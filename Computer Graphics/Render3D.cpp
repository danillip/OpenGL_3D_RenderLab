#include "Render3D.h"
#include <iostream>

// констр
Render3D::Render3D() {}

// дестр
Render3D::~Render3D() {
    // удаляем все модели из памяти
    for (auto model : m_models) {
        delete model;
    }
}

// 3Д модель в рендер
void Render3D::addObject(GLModel* model) {
    m_models.push_back(model);
}

// Рисуем 3Д моедль
void Render3D::draw() const {
    for (const auto& model : m_models) {
        model->draw(); // мет отрисовки
    }
}

// Количество моделей читаем
int Render3D::getModelCount() const {
    return static_cast<int>(m_models.size());
}

// Рисуем по индеексу
void Render3D::drawCurrentModel(int index) const {
    if (index >= 0 && index < static_cast<int>(m_models.size())) {
        m_models[index]->draw();
    }
    else {
        std::cerr << "Ошибка: индекс " << index << " вне диапазона." << std::endl;
    }
}
