
struct VSIn
{
	float3 Pos : POSITION;
	flaot4 Color : COLOR;
};

struct VSOut
{
	float4 Pos : SV_Position;
	float4 Color : COLOR;
};

VSOut main(VSIn in)
{
	VSOut out = (VSOut)0.0f;
	
	Out.Pos = float4(In.Pos, 1.0f);
	Out.Color = In.Color;

	return Out;
}