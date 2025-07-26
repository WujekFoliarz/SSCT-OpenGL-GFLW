#include "application.hpp"

#if defined(_WIN32)
#include <Windows.h>
#endif

#if defined(__ANDROID__)
#include <jni.h>
#endif

#include "log.hpp"

static Application application;

bool desktopMain() {
	if (!application.init()) {
		return false;
	}

	while (application.update()) {}

	application.cleanup();
	return true;
}

// Windows-specific code (Standard Executable)
#if (!defined(__ANDROID__) && !defined(COMPILE_TO_DLL))

int main(int argc, char* argv[]) {
	return desktopMain() ? 0 : 1;
}
// Android-specific code
#else

extern "C"
JNIEXPORT void JNICALL 
Java_com_example_androidstudioapplication_MainActivity_00024Renderer_nativeOnSurfaceCreated(JNIEnv* env, jobject obj) {
	application.init();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidstudioapplication_MainActivity_00024Renderer_nativeOnSurfaceChanged(JNIEnv*, jobject, jint width, jint height) {
	glViewport(0, 0, width, height);
	application.getRenderer()->compileShaders();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidstudioapplication_MainActivity_00024Renderer_nativeOnDrawFrame(JNIEnv*, jobject) {
	application.update();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidstudioapplication_MainActivity_nativeOnTouch(JNIEnv*, jobject, jint action, jint index, jfloat x, jfloat y) {
	application.getInput()->readAndroidInput(action, index, x, y);
}

#endif