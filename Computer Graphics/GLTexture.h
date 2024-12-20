#pragma once
#include <string>
#include <glad/glad.h>
#include "stb_image.h" // Подключение для работы с загрузкой текстур

class GLTexture {
public:
    // Конструктор по умолчанию
    GLTexture();

    // Конструктор с загрузкой текстуры
    GLTexture(const std::string& path);

    // Деструктор
    ~GLTexture();

    // Метод для загрузки текстуры из файла
    bool loadFromFile(const std::string& path);

    // Привязка текстуры
    void bind(unsigned int unit = 0) const;

    // Отвязывание текстуры
    void unbind() const;

private:
    unsigned int textureID;
};
