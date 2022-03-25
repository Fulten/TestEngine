
struct VertexOut
{
	float3 color : COLOR;
	float4 pos : SV_POSITION;
};

VertexOut main(float2 pos : POSITION2D, float3 color: COLOR)
{
	VertexOut vOut;
	vOut.pos = float4(pos.x, pos.y, 1.0f, 1.0f);
	vOut.color = color;
	return vOut;
}