#include "material_dx11.h"
#include "../camera/camera.h"
#include "../dx11/renderer_dx11.h"
#include "../engine.h"
#include "texture_dx11.h"

MaterialDx11::MaterialDx11():
vertex_shader_(NULL),
geometry_shader_(NULL),
pixel_shader_(NULL),
matrix_buffer_(NULL),
input_layout_(NULL),
texture_samper_state_(NULL){

}

MaterialDx11::~MaterialDx11(){

}

bool MaterialDx11::DoInit(){
	return true;
}

void MaterialDx11::DoFree(){
	SAFE_RELEASE(texture_samper_state_);
	SAFE_RELEASE(vertex_shader_);
	SAFE_RELEASE(geometry_shader_);
	SAFE_RELEASE(pixel_shader_);
	SAFE_RELEASE(matrix_buffer_);
}

void MaterialDx11::DoApply(){
	RendererDx11* renderer_dx11 = dynamic_cast<RendererDx11*>(g_renderer);
	ID3D11Device* device = renderer_dx11->device();
	ID3D11DeviceContext* device_context = renderer_dx11->device_context();

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBuffer* dataPtr;
	unsigned int bufferNumber;

	result = device_context->Map(matrix_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return;
	}

	RTMath::Matrix viewMat;
	g_camera->GetViewMatrix(&viewMat);

	RTMath::Matrix world, view, proj;
	world.TransposeOf(renderer_dx11->world_mat());
	view.TransposeOf(viewMat);
	proj.TransposeOf(renderer_dx11->projection_mat());

	dataPtr = (MatrixBuffer*)mappedResource.pData;
	dataPtr->world_ = world;
	dataPtr->view_ = view;
	dataPtr->projection_ = proj;


	device_context->Unmap(matrix_buffer_, 0);
	bufferNumber = 0;
	device_context->VSSetConstantBuffers(bufferNumber, 1, &matrix_buffer_);

	device_context->IASetInputLayout(input_layout_);
	device_context->VSSetShader(vertex_shader_, NULL, 0);
	device_context->PSSetShader(pixel_shader_, NULL, 0);

	TextureDx11* d3d_texture = dynamic_cast<TextureDx11*>(texture_);
	ID3D11ShaderResourceView* tex_view = d3d_texture->texture_view();
	device_context->PSSetShaderResources(0, 1, &tex_view);
}

bool MaterialDx11::CreateShader(){
	RendererDx11* renderer_dx11 = dynamic_cast<RendererDx11*>(g_renderer);
	ID3D11Device* device = renderer_dx11->device();

	HRESULT result = E_FAIL;
	ID3D10Blob* error_msg = NULL;
	ID3D10Blob* vertex_buffer = NULL;
	ID3D10Blob* pixel_buffer = NULL;

	WCHAR wstr[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, vs_file_name_.c_str(), -1, wstr, sizeof(wstr));
	result = D3DX11CompileFromFile(wstr, 0, 0, "Main", "vs_5_0", 0, 0, 0, &vertex_buffer, &error_msg, 0);
	if (FAILED(result))
	{
		const char* error = (char*)error_msg->GetBufferPointer();
		return false;
	}

	MultiByteToWideChar(CP_ACP, 0, ps_file_name_.c_str(), -1, wstr, sizeof(wstr));
	result = D3DX11CompileFromFile(wstr, 0, 0, "Main", "ps_5_0", 0, 0, 0, &pixel_buffer, &error_msg, 0);
	if (FAILED(result))
	{
		const char* error = (char*)(error_msg->GetBufferPointer());
		return false;
	}

	result = device->CreateVertexShader(vertex_buffer->GetBufferPointer(), vertex_buffer->GetBufferSize(),
		NULL, &vertex_shader_);
	if (FAILED(result))
	{
		return false;
	}


	result = device->CreatePixelShader(pixel_buffer->GetBufferPointer(), pixel_buffer->GetBufferSize(),
		NULL, &pixel_shader_);
	if (FAILED(result))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC poloygon_layout[3];
	unsigned int num_element;

	poloygon_layout[0].SemanticName = "POSITION";
	poloygon_layout[0].SemanticIndex = 0;
	poloygon_layout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
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
	poloygon_layout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	poloygon_layout[2].InputSlot = 0;
	poloygon_layout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	poloygon_layout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	poloygon_layout[2].InstanceDataStepRate = 0;


	num_element = sizeof(poloygon_layout) / sizeof(poloygon_layout[0]);
	result = device->CreateInputLayout(poloygon_layout, num_element, vertex_buffer->GetBufferPointer(),
		vertex_buffer->GetBufferSize(), &input_layout_);
	if (FAILED(result))
	{
		return false;
	}

	SAFE_RELEASE(vertex_buffer);
	SAFE_RELEASE(pixel_buffer);

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

bool MaterialDx11::CreateTexture(){
	RendererDx11* renderer = RendererDx11::Instance();
	ID3D11Device* device = renderer->device();

	D3D11_SAMPLER_DESC desc;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.MipLODBias = 0.0f;
	desc.MaxAnisotropy = 1;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.BorderColor[0] = 0;
	desc.BorderColor[1] = 0;
	desc.BorderColor[2] = 0;
	desc.BorderColor[3] = 0;
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;
	HRESULT hr = device->CreateSamplerState(&desc, &texture_samper_state_);
	if (FAILED(hr)){
		Free();
		return false;
	}

	return true;
}