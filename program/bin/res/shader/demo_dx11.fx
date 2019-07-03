
// global variables
float4x4 g_worldViewProjectionMat;
float4x4 g_worldMat;
float4x4 g_viewMat;
float4x4 g_projMat;
Texture2D g_baseTexture;          

// render state
DepthStencilState EnableDepth
{
	DepthEnable = TRUE;
	DepthWriteMask = ALL;
	DepthFunc = LESS;
};

RasterizerState EnableWireframe
{
	//FillMode = Wireframe;
	FillMode = Solid;

	//CullMode = Back;
	//CullMode = None;
	
	//FrontCounterClockwise = FALSE;
};

SamplerState BaseTextureSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

// vertex shader
struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
	float4 tex: TEXCOORD0;
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
	//texColor = shaderTexture.Sample(samplerType, input.tex) * input.color;
	//texColor = g_baseTexture.Sample(BaseTextureSampler, input.tex) * input.color;
	texColor = g_baseTexture.Sample(BaseTextureSampler, input.tex);
	//texColor = float4(1.0, 100, 0, 0);
	return texColor;
}

// technique
technique11 DemoTechnique
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VSMain()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PSMain()));

		//SetDepthStencilState(EnableDepth, 0);
		SetRasterizerState(EnableWireframe);
	}
}