#include "geometry.h"

Geometry::Geometry() :
vertex_buffer_(NULL),
index_buffer_(NULL),
vertex_data_(NULL),
index_data_(NULL)
{

}

Geometry::~Geometry(){
	Free();
}


bool Geometry::Create(Vertex* vertex_data, int vertex_num, unsigned int* index_data, int index_num){

	if (vertex_data == NULL){
		return false;
	}
	RendererDx11* renderer_dx11 = dynamic_cast<RendererDx11*>(g_renderer);
	ID3D11Device* device = renderer_dx11->device();

	vertex_num_ = vertex_num;
	index_num_ = index_num;

	int vertex_byte_size = sizeof(Vertex)*vertex_num_;
	int index_byte_size = sizeof(unsigned int)*index_num_;
	vertex_data_ = (Vertex*)malloc(vertex_byte_size);
	index_data_ = (unsigned int*)malloc(index_byte_size);
	memcpy(vertex_data_, vertex_data, vertex_byte_size);
	memcpy(index_data_, index_data, index_byte_size);

	D3D11_BUFFER_DESC vertex_buffer_desc;
	D3D11_BUFFER_DESC index_buffer_desc;
	D3D11_SUBRESOURCE_DATA vertex_src_data;
	D3D11_SUBRESOURCE_DATA index_src_data;
	HRESULT result = E_FAIL;

	vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	vertex_buffer_desc.ByteWidth = sizeof(Vertex)*vertex_num;
	vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertex_buffer_desc.CPUAccessFlags = 0;
	vertex_buffer_desc.MiscFlags = 0;
	vertex_buffer_desc.StructureByteStride = 0;
	
	vertex_src_data.pSysMem = vertex_data_;
	vertex_src_data.SysMemPitch = 0;
	vertex_src_data.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertex_buffer_desc, &vertex_src_data, &vertex_buffer_);
	if (FAILED(result)){
		return false;
	}

	index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	index_buffer_desc.ByteWidth = sizeof(int)*index_num;
	index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	index_buffer_desc.CPUAccessFlags = 0;
	index_buffer_desc.MiscFlags = 0;
	index_buffer_desc.StructureByteStride = 0;

	index_src_data.pSysMem = index_data_;
	index_src_data.SysMemPitch = 0;
	index_src_data.SysMemSlicePitch = 0;
	result = device->CreateBuffer(&index_buffer_desc, &index_src_data, &index_buffer_);
	if (FAILED(result)){
		return false;
	}

	return true;
}

void Geometry::Free(){
	SAFE_RELEASE(vertex_buffer_);
	SAFE_RELEASE(index_buffer_);
	SAFE_DELETE(vertex_data_);
	SAFE_DELETE(index_data_);
}

void Geometry::SetDataSteam()
{
	RendererDx11* renderer_dx11 = dynamic_cast<RendererDx11*>(g_renderer);
	ID3D11Device* device = renderer_dx11->device();
	ID3D11DeviceContext *device_contex = renderer_dx11->device_context();

	unsigned int stride = sizeof(Vertex);
	unsigned int offset = 0;

	device_contex->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);
	device_contex->IASetIndexBuffer(index_buffer_, DXGI_FORMAT_R32_UINT, 0);
	device_contex->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Geometry::Flush()
{
	RendererDx11* renderer_dx11 = dynamic_cast<RendererDx11*>(g_renderer);
	ID3D11Device* device = renderer_dx11->device();
	ID3D11DeviceContext *device_contex = renderer_dx11->device_context();

	device_contex->DrawIndexed(index_num_, 0, 0);
}