#define STRINGIFY(x) #x

"#version 330\n"

STRINGIFY(

struct Light {
    vec3 color;
    vec3 position;
    float ambientIntensity;
    float diffuseIntensity;
};

struct Material {
    float shininess;
    float specularIntensity;
};

uniform vec3 cameraPosition;
uniform Material uMaterial;
uniform Light uLight;
uniform sampler2D uTexture;

in vec3 fPosition;
in vec3 fNormal;
in vec4 fColor;
in vec2 fTexCoord;

out vec4 oColor;

void main() {
    vec3 lightDirection = normalize(uLight.position - fPosition);
    vec3 Normal = normalize(fNormal);
    float lambertian = max(dot(lightDirection,Normal), 0.0);

    // Ambient
    vec3 AmbientColor = uLight.color * uLight.ambientIntensity;
    
    // Diffuse
    vec3 DiffuseColor = lambertian * uLight.color * uLight.diffuseIntensity;
    
    // Specular
    vec3 Eye = normalize(cameraPosition-fPosition);
    vec3 Reflection = reflect(-lightDirection, Normal);
    float SpecularFactor = 0.0;
    
    if(lambertian > 0.0) {
        float specAngle = max(dot(Reflection, Eye), 0.0);
        SpecularFactor = pow(specAngle, uMaterial.shininess);
    }
    
    vec3 SpecularColor = uLight.color * uMaterial.specularIntensity * SpecularFactor;
    
    oColor = texture(uTexture, fTexCoord) * vec4(AmbientColor+DiffuseColor+SpecularColor,1);
}
          
)