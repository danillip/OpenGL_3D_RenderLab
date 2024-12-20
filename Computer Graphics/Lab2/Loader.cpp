#include "Loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

// �����������, ������� �������� ����� ��������
Loader::Loader(const std::string& path) : m_path(path) {
    if (!isLoad()) {
        std::cerr << "������ �������� ������ �� �����: " << m_path << std::endl;
    }
}

// ����������
Loader::~Loader() {}

// ����� ��� ��������� ������
std::vector<glm::vec2> Loader::vertices() const {
    return m_vertices;
}

// ����� ��� ��������� ��������
std::vector<int> Loader::indices() const {
    return m_indices;
}

// ����� ��� �������� ������ �� �����
bool Loader::isLoad() {
    setlocale(LC_ALL, "RU");
    std::ifstream file(m_path);
    if (!file.is_open()) {
        std::cerr << "�� ������� ������� ����: " << m_path << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        char type;
        iss >> type;

        if (type == 'v') { // ��������� ������
            double x, y;
            if (iss >> x >> y) {
                m_vertices.emplace_back(static_cast<float>(x), static_cast<float>(y));
            }
        }
        else if (type == 'f') { // ��������� ��������
            int index;
            while (iss >> index) {
                m_indices.push_back(index);
            }
        }
    }

    file.close();
    return true;
}
