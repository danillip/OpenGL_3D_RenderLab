#version 330 core

in vec2 TexCoord;  // Координаты текстуры
in vec3 Normal;    // Нормаль в мировом пространстве
in vec3 FragPos;   // Позиция фрагмента в мировом пространстве

out vec4 FragColor;

uniform sampler2D texture1;  // Текстура
uniform vec3 lightColor;  // Цвет света
uniform vec3 lightDirection;    // Направление света в мировом пространстве
uniform vec3 viewPos;     // Позиция камеры
uniform mat4 model;       // Матрица модели
uniform mat4 view;        // Матрица камеры (вида)
uniform mat4 projection;  // Матрица проекции

void main() {
    // Получаем цвет из текстуры
    vec4 textureColor = texture(texture1, TexCoord);

    // Преобразуем нормаль и позицию фрагмента в мировой базис
    vec3 fragPos = vec3(model * vec4(FragPos, 1.0));  // Преобразование позиции фрагмента в мировой базис
    vec3 normal = normalize(mat3(transpose(inverse(model))) * Normal);  // Преобразование нормали

    // Направление света в мировом пространстве
    vec3 lightDir = normalize(lightDirection);  // Направление света фиксировано в мировом пространстве

    // Направление к камере
    vec3 viewDir = normalize(viewPos - fragPos);

    // Рассеянное освещение (ambient)
    vec3 ambient = 0.1 * lightColor;

    // Дифузное освещение (diffuse) — это для каждой грани
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Зеркальное освещение (specular)
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = 0.5 * spec * lightColor;

    // Итоговый цвет с освещением
    vec3 result = (ambient + diffuse + specular) * vec3(textureColor);

    // Дебаг: выделяем фрагменты, куда свет направляется
    //float lightDot = dot(normal, lightDir);
    //if (lightDot > 0.99) {
        // Когда нормаль близка к направлению света, выделяем этот фрагмент красным для дебага
    //    result = vec3(1.0, 0.0, 0.0);  // Красный цвет для дебага
    //} else if (lightDot > 0.0) {
        // Когда свет падает на грань, но не идеально (не параллельно нормали), сделаем ее зеленой
    //    result = vec3(0.0, 1.0, 0.0);  // Зеленый для частичного попадания света
    //}

    // Визуализация самого света, если фрагмент направлен в сторону света
    // Например, если фрагмент направлен в сторону света, делаем его синим
    //float directionDot = dot(normalize(fragPos), lightDir);  // Вектор из фрагмента в сторону света
    //if (directionDot > 0.5) {
    //    result = vec3(0.0, 0.0, 1.0);  // Если фрагмент находится на пути света, сделаем его синим
    //}

    FragColor = vec4(result, 1.0);  // Итоговый цвет фрагмента
}
