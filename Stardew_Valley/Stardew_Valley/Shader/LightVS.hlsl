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
	float4 lightPos[29];
}

struct VertexInput
{
	float4 pos : POSITION;
	float2 uv : UV;
};

struct VertexOutput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	float distance[29] : DISTANCE;
};

VertexOutput VS(VertexInput input)
{
	VertexOutput result;
	result.pos = mul(input.pos, world);

	for (int i = 0; i < 29; i++)
	{
		if (lightPos[i].x + lightPos[i].y + lightPos[i].z < 0)
			result.distance[i] = 0;
		else
		{
			float2 worldLightPos = lightPos[i].xy;
			worldLightPos -= result.pos.xy;
			result.distance[i] = dot(worldLightPos, worldLightPos);
		}
	}

	result.pos = mul(result.pos, view);
	result.pos = mul(result.pos, proj);
	result.uv = input.uv;

	return result;
}