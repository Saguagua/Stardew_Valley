cbuffer World : register(b0)
{
	matrix world;
}

cbuffer View : register(b1)
{
	matrix view;
}

cbuffer Projection : register(b2)
{
	matrix proj;
}

cbuffer LightBuffer : register(b3)
{
	float4 lightPos[4];
}

struct VertexInput
{
	float4 pos : POSITION;
	float2 uv : UV;
};

struct VertexOutput
{
	float4 pos : SV_POSITION;
	float distance[4] : DISTANCE;
	float2 uv : UV;
};

VertexOutput VS(VertexInput input)
{
	float2 distance1 = lightPos[0] - input.pos;
	float2 distance2 = lightPos[1] - input.pos;
	float2 distance3 = lightPos[2] - input.pos;
	float2 distance4 = lightPos[3] - input.pos;

	VertexOutput result;
	result.pos = mul(input.pos, world);

	float2 worldLightPos1 = mul(lightPos[0], world).xy;
	float2 worldLightPos2 = mul(lightPos[1], world).xy;
	float2 worldLightPos3 = mul(lightPos[2], world).xy;
	float2 worldLightPos4 = mul(lightPos[3], world).xy;
	
	worldLightPos1 -= result.pos.xy;
	worldLightPos2 -= result.pos.xy;
	worldLightPos3 -= result.pos.xy;
	worldLightPos4 -= result.pos.xy;

	result.distance[0] = dot(worldLightPos1, worldLightPos1);
	result.distance[1] = dot(worldLightPos2, worldLightPos2);
	result.distance[2] = dot(worldLightPos3, worldLightPos3);
	result.distance[3] = dot(worldLightPos4, worldLightPos4);

	result.pos = mul(result.pos, view);
	result.pos = mul(result.pos, proj);
	result.uv = input.uv;

	return result;
}