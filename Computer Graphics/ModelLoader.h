// ModelLoader.h
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm.hpp>
#include "VertexData.h"  // Подключаем заголовочный файл с определением VertexData
#include "GLModel.h"

struct FaceData {
    int vertexIndex;
    int texCoordIndex;
    int normalIndex;
};

std::vector<VertexData> loadModelFromFile(const std::string& filename,
    std::vector<int>& indices,
    std::vector<glm::vec2>& texCoords,
    std::vector<glm::vec3>& normals) {
    std::vector<glm::vec3> tempVertices;
    std::vector<glm::vec2> tempTexCoords;
    std::vector<glm::vec3> tempNormals;

    std::vector<VertexData> vertices;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return vertices;
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string temp;
        ss >> temp;

        if (temp == "v") {
            glm::vec3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            tempVertices.push_back(vertex);
        }
        else if (temp == "vt") {
            glm::vec2 texCoord;
            ss >> texCoord.x >> texCoord.y;
            tempTexCoords.push_back(texCoord);
        }
        else if (temp == "vn") {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            tempNormals.push_back(normal);
        }
        else if (temp == "f") {
            FaceData faceData[3];
            char slash;
            for (int i = 0; i < 3; ++i) {
                ss >> faceData[i].vertexIndex >> slash >> faceData[i].texCoordIndex >> slash >> faceData[i].normalIndex;

                // Корректировка индексов для массива
                int vertexIndex = faceData[i].vertexIndex - 1;
                int texCoordIndex = faceData[i].texCoordIndex - 1;
                int normalIndex = faceData[i].normalIndex - 1;

                // Создаем вершину с уникальной нормалью для каждой грани
                VertexData vertex;
                vertex.position = tempVertices[vertexIndex];
                vertex.texCoord = (texCoordIndex >= 0 && texCoordIndex < tempTexCoords.size())
                    ? tempTexCoords[texCoordIndex] : glm::vec2(0.0f, 0.0f);
                vertex.normal = (normalIndex >= 0 && normalIndex < tempNormals.size())
                    ? tempNormals[normalIndex] : glm::vec3(0.0f, 0.0f, 1.0f);

                // Добавляем вершину и индекс
                vertices.push_back(vertex);
                indices.push_back(vertices.size() - 1);

                std::cout << "Vertex: (" << vertex.position.x << ", " << vertex.position.y << ", " << vertex.position.z << ") ";
                std::cout << "Normal: (" << vertex.normal.x << ", " << vertex.normal.y << ", " << vertex.normal.z << ")" << std::endl;
            }
        }
    }

    file.close();

    return vertices;
}
