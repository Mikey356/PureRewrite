#version 460 core
out vec4 FragColor;

layout (binding = 0) uniform sampler2D u_textures;

// tone mapping
vec3 FilmicToneMap(vec3 x) {
  vec3 X = max(vec3(0.0), x - 0.004);
  vec3 result = (X * (6.2 * X + 0.5)) / (X * (6.2 * X + 1.7) + 0.06);
  return pow(result, vec3(2.2));
}

void main()
{
	ivec2 px = ivec2(gl_FragCoord.xy);
	vec3 srcColor = texelFetch(u_textures, px, 0).rgb;

	vec3 finalColor = FilmicToneMap(srcColor);
	// finalColor = srcColor;

	FragColor = vec4(finalColor, 1.0); 
	
}