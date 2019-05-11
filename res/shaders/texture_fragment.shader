#version 330 core
layout(location = 0) out vec4 color;

uniform sampler2D u_Texture;
uniform float u_ColorScale = 1.0f;

in vec2 v_TexCoord;

void main()
{
	vec4 texCoord = texture(u_Texture, v_TexCoord);
	texCoord.xyz *= u_ColorScale;
	color = texCoord;
};
