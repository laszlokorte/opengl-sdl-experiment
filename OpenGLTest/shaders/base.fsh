#define STRINGIFY(x) #x

"#version 330\n"

STRINGIFY(
          
struct Light {
    vec3 Color;
    float AnbientIntensity;
    vec3 Direction;
    float DiffuseIntensity;
};

uniform Light uLight;
uniform sampler2D uTexture;

in vec4 fPos;
in vec4 fNormal;
in vec4 fColor;
in vec4 fTexCoord;

out vec4 color;

void main() {
    color = fColor; //fColor
}
          
)