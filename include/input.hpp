#ifndef INPUT_H
#define INPUT_H

#if !defined(__ANDROID__)
#include <GLFW/glfw3.h>
#endif

#define KEYMAX 348
#include <unordered_map>
#include <cstdint>

enum AndroidCursorAction {
	NONE = -1,
	ACTION_DOWN = 0,
	ACTION_UP = 1,
	ACTION_MOVE = 2
};

struct CursorPos {
	int32_t fingerAction = AndroidCursorAction::NONE;
	double x = 0;
	double y = 0;
};

class Input {
private:
	CursorPos m_primaryCursor = {};
	CursorPos m_lastPrimaryCursor = {};
	CursorPos m_secondaryCursor = {};
	CursorPos m_lastSecondaryCursor = {};
	std::unordered_map<uint32_t, bool> m_keyboardKeys;
	std::unordered_map<uint32_t, bool> m_previousKeyboardKeys;
public:
	Input();
	CursorPos getPrimaryCursor() const;

	bool isCursorHeld();
	bool isCursorPressed();
	bool wasCursorReleased();

#if !defined(__ANDROID__)
	bool isKeyHeld(uint32_t key);
	bool isKeyPressed(uint32_t key);
	bool wasKeyReleased(uint32_t key);
	void readGlfwInput(GLFWwindow* window);
#else
	void readAndroidInput(int32_t action, int32_t index, double x, double y);
#endif
	
};

#endif // INPUT_H