struct MatrixBuffer
{
	float4 worldMatrix;
	float4 viewMatrix;
	float4 projectMatrix;
}

struct VSInput
{
	float4 position : SV_POSITION;
	float4 normal : SV_NORMAL;
	float2 texCoord : TEXCOORD0;
}

struct VSOutput
{
	float4 position : SV_POSITION;
	float3 normal : SV_NORMAL;
	float2 texCoord : TEXCOORD0;
}

VSOutput VSMain(VSInput in)
{
	VSOutput out;
	out.position = mul(in.position, worldMatrix);
	out.position = mul(out.position, viewMatrix);
	out.position = mul(out.position, projectMatrix);

	out.normal = nul(in.position, worldMatrix);
	out.texCoord = in.texCoord;

	return out;
}