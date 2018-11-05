#ifndef APP_MODEL_TABLE_H
#define APP_MODEL_TABLE_H

#include <string>
#include <map>
#include <vector>
#include "engine_include.h"
#include "util/csv_parser.h"

class ModelTable : public Singleton<ModelTable>{
public:
	ModelTable();
	~ModelTable();

	class Item
	{
	public:
		Item() { ; }
		~Item() { ; }

		int id_;
		std::string model;
		engine::Vector postion;
		engine::Vector scale;
		engine::Vector rotate;
		std::string base_map;
		std::string normal_map;
		std::string specular_map;
	};

	bool Init(const char* file_name);
	void Free();
	ModelTable::Item* GetItem(int id) { return data_[id]; }

private:
	std::map<int, ModelTable::Item*> data_;
};


#endif // APP_MODEL_TABLE_H