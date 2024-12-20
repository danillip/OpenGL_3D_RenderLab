#pragma once

#include <string>
#include <vector>
#include <vec2.hpp>

class Loader {
public:
    Loader(const std::string& path);
    ~Loader();

    std::vector<glm::vec2> vertices() const;
    std::vector<int> indices() const;

private:
    bool isLoad();

    std::vector<glm::vec2> m_vertices;
    std::vector<int> m_indices;

    std::string m_path;
};
