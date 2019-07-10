
// global variables
float4x4 g_worldViewProjectionMat;

// render state
DepthStencilState EnableDepth
{
	DepthEnable = TRUE;
	DepthWriteMask = ALL;
	DepthFunc = LESS;
};

RasterizerState EnableWireframe
{
	FillMode = Solid;
	CullMode = None;
};

// vertex shader
struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
	float4 tex: TEXCOORD0;
	float4 tex2: TEXCOORD1;
	float4 nomal : NORMAL;
	float4 tangent : TANGENT;
	float4 bitangent : BITANGENT;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 tex : TEXCOORD0;
};

PixelInputType VSMain(VertexInputType input)
{
	PixelInputType output;

	input.position.w = 1.0f;
	output.position = mul(input.position, g_worldViewProjectionMat);

	output.color = input.color;
	output.tex = float2(input.tex.x, input.tex.y);

	return output;
}

float4 PSMain(PixelInputType input) : SV_Target
{
	float4 texColor;
	//texColor = g_baseTexture.Sample(BaseTextureSampler, input.tex) * input.color * g_directionLightColor;
	texColor = float4(1.0f, 1.0f, 0.0f, 1.0f);
	return texColor;
}

// technique
technique11 MainTechnique
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VSMain()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PSMain()));

		SetDepthStencilState(EnableDepth, 0);
		SetRasterizerState(EnableWireframe);
	}
}