#include "model_table.h"
#include "model_loader.h"

bool ModelLoader::Loader(int model_id, std::vector<engine::Mesh*>& result) {
	
	ModelTable::Item* item = ModelTable::Instance().GetItem(model_id);
	if (!item){
		return false;
	}

	if (!AssimpUtil::LoadFile(item->model.c_str(), result)){
		return false;
	}

	std::vector<engine::Mesh*>::iterator itr = result.begin();
	for (; itr != result.end(); itr++){
		if (!item->base_map.empty()) {
			(*itr)->material()->SetBaseMap(item->base_map.c_str());
		}
		if (!item->normal_map.empty()) {
			(*itr)->material()->SetNormalMap(item->normal_map.c_str());
		}
		if (!item->specular_map.empty()) {
			(*itr)->material()->SetSpecularMap(item->specular_map.c_str());
		}
	}

	return true;
}