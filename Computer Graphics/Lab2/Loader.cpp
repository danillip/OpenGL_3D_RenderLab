#include "Loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Конструктор, который вызывает метод загрузки
Loader::Loader(const std::string& path) : m_path(path) {
    if (!isLoad()) {
        std::cerr << "Ошибка загрузки модели из файла: " << m_path << std::endl;
    }
}

// Деструктор
Loader::~Loader() {}

// Метод для получения вершин
std::vector<glm::vec2> Loader::vertices() const {
    return m_vertices;
}

// Метод для получения индексов
std::vector<int> Loader::indices() const {
    return m_indices;
}

// Метод для загрузки данных из файла
bool Loader::isLoad() {
    setlocale(LC_ALL, "RU");
    std::ifstream file(m_path);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << m_path << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        char type;
        iss >> type;

        if (type == 'v') { // Обработка вершин
            double x, y;
            if (iss >> x >> y) {
                m_vertices.emplace_back(static_cast<float>(x), static_cast<float>(y));
            }
        }
        else if (type == 'f') { // Обработка индексов
            int index;
            while (iss >> index) {
                m_indices.push_back(index);
            }
        }
    }

    file.close();
    return true;
}
