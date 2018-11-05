#ifndef	ENGINE_PICTURE_UTIL_H
#define ENGINE_PICTURE_UTIL_H

#include "../engine_pch.h"

namespace engine {


class ImageUtil
{
public:
	ImageUtil(){ ; }
	~ImageUtil(){ ; }

	enum Type
	{
		INVALID = 0,
		PNG		= 1,
		TGA		= 2,
		JPG		= 3,
	};

	struct Data
	{
		Type type_;
		unsigned char* data_;
		int width_;
		int height_;
	};
	
	struct TgaHeader
	{
		unsigned char data1_[12];
		unsigned short width_;
		unsigned short height_;
		unsigned char bpp_;
		unsigned char data2_;
	};

	static bool Load(const char* file_name, ImageUtil::Data& result); 
	static ImageUtil::Type GetType(const char* file_name);
	
private:
	static bool LoadPNG(const char* file_name, ImageUtil::Data& result);
	static bool LoadTGA(const char* file_name, ImageUtil::Data& result);
	static bool LoadJPG(const char* file_name, ImageUtil::Data& result);

};


}

#endif // ENGINE_PICTURE_UTIL_H