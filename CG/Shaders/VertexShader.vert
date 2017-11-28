#version 400

uniform mat4 _ModelViewProjectionMatrix;
uniform mat4 _ObjectMatrix;
uniform vec4 _Time;

in vec3 InPosition;
in vec3 InNormal;
in vec2 InTexCoord0;
in vec4 InColor;

struct v2f
{
	vec3 WorldPosition;
	vec4 Color;
	vec2 TexCoord0;
	vec3 Normal;
};

out v2f VertexInfo;

void main()
{
	VertexInfo.Color = InColor;
	VertexInfo.TexCoord0 = InTexCoord0;
	VertexInfo.Normal = InNormal;
	VertexInfo.WorldPosition = (vec4(InPosition, 1) * _ObjectMatrix).xyz;

	gl_Position = vec4(InPosition, 1) * _ModelViewProjectionMatrix;
}
