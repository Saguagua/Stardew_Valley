Texture2D resource : register(t0);
SamplerState samp : register(s0);

cbuffer XMLBuffer : register(b0)
{
	float2 startPos;
	float2 size;
	float2 imageSize;
	float2 ratio;
};

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

	resultUV.x = (startPos.x) / (imageSize.x) + input.uv.x * (size.x / imageSize.x);
	resultUV.y = (startPos.y) / (imageSize.y) + input.uv.y * (size.y / imageSize.y);

	float4 mixedColor = { 0,0,0,0 };
	float4 colorResult;

	for (int i = 0; i < 29; i++)
	{
		colorResult = saturate(lightColor[i + 1] / input.distance[i]);
		mixedColor += colorResult;
	}

	float4 color = resource.Sample(samp, resultUV);
	color = saturate(color * (mixedColor + lightColor[0]));
	return color;
}