#version 460 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;
layout (location = 3) in vec3 a_tangent;

out vec3 v_normal;
out vec3 v_tangent;
out vec3 v_worldPosition;
out vec2 v_uv;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;
uniform mat4 u_inverseModel;
    
void main()
{
    v_tangent = a_tangent;
    v_uv = a_uv;    

    mat4 normalMatrix = transpose(u_inverseModel);
    v_normal = normalize((normalMatrix * vec4(a_normal, 0.0))).xyz;   
    
    vec4 worldPosition = u_model * vec4(a_position, 1.0);
    v_worldPosition = worldPosition.xyz;

    gl_Position = u_projection * u_view * worldPosition;
   
}