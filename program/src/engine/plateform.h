#ifndef ENGINE_PLATFORM_H
#define ENGINE_PLATFORM_H

namespace engine {


class Plateform
{
public:
	Plateform(){ ; }
	~Plateform(){ ; }

	enum OS
	{
		WINDOWS = 0,
		MACOSX = 1,
		LINUX = 2,
		ANDROID = 3,
		IOS = 4,
	};

	enum  GraphicAPI
	{
		GL = 0,
		D3D_11 = 1,
		GLES_2 = 2,
	};

	static void Init();
	static Plateform::OS os(){ return os_; }
	static Plateform::GraphicAPI graphic_api(){ return graphic_api_; }
	
private:
	static Plateform::OS os_;
	static Plateform::GraphicAPI graphic_api_;
};


}
#endif // ENGINE_PLATFORM_H