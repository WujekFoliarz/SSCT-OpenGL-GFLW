#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "renderer.hpp"
#include "input.hpp"

class Application {
private:
	Renderer m_renderer;
	Input m_input;
public:
	enum class Platform {
		Windows,
		Linux,
		Android,
		Unknown
	};

	inline Platform getPlatform() {
		
	#if defined(__linux__)
		return Platform::Linux;
	#elif defined(__ANDROID__)
		return Platform::Android;
	#elif defined(_WIN32)
		return Platform::Windows;
	#else
		return Platform::Unknown;
	#endif
	}

	bool init();
	bool update();
	bool cleanup();
	Renderer* getRenderer();
	Input* getInput();
};


#endif // APPLICATION_HPP