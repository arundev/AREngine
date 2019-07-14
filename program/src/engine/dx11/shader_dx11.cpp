#include "shader_dx11.h"
#include "renderer_dx11.h"

namespace engine
{

const D3D11_INPUT_ELEMENT_DESC kPoloygonLayout[] =
{
	{ "POSITION",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",  1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",	   0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT",   0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "BITANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

ShaderDx11::ShaderDx11()
{

}

ShaderDx11::~ShaderDx11()
{

}

bool ShaderDx11::Init(const std::string& vs, const std::string& ps)
{
	vs_file_ = vs;
	ps_file_ = ps;

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

	std::string full_path = g_file_util->GetShaderFolder() + vs_file_;
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

	full_path = g_file_util->GetShaderFolder() + ps_file_;
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

	unsigned int num_element = sizeof(kPoloygonLayout) / sizeof(kPoloygonLayout[0]);
	result = device->CreateInputLayout(kPoloygonLayout, num_element, 
		vertex_shader_buffer->GetBufferPointer(), vertex_shader_buffer->GetBufferSize(), 
		&shader_input_layout_);
	if (FAILED(result))
	{
		return false;
	}

	SAFE_RELEASE(vertex_shader_buffer);
	SAFE_RELEASE(vertex_shader_buffer);

	D3D11_BUFFER_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(D3D11_BUFFER_DESC));
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;

	buffer_desc.ByteWidth = sizeof(MatrixProperty);
	result = device->CreateBuffer(&buffer_desc, NULL, &matrix_buffer_);
	if (FAILED(result))
	{
		return false;
	}

	buffer_desc.ByteWidth = sizeof(MaterialProperty);
	result = device->CreateBuffer(&buffer_desc, NULL, &material_buffer_);
	if (FAILED(result))
	{
		return false;
	}

	buffer_desc.ByteWidth = sizeof(LightProperty);
	result = device->CreateBuffer(&buffer_desc, NULL, &light_buffer_);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void ShaderDx11::Update(float elapse)
{

}

void ShaderDx11::Render()
{
	RendererDx11* renderer_dx11 = dynamic_cast<RendererDx11*>(g_renderer);
	ID3D11Device* device = renderer_dx11->device();
	ID3D11DeviceContext* device_context = renderer_dx11->device_context();

	// vs: vertex layout
	device_context->IASetInputLayout(shader_input_layout_);

	// vs: matrix buffer：由于默认情况下shader编译会把row-major优化为colum-major，因此需要transpose
	device_context->UpdateSubresource(matrix_buffer_, 0, nullptr, &transform_.world_mat, 0, 0);
	device_context->VSSetConstantBuffers(0, 1, &matrix_buffer_);

	// ps: material light buffer
	device_context->UpdateSubresource(material_buffer_, 0, nullptr, &material_, 0, 0);
	device_context->UpdateSubresource(light_buffer_, 0, nullptr, &lights_, 0, 0);
	ID3D11Buffer* ps_constant_buffer[2] = { material_buffer_, light_buffer_ };
	device_context->PSSetConstantBuffers(0, 2, ps_constant_buffer);

	// ps: sampler
	auto set_sampler = [=](ID3D11ShaderResourceView* texture_view, ID3D11SamplerState* sampler)->void
	{
		if (texture_view && sampler)
		{
			device_context->PSSetShaderResources(0, 1, &texture_view);
			device_context->PSSetSamplers(0, 1, &sampler);
		}
	};
	set_sampler(base_map_res_, base_map_sampler_);
	set_sampler(normal_map_res_, normal_map_sampler_);
	set_sampler(specular_map_res_, specular_map_sampler_);
	
	// apply shader
	device_context->VSSetShader(vertex_shader_, NULL, 0);
	device_context->PSSetShader(pixel_shader_, NULL, 0);
}

void ShaderDx11::ApplySampler(ID3D11ShaderResourceView* texture_view, ID3D11SamplerState* sampler)
{

}

}

