#ifndef APP_MODEL_LOADER_H
#define APP_MODEL_LOADER_H

#include <vector>
#include "engine_include.h"

class ModelLoader : public Singleton<ModelLoader>
{
public:
	~ModelLoader() { ; }
	ModelLoader() { ; }
	
	bool Loader(int model_id, std::vector<Mesh*>& result);
	
protected:
private:
};

#endif // APP_MODEL_LOADER_H