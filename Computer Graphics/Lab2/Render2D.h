#pragma once

#include <vector>
#include "Model2D.h"

class Render2D {
public:
    Render2D();
    ~Render2D();

    void addObject(Model2D* model);
    void draw() const;

    int getModelCount() const; // Метод для получения количества моделей
    void drawCurrentModel(int index) const; // Метод для отрисовки текущей модели

private:
    std::vector<Model2D*> m_models; // Хранит указатели на объекты моделей
};
