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
light_buffer_(NULL),
input_layout_(NULL){

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
	SAFE_RELEASE(light_buffer_);
	SAFE_RELEASE(input_layout_);
}

void MaterialDx11::DoApply(){
	RendererDx11* renderer_dx11 = dynamic_cast<RendererDx11*>(g_renderer);
	ID3D11Device* device = renderer_dx11->device();
	ID3D11DeviceContext* device_context = renderer_dx11->device_context();

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBuffer* dataPtr;
	unsigned int bufferNumber;

	// transform matrix
	result = device_context->Map(matrix_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result)) {
		return;
	}

	RTMath::Matrix viewMat;
	g_camera->GetViewMatrix(&viewMat);
	RTMath::Matrix world, view, proj;
	world.TransposeOf(renderer_dx11->world_mat());
	view.TransposeOf(viewMat);
	proj.TransposeOf(renderer_dx11->projection_mat());
	dataPtr = (MatrixBuffer*)mappedResource.pData;
	dataPtr->world = world;
	dataPtr->view = view;
	dataPtr->projection = proj;

	device_context->Unmap(matrix_buffer_, 0);
	bufferNumber = 0;
	device_context->VSSetConstantBuffers(bufferNumber, 1, &matrix_buffer_);

	// lighting
	if (light_buffer_ != NULL){
		result = device_context->Map(light_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result)) {
			return;
		}
		LightingBuffer* lightDataPtr = (LightingBuffer*)mappedResource.pData;
		lightDataPtr->ambient_light_color = renderer_dx11->ambient_light_color();
		lightDataPtr->ambient_light_intensity = renderer_dx11->ambient_light_intensity();
		lightDataPtr->direction_light_color = renderer_dx11->direction_light_color();
		lightDataPtr->direction_light_direction = renderer_dx11->direction_light_direction();
		device_context->Unmap(light_buffer_, 0);
		device_context->PSSetConstantBuffers(bufferNumber, 1, &light_buffer_);
	}

	// set shader texture sampler
	if (base_map_){
		TextureDx11* d3d_texture = dynamic_cast<TextureDx11*>(base_map_);
		ID3D11ShaderResourceView* tex_view = const_cast<ID3D11ShaderResourceView*>(d3d_texture->texture_view());
		ID3D11SamplerState* sampler_state = const_cast<ID3D11SamplerState*>(d3d_texture->sampler_state());
		device_context->PSSetShaderResources(0, 1, &tex_view);
		device_context->PSSetSamplers(0, 1, &sampler_state);
	}

	// set shader
	device_context->IASetInputLayout(input_layout_);
	device_context->VSSetShader(vertex_shader_, NULL, 0);
	device_context->PSSetShader(pixel_shader_, NULL, 0);
}

bool MaterialDx11::CreateShader(){
	RendererDx11* renderer_dx11 = dynamic_cast<RendererDx11*>(g_renderer);
	ID3D11Device* device = renderer_dx11->device();

	HRESULT result = E_FAIL;
	ID3D10Blob* error_msg = NULL;
	ID3D10Blob* vertex_shader_buffer = NULL;
	ID3D10Blob* pixel_shader_buffer = NULL;

	std::string full_path = g_file_util->GetShaderFolder() + vs_file_name_;
	result = D3DX11CompileFromFile(full_path.c_str(), 0, 0, "Main", "vs_5_0", 0, 0, 0, &vertex_shader_buffer, &error_msg, 0);
	if (FAILED(result)){
		const char* error = (char*)error_msg->GetBufferPointer();
		g_log->Write(error);
		return false;
	}

	full_path = g_file_util->GetShaderFolder() + ps_file_name_;
	result = D3DX11CompileFromFile(full_path.c_str(), 0, 0, "Main", "ps_5_0", 0, 0, 0, &pixel_shader_buffer, &error_msg, 0);
	if (FAILED(result)){
		const char* error = (char*)(error_msg->GetBufferPointer());
		g_log->Write(error);
		return false;
	}

	result = device->CreateVertexShader(vertex_shader_buffer->GetBufferPointer(), vertex_shader_buffer->GetBufferSize(),
		NULL, &vertex_shader_);
	if (FAILED(result)){
		return false;
	}

	result = device->CreatePixelShader(pixel_shader_buffer->GetBufferPointer(), pixel_shader_buffer->GetBufferSize(),
		NULL, &pixel_shader_);
	if (FAILED(result)){
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC poloygon_layout[5] = {
		{"SV_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	1, DXGI_FORMAT_R32G32_FLOAT,	0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	/*
	D3D11_INPUT_ELEMENT_DESC poloygon_layout[3] = {
		{ "SV_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	*/

	int num_element = sizeof(poloygon_layout) / sizeof(poloygon_layout[0]);
	result = device->CreateInputLayout(poloygon_layout, num_element, vertex_shader_buffer->GetBufferPointer(),
		vertex_shader_buffer->GetBufferSize(), &input_layout_);
	if (FAILED(result)){
		return false;
	}

	SAFE_RELEASE(vertex_shader_buffer);
	SAFE_RELEASE(pixel_shader_buffer);

	D3D11_BUFFER_DESC matrix_desc;
	matrix_desc.Usage = D3D11_USAGE_DYNAMIC;
	matrix_desc.ByteWidth = sizeof(MatrixBuffer);
	matrix_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrix_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrix_desc.MiscFlags = 0;
	matrix_desc.StructureByteStride = 0;
	result = device->CreateBuffer(&matrix_desc, NULL, &matrix_buffer_);
	if (FAILED(result)){
		return false;
	}

	D3D11_BUFFER_DESC light_buffer_desc;
	light_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	light_buffer_desc.ByteWidth = sizeof(LightingBuffer);
	light_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	light_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	light_buffer_desc.MiscFlags = 0;
	light_buffer_desc.StructureByteStride = 0;
	result = device->CreateBuffer(&light_buffer_desc, NULL, &light_buffer_);
	if (FAILED(result)){
		return false;
	}

	return true;
}

