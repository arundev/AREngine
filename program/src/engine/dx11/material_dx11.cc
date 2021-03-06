#include "material_dx11.h"
#include "../graphic/camera_data.h"
#include "../dx11/renderer_dx11.h"
#include "../engine.h"
#include "../math/math.h"
#include "texture_dx11.h"

namespace engine {


MaterialDx11::MaterialDx11():
vertex_shader_(NULL),
geometry_shader_(NULL),
pixel_shader_(NULL),
matrix_buffer_(NULL),
shader_input_layout_(NULL),
effect_(nullptr),
technique_(nullptr),
world_view_projection_mat_(nullptr),
world_mat_(nullptr),
effect_input_layout_(nullptr){

}

MaterialDx11::~MaterialDx11(){

}

bool MaterialDx11::DoInit(){
	return true;
}

void MaterialDx11::DoFree(){
	SAFE_RELEASE(vertex_shader_);
	SAFE_RELEASE(geometry_shader_);
	SAFE_RELEASE(pixel_shader_);
	SAFE_RELEASE(matrix_buffer_);
	SAFE_RELEASE(shader_input_layout_);

	SAFE_RELEASE(effect_);
	SAFE_RELEASE(effect_input_layout_);
}

void MaterialDx11::DoApply()
{
	if (effect_)
	{
		ApplyEffect();
	}
	else if (vertex_shader_ && pixel_shader_)
	{
		ApplyShader();
	}
}

void MaterialDx11::ApplyShader()
{
	RendererDx11* renderer_dx11 = dynamic_cast<RendererDx11*>(g_renderer);
	ID3D11Device* device = renderer_dx11->device();
	ID3D11DeviceContext* device_context = renderer_dx11->device_context();

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBuffer* dataPtr;
	unsigned int bufferNumber;

	//renderer_dx11->SetWireframe(false);

	result = device_context->Map(matrix_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return;
	}

	Matrix viewMat;
	g_camera->GetViewMatrix(&viewMat);

	Matrix world, view, proj;
	//world.TransposeOf(renderer_dx11->world_mat());
	world.TransposeOf(*transform_);
	view.TransposeOf(viewMat);
	proj.TransposeOf(renderer_dx11->projection_mat());

	dataPtr = (MatrixBuffer*)mappedResource.pData;
	dataPtr->world_ = world;
	dataPtr->view_ = view;
	dataPtr->projection_ = proj;


	device_context->Unmap(matrix_buffer_, 0);
	bufferNumber = 0;
	device_context->VSSetConstantBuffers(bufferNumber, 1, &matrix_buffer_);

	device_context->IASetInputLayout(shader_input_layout_);
	device_context->VSSetShader(vertex_shader_, NULL, 0);
	device_context->PSSetShader(pixel_shader_, NULL, 0);

	// base map
	if (base_map_)
	{
		TextureDx11* d3d_texture = dynamic_cast<TextureDx11*>(base_map_);
		ID3D11ShaderResourceView* tex_view = const_cast<ID3D11ShaderResourceView*>(d3d_texture->texture_view());
		ID3D11SamplerState* sampler_state = const_cast<ID3D11SamplerState*>(d3d_texture->sampler_state());
		device_context->PSSetShaderResources(0, 1, &tex_view);
		device_context->PSSetSamplers(0, 1, &sampler_state);
	}
}

void MaterialDx11::ApplyEffect()
{
	RendererDx11* renderer_dx11 = dynamic_cast<RendererDx11*>(g_renderer);
	ID3D11Device* device = renderer_dx11->device();
	ID3D11DeviceContext* device_context = renderer_dx11->device_context();

	// transform
	Matrix viewMat;
	g_camera->GetViewMatrix(&viewMat);
	Matrix world, view, proj;
	//world.TransposeOf(renderer_dx11->world_mat());
	//world.TransposeOf(*transform_);
	//view.TransposeOf(viewMat);
	//proj.TransposeOf(renderer_dx11->projection_mat());

	world = *transform_;
	view = viewMat;
	proj = renderer_dx11->projection_mat();

	Matrix worldViewProj = world * view * proj;;
	world_view_projection_mat_->SetMatrix(reinterpret_cast<float*>(&worldViewProj._11));

	// input layout
	device_context->IASetInputLayout(effect_input_layout_);

	// render
	D3DX11_TECHNIQUE_DESC tech_desc;
	HRESULT hr = technique_->GetDesc(&tech_desc);
	if (FAILED(hr))
	{
		return;
	}
	for (UINT16 p = 0; p < tech_desc.Passes; p++)
	{
		if (base_map_)
		{
			TextureDx11* d3d_texture = dynamic_cast<TextureDx11*>(base_map_);
			ID3D11ShaderResourceView* tex_view = const_cast<ID3D11ShaderResourceView*>(d3d_texture->texture_view());
			ID3D11SamplerState* sampler_state = const_cast<ID3D11SamplerState*>(d3d_texture->sampler_state());

			hr = base_texture_srv_->SetResource(tex_view);
			if (FAILED(hr))
			{
				return;
			}
		}
		technique_->GetPassByIndex(p)->Apply(0, device_context);
	}
}

bool MaterialDx11::CreateShader(){
	RendererDx11* renderer_dx11 = dynamic_cast<RendererDx11*>(g_renderer);
	ID3D11Device* device = renderer_dx11->device();

	HRESULT result = E_FAIL;
	ID3DBlob* error_msg = NULL;
	ID3DBlob* vertex_shader_buffer = NULL;
	ID3DBlob* pixel_shader_buffer = NULL;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	dwShaderFlags |= D3DCOMPILE_DEBUG;
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	std::string full_path = g_file_util->GetShaderFolder() + vs_file_name_;
	WCHAR wstr[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, full_path.c_str(), -1, wstr, sizeof(wstr));


	result = D3DCompileFromFile(wstr, nullptr, 
		D3D_COMPILE_STANDARD_FILE_INCLUDE, "Main", "vs_5_0",
		dwShaderFlags, 0, 
		&vertex_shader_buffer, &error_msg);
	if (FAILED(result))
	{
		const char* error = (char*)error_msg->GetBufferPointer();
		return false;
	}

	full_path = g_file_util->GetShaderFolder() + ps_file_name_;
	MultiByteToWideChar(CP_ACP, 0, full_path.c_str(), -1, wstr, sizeof(wstr));
	result = D3DCompileFromFile(wstr, 0, 0, "Main", "ps_5_0", 
		dwShaderFlags, 0,
		&pixel_shader_buffer, &error_msg);
	if (FAILED(result))
	{
		const char* error = (char*)(error_msg->GetBufferPointer());
		return false;
	}

	result = device->CreateVertexShader(vertex_shader_buffer->GetBufferPointer(), vertex_shader_buffer->GetBufferSize(),
		NULL, &vertex_shader_);
	if (FAILED(result))
	{
		return false;
	}

	result = device->CreatePixelShader(pixel_shader_buffer->GetBufferPointer(), pixel_shader_buffer->GetBufferSize(),
		NULL, &pixel_shader_);
	if (FAILED(result))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC poloygon_layout[3];
	unsigned int num_element;

	poloygon_layout[0].SemanticName = "POSITION";
	poloygon_layout[0].SemanticIndex = 0;
	poloygon_layout[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	poloygon_layout[0].InputSlot = 0;
	poloygon_layout[0].AlignedByteOffset = 0;
	poloygon_layout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	poloygon_layout[0].InstanceDataStepRate = 0;

	poloygon_layout[1].SemanticName = "COLOR";
	poloygon_layout[1].SemanticIndex = 0;
	poloygon_layout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	poloygon_layout[1].InputSlot = 0;
	poloygon_layout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	poloygon_layout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	poloygon_layout[1].InstanceDataStepRate = 0;

	poloygon_layout[2].SemanticName = "TEXCOORD";
	poloygon_layout[2].SemanticIndex = 0;
	poloygon_layout[2].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	poloygon_layout[2].InputSlot = 0;
	poloygon_layout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	poloygon_layout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	poloygon_layout[2].InstanceDataStepRate = 0;


	num_element = sizeof(poloygon_layout) / sizeof(poloygon_layout[0]);
	result = device->CreateInputLayout(poloygon_layout, num_element, 
		vertex_shader_buffer->GetBufferPointer(),
		vertex_shader_buffer->GetBufferSize(), &shader_input_layout_);
	if (FAILED(result))	
	{
		return false;
	}

	SAFE_RELEASE(vertex_shader_buffer);
	SAFE_RELEASE(vertex_shader_buffer);

	D3D11_BUFFER_DESC matrix_desc;
	matrix_desc.Usage = D3D11_USAGE_DYNAMIC;
	matrix_desc.ByteWidth = sizeof(MatrixBuffer);
	matrix_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrix_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrix_desc.MiscFlags = 0;
	matrix_desc.StructureByteStride = 0;
	result = device->CreateBuffer(&matrix_desc, NULL, &matrix_buffer_);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool MaterialDx11::CreateShader(const std::string& fx_file)
{
	RendererDx11* renderer_dx11 = dynamic_cast<RendererDx11*>(g_renderer);
	ID3D11Device* d3d_device = renderer_dx11->device();

	// effect��technique��global variables
	std::string full_path = g_file_util->GetShaderFolder() + fx_file;
	WCHAR wstr[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, full_path.c_str(), -1, wstr, sizeof(wstr));
	ID3DBlob* error_blob = nullptr;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef _DEBUG
	dwShaderFlags |= D3DCOMPILE_DEBUG;
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif


	HRESULT result = D3DX11CompileEffectFromFile(wstr, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, dwShaderFlags, 0, d3d_device, &effect_, &error_blob);
	if (error_blob)
	{
		error_blob->Release();
	}
	if (FAILED(result))
	{
		g_log->Write("failed tp D3DX11CompileEffectFromFile, fx_file = " + std::string(fx_file));
		return false;
	}

	technique_ = effect_->GetTechniqueByName("DemoTechnique");
	world_view_projection_mat_ = effect_->GetVariableByName("g_worldViewProjectionMat")->AsMatrix();
	world_mat_ = effect_->GetVariableByName("g_worldMat")->AsMatrix();
	view_mat_ = effect_->GetVariableByName("g_viewMat")->AsMatrix();
	proj_mat_ = effect_->GetVariableByName("g_projMat")->AsMatrix();

	base_texture_srv_ = effect_->GetVariableByName("g_baseTexture")->AsShaderResource();
	const D3D11_INPUT_ELEMENT_DESC poloygon_layout[] =
	{
		{ "POSITION",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	unsigned int num_element = sizeof(poloygon_layout) / sizeof(poloygon_layout[0]);

	D3DX11_PASS_DESC pass_desc;
	technique_->GetPassByIndex(0)->GetDesc(&pass_desc);
	result = d3d_device->CreateInputLayout(poloygon_layout, num_element, 
		pass_desc.pIAInputSignature, pass_desc.IAInputSignatureSize,
		&effect_input_layout_);
	if (FAILED(result))
	{
		g_log->Write("failed to CreateInputLayout, fx_file = " + std::string(fx_file));
		return false;
	}

	return true;
}


}
