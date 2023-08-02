Texture2D resource : register(t0);
SamplerState samp : register(s0);

cbuffer FrameBuffer : register(b0)
{
	float2 maxFrame;
	float2 curFrame;
}

cbuffer LightBuffer:register(b1)
{
	float4 lightColor[4];
}

struct Input
{
	float4 pos : SV_POSITION;
	float distance[4] : DISTANCE;
	float2 uv : UV;
};

float4 PS(Input input) : SV_TARGET
{
	float2 resultUV;

	resultUV.x = input.uv.x / maxFrame.x + curFrame.x / maxFrame.x;
	resultUV.y = input.uv.y / maxFrame.y + curFrame.y / maxFrame.y;

	float4 color1 = saturate(lightColor[0] / input.distance[0]);
	float4 color2 = saturate(lightColor[1] / input.distance[1]);
	float4 color3 = saturate(lightColor[2] / input.distance[2]);
	float4 color4 = saturate(lightColor[3] / input.distance[3]);

	float4 color = (resource.Sample(samp, resultUV) + saturate(color1 + color2 + color3 + color4));

	return color;
}