#include "Render2D.h"
#include <iostream>

// Конструктор
Render2D::Render2D() {}

// Деструктор
Render2D::~Render2D() {
    // Освобождение памяти, если необходимо
    for (auto model : m_models) {
        delete model;
    }
}

// Метод для добавления модели в рендерер
void Render2D::addObject(Model2D* model) {
    m_models.push_back(model);
}

// Метод для отрисовки всех моделей
void Render2D::draw() const {
    for (const auto& model : m_models) {
        model->draw(); // Отрисовываем каждую модель
    }
}
