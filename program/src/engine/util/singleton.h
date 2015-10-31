#ifndef ENGINE_UTIL_SINGLETON
#define ENGINE_UTIL_SINGLETON

template<typename T>
class Singleton {
public:
	Singleton() { ; }
	~Singleton() { ; }

	static T& Instance() {
		static T instance;
		return instance;
	}

private:

};

#endif // ENGINE_UTIL_SINGLETON