#ifndef INPUT_H
#define INPUT_H

#if !defined(__ANDROID__)
#include <GLFW/glfw3.h>
#endif

#define KEYMAX 348
#include <unordered_map>
#include <cstdint>

struct CursorPos {
	double x = 0;
	double y = 0;
};

class Input {
private:
	CursorPos m_primaryCursor = {};
	CursorPos m_secondaryCursor = {};
	std::unordered_map<uint32_t, bool> m_keyboardKeys;
	std::unordered_map<uint32_t, bool> m_previousKeyboardKeys;
public:
	Input();
	CursorPos getPrimaryCursor() const;
#if !defined(__ANDROID__)
	bool isKeyHeld(uint32_t key);
	bool isKeyPressed(uint32_t key);
	bool wasKeyReleased(uint32_t key);
	void readGlfwInput(GLFWwindow* window);
#else
	void readAndroidInput(uint32_t action, double x, double y);
#endif
	
};

#endif // INPUT_H