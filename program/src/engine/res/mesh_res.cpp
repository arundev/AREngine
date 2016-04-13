#include "mesh_res.h"


void MeshRes::SetVertexData(const MeshRes::Vertex* data, int num){
	vertices_.resize(num);

	MeshRes::Vertex* first = vertices_._Myfirst;
	memcpy(first, data, sizeof(MeshRes::Vertex)*num);
}

void MeshRes::SetIndexData(int* data, int num){
	indices_.resize(num);

	int* first = indices_._Myfirst;
	memcpy(first, data, sizeof(int)*num);
}