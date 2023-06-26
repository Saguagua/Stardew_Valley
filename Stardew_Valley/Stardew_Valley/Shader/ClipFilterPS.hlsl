Texture2D resource : register(t0);
SamplerState samp : register(s0);

cbuffer ReverseBuffer : register(b0)
{
	int isReverse;
	int paddint[3];
}

cbuffer FrameBuffer : register(b1)
{
	float2 maxFrame;
	float2 curFrame;
}

struct Input
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

float4 PS(Input input) : SV_TARGET
{
	float2 resultUV;

	if (isReverse == 1)
		input.uv.x = 1 - input.uv.x;

	resultUV.x = input.uv.x / maxFrame.x + curFrame.x / maxFrame.x;
	resultUV.y = input.uv.y / maxFrame.y + curFrame.y / maxFrame.y;

	float4 color = resource.Sample(samp, resultUV);

	return color;
}