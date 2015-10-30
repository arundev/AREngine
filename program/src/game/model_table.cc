#include "model_table.h"

ModelTable::ModelTable() {

}

ModelTable::~ModelTable() {
	Free();
}


bool ModelTable::Init(const char* file_name) {
	Free();

	const char field_terminator = ',';
	const char line_terminator = '\n';
	const char enclosure_char = '"';

	csv_parser file_parser;
	file_parser.set_skip_lines(1);
	if (!file_parser.init(file_name)) {
		return false;
	}
	
	file_parser.set_enclosed_char(enclosure_char, ENCLOSURE_OPTIONAL);
	file_parser.set_field_term_char(field_terminator);
	file_parser.set_line_term_char(line_terminator);
	unsigned int row_count = 1U;

	while (file_parser.has_more_rows()) {
		unsigned int i = 0;
		csv_row row = file_parser.get_row();
		
		int id = atoi(row[0].c_str());
		ModelTable::Item* item = new ModelTable::Item();
		item->id_ = id;
		item->base_map = row[1];
		item->normal_map = row[2];
		item->specular_map = row[3];


		SAFE_DELETE(data_[id]);
		data_[key] = 
		

		row_count++;
	}


	return true;
}

void ModelTable::Free() {
	std::map<int, ModelTable::Item*>::iterator table_itr = data_.begin();
	for (; table_itr != data_.end(); table_itr++) {
		SAFE_DELETE(*table_itr->second);
	}
	data_.clear();
}