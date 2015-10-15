#include "renderer_dx11.h"
#include "util_dx11.h"
#include "../log.h"


RendererDx11::RendererDx11() : 
swap_chain_(NULL),
device_(NULL),
device_context_(NULL),
render_target_view_(NULL),
depth_stencil_buffer_(NULL),
depth_stencil_state_(NULL),
depth_stencil_view_(NULL),
raster_state_(NULL)
{

}

RendererDx11::~RendererDx11(){
	Free();
}

bool RendererDx11::DoInit(){
	HRESULT hr = S_OK;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapter_output;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(hr)){
		return false;
	}

	hr = factory->EnumAdapters(0, &adapter);
	if (FAILED(hr)){
		return false;
	}

	hr = adapter->EnumOutputs(0, &adapter_output);
	if (FAILED(hr)){
		return false;
	}

	DXGI_MODE_DESC* display_mode_list;
	unsigned int num_mode;
	unsigned int numerator;
	unsigned int denominator;
	unsigned int string_length;
	hr = adapter_output->GetDisplayModeList(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_mode, NULL);
	if (FAILED(hr)){
		return false;
	}
	display_mode_list = new DXGI_MODE_DESC[num_mode];
	if (display_mode_list == NULL){
		return false;
	}
	hr = adapter_output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_mode, display_mode_list);
	if (FAILED(hr)){
		return false;
	}
	for (int i = 0; i < num_mode; i++){
		if (display_mode_list[i].Width == (unsigned int)screen_width_){
			numerator = display_mode_list[i].RefreshRate.Numerator;
			denominator = display_mode_list[i].RefreshRate.Denominator;
		}
	}

	DXGI_ADAPTER_DESC adapter_desc;
	hr = adapter->GetDesc(&adapter_desc);
	if (FAILED(hr)){
		return false;
	}
	video_card_memory = (int)(adapter_desc.DedicatedVideoMemory / 1024 / 1024);
	int error = wcstombs_s(&string_length, video_card_description, 128, adapter_desc.Description, 128);
	if (error != 0){
		return false;
	}

	SAFE_DELETE_ARRAY(display_mode_list);
	SAFE_RELEASE(adapter_output);
	SAFE_RELEASE(factory);

	DXGI_SWAP_CHAIN_DESC swap_chain_desc;
	D3D_FEATURE_LEVEL feature_level;
	ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));
	swap_chain_desc.BufferCount = 1;
	swap_chain_desc.BufferDesc.Width = screen_width_;
	swap_chain_desc.BufferDesc.Height = screen_height_;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	if (vsync_enabled_){
		swap_chain_desc.BufferDesc.RefreshRate.Numerator = numerator;
		swap_chain_desc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else{
		swap_chain_desc.BufferDesc.RefreshRate.Numerator = 0;
		swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
	}
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.OutputWindow = (HWND)window_;
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.SampleDesc.Quality = 0;
	swap_chain_desc.Windowed = !full_screen_;
	swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swap_chain_desc.Flags = 0;

	feature_level = D3D_FEATURE_LEVEL_11_0;
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &feature_level, 1,
		D3D11_SDK_VERSION, &swap_chain_desc, &swap_chain_, &device_, NULL, &device_context_);
	if (FAILED(hr)){
		return false;
	}

	ID3D11Texture2D* back_buffer_ptr;
	hr = swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer_ptr);
	if (FAILED(hr)){
		return false;
	} 
	hr = device_->CreateRenderTargetView(back_buffer_ptr, NULL, &render_target_view_);
	if (FAILED(hr)){
		return false;
	}
	SAFE_RELEASE(back_buffer_ptr);

	D3D11_TEXTURE2D_DESC depth_buffer_desc;
	ZeroMemory(&depth_buffer_desc, sizeof(depth_buffer_desc));
	depth_buffer_desc.Width = screen_width_;
	depth_buffer_desc.Height = screen_height_;
	depth_buffer_desc.MipLevels = 1;
	depth_buffer_desc.ArraySize = 1;
	depth_buffer_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depth_buffer_desc.SampleDesc.Count = 1;
	depth_buffer_desc.SampleDesc.Quality = 0;
	depth_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	depth_buffer_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depth_buffer_desc.CPUAccessFlags = 0;
	depth_buffer_desc.MiscFlags = 0;

	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
	hr = device_->CreateTexture2D(&depth_buffer_desc, NULL, &depth_stencil_buffer_);
	if (FAILED(hr)){
		return false;
	}
	ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));  
	depth_stencil_desc.DepthEnable = true;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
	depth_stencil_desc.StencilEnable = true;
	depth_stencil_desc.StencilReadMask = 0xFF;
	depth_stencil_desc.StencilWriteMask = 0xFF;
	depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	hr = device_->CreateDepthStencilState(&depth_stencil_desc, &depth_stencil_state_);
	if (FAILED(hr)){
		return false;
	}
	device_context_->OMSetDepthStencilState(depth_stencil_state_, 1);

	D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
	ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));
	depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_view_desc.Texture2D.MipSlice = 0;
	hr = device_->CreateDepthStencilView(depth_stencil_buffer_, &depth_stencil_view_desc, &depth_stencil_view_);
	if (FAILED(hr)){
		return false;
	}

	D3D11_RASTERIZER_DESC raster_desc;
	D3D11_VIEWPORT viewport;
	float field_of_view, screen_aspect;
	device_context_->OMSetRenderTargets(1, &render_target_view_, depth_stencil_view_);
	raster_desc.AntialiasedLineEnable = false;
	raster_desc.CullMode = D3D11_CULL_NONE;
	raster_desc.DepthBias = 0;
	raster_desc.DepthBiasClamp = 0.0f;
	raster_desc.DepthClipEnable = true;
	raster_desc.FillMode = D3D11_FILL_SOLID;
	raster_desc.FrontCounterClockwise = false;
	raster_desc.MultisampleEnable = false;
	raster_desc.ScissorEnable = false;
	raster_desc.SlopeScaledDepthBias = 0.0f;
	hr = device_->CreateRasterizerState(&raster_desc, &raster_state_);
	if (FAILED(hr)){
		return false;
	}

	device_context_->RSSetState(raster_state_);
	viewport.Width = (float)screen_width_;
	viewport.Height = (float)screen_width_;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	device_context_->RSSetViewports(1, &viewport);

	field_of_view = (float)D3DX_PI / 4.0f;
	screen_aspect = (float)screen_width_ / (float)screen_height_;

	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(&projection, field_of_view, screen_aspect, screen_near_, screen_depth_);
	MatrixFromDx11(&projection, &projection_mat_);
	world_mat_.Identity();

	return true;
}


void RendererDx11::Update(){
	
}

void RendererDx11::PreRender(const Vector& clear_color){
	BeginScene(clear_color.x, clear_color.y, clear_color.z, 1);
}

void RendererDx11::Render(){
	
	
}

void RendererDx11::PostRender(){
	EndScene();
}

void RendererDx11::BeginScene(float red, float green, float blue, float alpha){
	float color[4];
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	device_context_->ClearRenderTargetView(render_target_view_, color);
	device_context_->ClearDepthStencilView(depth_stencil_view_, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return;
}

void RendererDx11::EndScene(){
	if (vsync_enabled_){
		swap_chain_->Present(1, 0);
	}
	else{
		swap_chain_->Present(0, 0);
	}

	return;
}

void RendererDx11::Free(){
	SAFE_RELEASE(swap_chain_);
	SAFE_RELEASE(device_context_);
	SAFE_RELEASE(render_target_view_);
	SAFE_RELEASE(depth_stencil_buffer_);
	SAFE_RELEASE(depth_stencil_state_);
	SAFE_RELEASE(depth_stencil_view_);
	SAFE_RELEASE(device_);
}