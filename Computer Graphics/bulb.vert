#version 420 core

layout(location = 0) in vec3 pos;

layout(std140, binding = 0) uniform Camera {
    mat4 projection;
    mat4 view;
    vec3 position;
} camera;

uniform mat4 model;

void main() {
    gl_Position = camera.projection * camera.view * model * vec4(pos, 1.0);
}
