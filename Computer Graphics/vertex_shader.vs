#version 330 core

layout (location = 0) in vec3 aPos;  // Входная позиция вершины
layout (location = 1) in vec2 aTexCoord;  // Входные координаты текстуры
layout (location = 2) in vec3 aNormal;  // Входные нормали

out vec2 TexCoord;  // Передаем координаты текстуры в фрагментный шейдер
out vec3 Normal;    // Передаем нормали
out vec3 FragPos;   // Позиция фрагмента в мировых координатах

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // Позиция вершины в мировом пространстве
	// Позиция каждой вершины также преобразуется в мировое пространство чтобы мы могли точно определить где она находится относительно источников света
    FragPos = vec3(model * vec4(aPos, 1.0f));

    // Преобразование нормали из локального в мировое пространство
	// Нормали моделей в локальном пространстве преобразуются в мировое пространство с помощью матрицы модели. 
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // Преобразуем позицию вершины для шейдера
    gl_Position = projection * view * model * vec4(aPos, 1.0f);

    // Передаем координаты текстуры
    TexCoord = aTexCoord;
}
