#include "geometry_dx11.h"
#include "renderer_dx11.h"

namespace engine {


GeometryDx11::GeometryDx11() : 
vertex_buffer_(NULL),
index_buffer_(NULL){

}

GeometryDx11::~GeometryDx11(){
	Free();
}

bool GeometryDx11::DoInit(){
	RendererDx11* renderer_dx11 = dynamic_cast<RendererDx11*>(g_renderer);
	ID3D11Device* device = renderer_dx11->device();

	D3D11_BUFFER_DESC vertex_buffer_desc;
	D3D11_BUFFER_DESC index_buffer_desc;
	D3D11_SUBRESOURCE_DATA vertex_src_data;
	D3D11_SUBRESOURCE_DATA index_src_data;
	HRESULT result = E_FAIL;

	vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	vertex_buffer_desc.ByteWidth = vertex_stride*vertex_num_;
	vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertex_buffer_desc.CPUAccessFlags = 0;
	vertex_buffer_desc.MiscFlags = 0;
	vertex_buffer_desc.StructureByteStride = 0;

	vertex_src_data.pSysMem = vertex_data_;
	vertex_src_data.SysMemPitch = 0;
	vertex_src_data.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertex_buffer_desc, &vertex_src_data, &vertex_buffer_);
	if (FAILED(result)){
		Free();
		return false;
	}

	index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	index_buffer_desc.ByteWidth = sizeof(unsigned int)*index_num_;
	index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	index_buffer_desc.CPUAccessFlags = 0;
	index_buffer_desc.MiscFlags = 0;
	index_buffer_desc.StructureByteStride = 0;

	index_src_data.pSysMem = index_data_;
	index_src_data.SysMemPitch = 0;
	index_src_data.SysMemSlicePitch = 0;
	result = device->CreateBuffer(&index_buffer_desc, &index_src_data, &index_buffer_);
	if (FAILED(result)){
		Free();
		return false;
	}

	return true;
}
void GeometryDx11::DoFree(){
	SAFE_RELEASE(vertex_buffer_);
	SAFE_RELEASE(index_buffer_);
}

void GeometryDx11::DoSetDataStream(){
	RendererDx11* renderer_dx11 = dynamic_cast<RendererDx11*>(g_renderer);
	ID3D11Device* device = renderer_dx11->device();
	ID3D11DeviceContext *device_contex = renderer_dx11->device_context();

	unsigned int stride = vertex_stride;
	unsigned int offset = 0;
	device_contex->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);
	device_contex->IASetIndexBuffer(index_buffer_, DXGI_FORMAT_R32_UINT, 0);
	device_contex->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void GeometryDx11::DoFlush(){
	RendererDx11* renderer_dx11 = dynamic_cast<RendererDx11*>(g_renderer);
	ID3D11Device* device = renderer_dx11->device();
	ID3D11DeviceContext *device_contex = renderer_dx11->device_context();

	device_contex->DrawIndexed(index_num_, 0, 0);
}


}