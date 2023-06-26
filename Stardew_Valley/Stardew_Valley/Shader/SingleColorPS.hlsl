cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

struct Input
{
	float4 pos : SV_POSITION;
};

float4 PS(Input input) : SV_TARGET
{
	return color;
}