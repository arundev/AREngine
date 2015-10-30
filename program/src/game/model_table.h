#ifndef APP_MODEL_TABLE_H
#define APP_MODEL_TABLE_H

#include <string>
#include <map>
#include <vector>
#include "engine_pch.h"
#include "util/csv_parser.hpp"

class ModelTable {
public:
	ModelTable();
	~ModelTable();

	class Item
	{
	public:
		int id_;
		std::string model;
		std::string base_map;
		std::string normal_map;
		std::string specular_map;
	};

	bool Init(const char* file_name);
	void Free();
	ModelTable::Item* GetItem(int id);

private:
	std::map<int, ModelTable::Item*> data_;
};


#endif // APP_MODEL_TABLE_H