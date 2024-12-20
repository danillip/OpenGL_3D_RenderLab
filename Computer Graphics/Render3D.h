#pragma once

#include <vector>
#include "GLModel.h"

class Render3D {
public:
    Render3D();
    ~Render3D();

    void addObject(GLModel* model); // ����� 3D ������
    void draw() const;              // ������ ��� ������

    int getModelCount() const;                // ��������� ���������� �������
    void drawCurrentModel(int index) const;   // ��������� ������ �� �������

private:
    std::vector<GLModel*> m_models; // ������ ���������� �� ������
};
