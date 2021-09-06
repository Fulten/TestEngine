

Texture2D<float4> shaderTexture;
SamplerState sampleType;

// uses a uvmap to sample a 2dtexture
float4 main(float2 tex : TEXCOORD0) : SV_TARGET
{
	float4 color = shaderTexture.Sample(sampleType, tex);
	return color;
}