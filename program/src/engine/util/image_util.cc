#include "image_util.h"

bool ImageUtil::Load(const char* file_name, ImageUtil::Data& result){

	string full_path = g_file_util->GetTextureFolder() + file_name;
	switch (GetType(full_path.c_str()))
	{
	case ImageUtil::PNG:
		return LoadPNG(full_path.c_str(), result);
	case ImageUtil::TGA:
		return LoadTGA(full_path.c_str(), result);
	case ImageUtil::JPG:
		return LoadJPG(full_path.c_str(), result);
	default:
		return false;
		break;
	}
	return false;
}

bool ImageUtil::LoadPNG(const char* file_name, ImageUtil::Data& result){
	return true;
}

bool ImageUtil::LoadTGA(const char* file_name, ImageUtil::Data& result){
	int error, bpp, imageSize, index, i, j, k;
	FILE* filePtr;
	unsigned int count;
	TgaHeader targaFileHeader;
	unsigned char* targaImage;

	error = fopen_s(&filePtr, file_name, "rb");
	if (error != 0){
		return false;
	}

	count = (unsigned int)fread(&targaFileHeader, sizeof(TgaHeader), 1, filePtr);
	if (count != 1)	{
		return false;
	}

	result.height_ = targaFileHeader.height_;
	result.width_  = targaFileHeader.width_;
	bpp = (int)targaFileHeader.bpp_;
	if (bpp != 32){
		return false;
	}

	imageSize = targaFileHeader.height_ * targaFileHeader.width_ * 4;
	targaImage = new unsigned char[imageSize];
	if (!targaImage){
		return false;
	}
	count = (unsigned int)fread(targaImage, 1, imageSize, filePtr);
	if (count != imageSize){
		return false;
	}

	error = fclose(filePtr);
	if (error != 0){
		return false;
	}

	result.data_ = new unsigned char[imageSize];
	if (!result.data_){
		return false;
	}
	index = 0;
	k = (result.width_ * result.height_ * 4) - (result.width_ * 4);
	for (j = 0; j < result.height_; j++)
	{
		for (i = 0; i < result.width_; i++)
		{
			result.data_[index + 0] = targaImage[k + 2];  // Red.
			result.data_[index + 1] = targaImage[k + 1];  // Green.
			result.data_[index + 2] = targaImage[k + 0];  // Blue
			result.data_[index + 3] = targaImage[k + 3];  // Alpha
			k += 4;
			index += 4;
		}
		k -= (result.width_ * 8);
	}
	delete[] targaImage;
	targaImage = 0;
	result.type_ = ImageUtil::TGA;
	
	return true;
}

bool ImageUtil::LoadJPG(const char* file_name, ImageUtil::Data& result){
	return true;
}

ImageUtil::Type ImageUtil::GetType(const char* file_name){
	string str = file_name;
	string::size_type pos = str.find_last_of('.') + 1;
	if (pos == str.npos){
		return ImageUtil::INVALID;
	}

	string::size_type len = str.length() - pos;
	string ext_name = str.substr(pos, len);
	if (ext_name == "tga" || ext_name == "TGA"){
		return ImageUtil::TGA;
	}
	else if (ext_name == "png" || ext_name == "PNG"){
		return ImageUtil::PNG;
	}
	else if (ext_name == "jpg" || ext_name == "JPG"){
		return ImageUtil::JPG;
	}
	 
	return ImageUtil::INVALID;
}