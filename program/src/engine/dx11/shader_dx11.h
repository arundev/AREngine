#ifndef ENGINE_DX11_BASE_SHADER_H
#define ENGINE_DX11_BASE_SHADER_H

#include "graphic/shader.h"
#include "dx11_include.h"

namespace engine
{
	class ShaderDx11 : public Shader
	{
	public:
		ShaderDx11();
		~ShaderDx11();

		virtual bool Init(const std::string& vs, const std::string& ps);
		virtual void Update(float elapse);
		virtual void Render();

		void set_base_map_sampler(ID3D11ShaderResourceView* texture_view_, ID3D11SamplerState* sampler) 
		{ 
			base_map_res_ = texture_view_; base_map_sampler_ = sampler; 
		}

		void set_normal_map_sampler(ID3D11ShaderResourceView* texture_view_, ID3D11SamplerState* sampler)
		{
			normal_map_res_ = texture_view_; normal_map_sampler_ = sampler;
		}

		void set_specular_map_sampler(ID3D11ShaderResourceView* texture_view_, ID3D11SamplerState* sampler)
		{
			specular_map_res_ = texture_view_; specular_map_sampler_ = sampler;
		}

	private:
		void ApplySampler(ID3D11ShaderResourceView* texture_view, ID3D11SamplerState* sampler);

	private:
		ID3D11VertexShader* vertex_shader_ = nullptr;
		ID3D11GeometryShader* geometry_shader_ = nullptr;
		ID3D11PixelShader* pixel_shader_ = nullptr;
		ID3D11InputLayout* shader_input_layout_ = nullptr;
		ID3D11Buffer* matrix_buffer_ = nullptr;
		ID3D11Buffer* material_buffer_ = nullptr;
		ID3D11Buffer* light_buffer_ = nullptr;

		ID3D11ShaderResourceView* base_map_res_ = nullptr;
		ID3D11SamplerState* base_map_sampler_ = nullptr;
		ID3D11ShaderResourceView* normal_map_res_ = nullptr;
		ID3D11SamplerState* normal_map_sampler_ = nullptr;
		ID3D11ShaderResourceView* specular_map_res_ = nullptr;
		ID3D11SamplerState* specular_map_sampler_ = nullptr;
	};

}

#endif // !ENGINE_DEMO_BASE_SHADER_H

