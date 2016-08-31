cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectMatrix;
};

struct VSInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texCoord1 : TEXCOORD0;
	float2 texCoord2 : TEXCOORD1;
	float3 normal : NORMAL;
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD0;
};

VSOutput Main(VSInput input)
{
	VSOutput output;
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectMatrix);

	output.normal = mul(input.position, worldMatrix);
	output.texCoord = input.texCoord1;

	return output;
}