#define STRINGIFY(x) #x

"#version 330\n"

STRINGIFY(

uniform mat4 uModelViewMatrix;
uniform mat4 uProjectionMatrix;

in vec3 vPosition;
in vec3 vNormal;
in vec4 vColor;
in vec4 vTexCoord;

out vec3 fPosition;
out vec3 fNormal;
out vec4 fColor;
out vec4 fTexCoord;

void main() {

    vec4 camPos = uModelViewMatrix * vec4(vPosition, 1.0);
    vec4 camNormal = uModelViewMatrix * vec4(vNormal, 0.0);

    fPosition = camPos.xyz;
    fNormal = camNormal.xyz;
    fColor = vColor;
    fTexCoord = vTexCoord;

    gl_Position = uProjectionMatrix * camPos;
}
)
