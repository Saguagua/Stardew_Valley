
cbuffer World : register(b0)
{
	matrix world;
};

cbuffer View : register(b1)
{
	matrix view;
};

cbuffer Proj : register(b2)
{
	matrix proj;
};

struct Input
{
	float4 pos : POSITION;
};

struct Output
{
	float4 pos : SV_POSITION;
};

Output VS(Input input)
{
	Output result;
	result.pos = mul(input.pos, world);
	result.pos = mul(result.pos, view);
	result.pos = mul(result.pos, proj);

	return result;
}