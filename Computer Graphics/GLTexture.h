#pragma once
#include <string>
#include <glad/glad.h>
#include "stb_image.h" // ����������� ��� ������ � ��������� �������

class GLTexture {
public:
    // ����������� �� ���������
    GLTexture();

    // ����������� � ��������� ��������
    GLTexture(const std::string& path);

    // ����������
    ~GLTexture();

    // ����� ��� �������� �������� �� �����
    bool loadFromFile(const std::string& path);

    // �������� ��������
    void bind(unsigned int unit = 0) const;

    // ����������� ��������
    void unbind() const;

private:
    unsigned int textureID;
};
