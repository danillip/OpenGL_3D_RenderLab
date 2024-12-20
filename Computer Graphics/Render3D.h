#pragma once

#include <vector>
#include "GLModel.h"

class Render3D {
public:
    Render3D();
    ~Render3D();

    void addObject(GLModel* model); // аддер 3D модели
    void draw() const;              // рисуем все модели

    int getModelCount() const;                // получение количества моделей
    void drawCurrentModel(int index) const;   // отрисовка модели по индексу

private:
    std::vector<GLModel*> m_models; // Вектор указателей на модели
};
