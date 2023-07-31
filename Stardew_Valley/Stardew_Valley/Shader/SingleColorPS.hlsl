cbuffer ColorBuffer : register(b0)
{
	float4 color;
	float2 ratio;
	float2 padding;
}

struct Input
{
	float4 pos : SV_POSITION;
};

float4 PS(Input input) : SV_TARGET
{
	if ()
	return color;
}