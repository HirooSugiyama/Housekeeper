

Texture2D<float4> tex0:register(t0);

sampler TextureSampler:register(s0);

cbuffer cbChangesEveryFrame:register(b0)
{
	float alpha;
	float AspectRatio;
	float2 Dummy;
}



float4 psMain(float4 color:COLOR0, float2 texCoord : TEXCOORD0):SV_Target0
{
	float4 col = tex0.Sample(TextureSampler, texCoord);// * color
	return float4(col.r, col.g, col.b, alpha);

}