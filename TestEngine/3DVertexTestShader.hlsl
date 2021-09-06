

struct VertexShaderInput
{
	float4 pos : POSITION0;
	float2 tex : TEXCOORD0;
};

struct VertexShaderOutput
{
	float4 pos : SV_POSITION0;
	float2 tex : TEXCOORD1;
};

VertexShaderOutput main(VertexShaderInput Vin : SV_POSITION : TEXCOORD)
{
	VertexShaderOutput Vout;
	Vout.pos = Vin.pos;
	Vout.tex = Vin.tex;

	return Vout;
}