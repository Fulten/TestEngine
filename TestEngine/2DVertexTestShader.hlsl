
struct VertexOut
{
	float2 tex : TEXCOORD0;
	float4 pos : SV_POSITION;
};

VertexOut main(float2 pos : POSITION2D, float2 tex : TEXCOORD)
{
	VertexOut vOut;
	vOut.pos = float4(pos.x, pos.y, 0.5f, 1.0f);
	vOut.tex = tex;
	return vOut;
}