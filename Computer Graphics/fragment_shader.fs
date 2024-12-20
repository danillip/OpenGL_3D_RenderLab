#version 330 core

in vec2 TexCoord;  // ���������� ��������
in vec3 Normal;    // ������� � ������� ������������
in vec3 FragPos;   // ������� ��������� � ������� ������������

out vec4 FragColor;

uniform sampler2D texture1;  // ��������
uniform vec3 lightColor;  // ���� �����
uniform vec3 lightDirection;    // ����������� ����� � ������� ������������
uniform vec3 viewPos;     // ������� ������
uniform mat4 model;       // ������� ������
uniform mat4 view;        // ������� ������ (����)
uniform mat4 projection;  // ������� ��������

void main() {
    // �������� ���� �� ��������
    vec4 textureColor = texture(texture1, TexCoord);

    // ����������� ������� � ������� ��������� � ������� �����
    vec3 fragPos = vec3(model * vec4(FragPos, 1.0));  // �������������� ������� ��������� � ������� �����
    vec3 normal = normalize(mat3(transpose(inverse(model))) * Normal);  // �������������� �������

    // ����������� ����� � ������� ������������
    vec3 lightDir = normalize(lightDirection);  // ����������� ����� ����������� � ������� ������������

    // ����������� � ������
    vec3 viewDir = normalize(viewPos - fragPos);

    // ���������� ��������� (ambient)
    vec3 ambient = 0.1 * lightColor;

    // �������� ��������� (diffuse) � ��� ��� ������ �����
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // ���������� ��������� (specular)
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = 0.5 * spec * lightColor;

    // �������� ���� � ����������
    vec3 result = (ambient + diffuse + specular) * vec3(textureColor);

    // �����: �������� ���������, ���� ���� ������������
    //float lightDot = dot(normal, lightDir);
    //if (lightDot > 0.99) {
        // ����� ������� ������ � ����������� �����, �������� ���� �������� ������� ��� ������
    //    result = vec3(1.0, 0.0, 0.0);  // ������� ���� ��� ������
    //} else if (lightDot > 0.0) {
        // ����� ���� ������ �� �����, �� �� �������� (�� ����������� �������), ������� �� �������
    //    result = vec3(0.0, 1.0, 0.0);  // ������� ��� ���������� ��������� �����
    //}

    // ������������ ������ �����, ���� �������� ��������� � ������� �����
    // ��������, ���� �������� ��������� � ������� �����, ������ ��� �����
    //float directionDot = dot(normalize(fragPos), lightDir);  // ������ �� ��������� � ������� �����
    //if (directionDot > 0.5) {
    //    result = vec3(0.0, 0.0, 1.0);  // ���� �������� ��������� �� ���� �����, ������� ��� �����
    //}

    FragColor = vec4(result, 1.0);  // �������� ���� ���������
}
