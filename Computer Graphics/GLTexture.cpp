#include "GLTexture.h"
#include <iostream>

// Конструктор по умолчанию
GLTexture::GLTexture() : textureID(0) {
    glGenTextures(1, &textureID);
}

// Конструктор с загрузкой текстуры
GLTexture::GLTexture(const std::string& path) : textureID(0) {
    glGenTextures(1, &textureID);
    if (!loadFromFile(path)) {
        std::cerr << "Failed to load texture: " << path << std::endl;
    }
}

// Деструктор
GLTexture::~GLTexture() {
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
    }
}

// Метод для загрузки текстуры из файла
bool GLTexture::loadFromFile(const std::string& path) {
    int width, height, nrChannels;

    // Загрузка изображения
    stbi_set_flip_vertically_on_load(true); // Переворот текстуры по вертикали
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load image: " << path << std::endl;
        return false;
    }

    GLenum format = (nrChannels == 3) ? GL_RGB : GL_RGBA;

    std::cout << "Texture width: " << width << " height: " << height << std::endl;

    // Привязка текстуры
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Установки текстурных параметров
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Очистка
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

// Привязка текстуры
void GLTexture::bind(unsigned int unit) const {
    if (unit >= 16) {
        std::cerr << "Texture unit exceeds limit (max 16 units)." << std::endl;
        return;
    }
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

// Отвязывание текстуры
void GLTexture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
