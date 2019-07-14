
cbuffer MatrixBuffer : register(b0)
{
	matrix g_world_mat;
	matrix g_inverse_transpose_world_mat;
	matrix g_world_view_proj_mat;
};

struct VertexInput
{
	float4 position : POSITION;
	float4 color : COLOR;
	float4 tex_coord: TEXCOORD0;
	float4 tex_coord2: TEXCOORD1;
	float4 normal : NORMAL;
	float4 tangent : TANGENT;
	float4 bitangent : BITANGENT;
};



struct VertexOuput
{
    float4 position_ws : TEXCOORD1;
	float3 normal_ws : TEXCOORD2;
	float2 tex_coord : TEXCOORD0;
    float4 position : SV_POSITION;
	float4 color : COLOR;
};


VertexOuput Main(VertexInput input)
{
    VertexOuput output;
   
	input.position.w = 1.0f;
	output.position = mul(g_world_view_proj_mat, input.position);
	output.position_ws = mul(g_world_mat, input.position);
	output.normal_ws = mul(g_inverse_transpose_world_mat, input.normal);
	output.tex_coord = input.tex_coord;
	output.color = input.color;
    
    return output;
}