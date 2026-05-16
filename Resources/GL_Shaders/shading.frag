#version 460 core

out vec4 FragColor;

in vec3 v_worldPosition;
in vec3 v_normal;
in vec3 v_tangent;
in vec2 v_uv;

uniform vec3 u_viewPos;
uniform sampler2D texture_diffuse1;

void main()
{
    vec3 baseColor = texture(texture_diffuse1, v_uv).rgb;
    vec3 normal = normalize(v_normal);
    if(!gl_FrontFacing) normal = -normal;

    // Blinn-Phong tweakables
    float ambientStrength = 0.05;
    float specularStrength = 0.2;

    // hardcoded light
    vec3 lightPosition = vec3(0.0, 2.2, 0);
    vec3 lightColor = vec3(0.5686, 0.7, 0.904);
    float lightRadius = 5.0;
    float lightStrength = 1.85f;

    // Attenuation
    vec3 lightDir = lightPosition- v_worldPosition;
    float dist = length(lightDir);
    float attenuation = smoothstep(lightRadius, 0.0, dist);
    // ambient
    vec3 ambient = ambientStrength * baseColor;

    // Diffuse
    float nDotL= clamp(dot(lightDir, normal), 0.0, 1.0);
    vec3 diffuse = baseColor * nDotL;


    // Specular
    vec3 viewDir = normalize(u_viewPos - v_worldPosition);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    vec3 specular = vec3(pow(max(dot(normal, halfwayDir), 0.0), 32.0)) * specularStrength;

    vec3 finalColor = (ambient + diffuse + specular) * lightColor  * lightColor * lightStrength * attenuation;  
    
    FragColor = vec4(finalColor, 1.0);
}