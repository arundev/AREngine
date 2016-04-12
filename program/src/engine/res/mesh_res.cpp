#include "mesh_res.h"


void MeshRes::SetVertexData(const MeshRes::Vertex* data, int num){
	vertices_.resize(num);

	/*MeshRes::Vertex* first = vertices_._Myfirst;
	memcpy(first, data, sizeof(MeshRes::Vertex)*num);*/

	for (int i = 0; i < num;i++)
	{
		vertices_[i] = data[i];
	}
}

void MeshRes::SetIndexData(int* data, int num){
	indices_.resize(num);

	/*int* first = indices_._Myfirst;
	memcpy(first, data, sizeof(int)*num);*/

	for (int i = 0; i < num;i++)
	{
		indices_[i] = data[i];
	}
}