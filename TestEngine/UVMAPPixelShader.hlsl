

// displays a uv map useing the red green channels
float4 main(float2 tex : TEXCOORD0) : SV_TARGET
{
	return float4(tex.x, tex.y, 0.0f, 1.0f);
}