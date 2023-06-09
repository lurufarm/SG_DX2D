
struct VSIn
{
	float3 Pos : POSITION;
	float4 Color : COLOR;
};

struct VSOut
{
	float4 Pos : SV_Position;
	float4 Color : COLOR;
};

/*cbuffer Transform : register(b0)
{
	float4 Pos;
}*/

cbuffer Transform : register(b0)
{
    float Scale;
    float3 Pos;
    float4 Color;
}


VSOut main(VSIn In)
{
    float3 Inpos = In.Pos;
    Inpos.xy *= Scale;
    Inpos.xy += Pos.xy;
	VSOut Out = (VSOut)0.0f;

	Out.Pos = float4(Inpos, 1.0f);
	Out.Color = Color;
	
    Out.Pos.x /= 800.0f;
    Out.Pos.y /= 450.0f;

	return Out;
}