#version 400

#define LIGHT_DISTANCE 10

uniform vec4 _Time;
uniform sampler2D _Texture;
uniform vec3 _LightPos;

out vec4 OutColor;

struct v2f
{
	vec3 WorldPosition;
	vec4 Color;
	vec2 TexCoord0;
	vec3 Normal;
};

in v2f VertexInfo;


void main()
{
	vec4 Color = texture2D(_Texture, VertexInfo.TexCoord0);
	float direction = max(0, dot(VertexInfo.Normal, _LightPos - VertexInfo.WorldPosition));
	float distance = (LIGHT_DISTANCE - distance(_LightPos, VertexInfo.WorldPosition)) / LIGHT_DISTANCE;
	OutColor = vec4(0.2, 0, 0.49, 1) * Color + Color * max(0, distance * direction);
}