Texture2D resource : register(t0);
SamplerState samp : register(s0);

cbuffer FrameBuffer : register(b0)
{
	float2 maxFrame;
	float2 curFrame;
}

cbuffer LightBuffer:register(b1)
{
	float4 lightColor[30];
}

struct Input
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	float distance[29] : DISTANCE;
};

float4 PS(Input input) : SV_TARGET
{
	float2 resultUV;

	resultUV.x = input.uv.x / maxFrame.x + curFrame.x / maxFrame.x;
	resultUV.y = input.uv.y / maxFrame.y + curFrame.y / maxFrame.y;

	float4 mixedColor = { 0,0,0,0 };
	float4 colorResult;

	for (int i = 0; i < 29; i++)
	{
		colorResult = saturate(lightColor[i+1] / input.distance[i]);
		mixedColor += colorResult;
	}

	float4 color = resource.Sample(samp, resultUV);
	color =  saturate(color * (mixedColor + lightColor[0]));
	return color;
}