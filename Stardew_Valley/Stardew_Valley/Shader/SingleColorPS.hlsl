cbuffer ColorBuffer : register(b0)
{
	float4 color;
	float2 ratio;
	float2 padding;
}

struct Input
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

float4 PS(Input input) : SV_TARGET
{
	if (input.uv.x > ratio.x || input.uv.y > ratio.y)
		return float4(0,0,0,0);
	return color;
}