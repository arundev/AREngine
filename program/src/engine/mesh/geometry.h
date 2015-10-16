#ifndef ENGINE_MESH_GEOMETRY_H
#define ENGINE_MESH_GEOMETRY_H

#include "../engine_pch.h"

class Geometry
{
public:
	Geometry();
	virtual ~Geometry();

	struct Vertex{
		Vector position;
		Color color;
		float tex_coord_x[1];
		float tex_coord_y[1];
	};

	static Geometry* Create();

	bool Init(Vertex* vertex_data, int vertex_num, unsigned int* index_data, int index_num);
	void Free();

	void SetDataSteam();
	void Flush();

protected:
	virtual bool DoInit() = 0;
	virtual void DoFree() = 0;
	virtual void DoSetDataStream() = 0;
	virtual void DoFlush() = 0;

protected:
	Vertex* vertex_data_;
	unsigned int* index_data_;
	int vertex_num_;
	int index_num_;
};


#endif // ENGINE_MODEL_GEOMETRY_H