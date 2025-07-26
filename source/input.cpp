#include "input.hpp"
#include "log.hpp"

Input::Input() {
	for (int i = 0; i < KEYMAX; i++) {
		m_keyboardKeys[i] = false;
		m_previousKeyboardKeys[i] = false;
	}
}

CursorPos Input::getPrimaryCursor() const {
	return m_primaryCursor;
}

bool Input::isCursorHeld() {
#if defined(__ANDROID__)
	return (m_primaryCursor.fingerAction == AndroidCursorAction::ACTION_DOWN || m_primaryCursor.fingerAction == AndroidCursorAction::ACTION_MOVE)
		&& (m_lastPrimaryCursor.fingerAction == AndroidCursorAction::ACTION_DOWN || m_lastPrimaryCursor.fingerAction == AndroidCursorAction::ACTION_MOVE);
#else
	return m_primaryCursor.fingerAction == GLFW_PRESS && m_lastPrimaryCursor.fingerAction == GLFW_PRESS;
#endif
}

bool Input::isCursorPressed() {
#if defined(__ANDROID__)
	static bool wasDown = false;
	bool isDown = m_primaryCursor.fingerAction == AndroidCursorAction::ACTION_DOWN;
	bool justPressed = isDown && !wasDown;
	wasDown = isDown;
	return justPressed;
#else
	return m_primaryCursor.fingerAction == GLFW_PRESS && m_lastPrimaryCursor.fingerAction != GLFW_PRESS;
#endif
}

bool Input::wasCursorReleased() {
#if defined(__ANDROID__)
	static bool wasReleased = false;
	bool isReleased = m_primaryCursor.fingerAction == AndroidCursorAction::ACTION_UP;
	bool justReleased = isReleased && !wasReleased;
	wasReleased = isReleased;
	return justReleased;
#else
	return m_primaryCursor.fingerAction != GLFW_PRESS && m_lastPrimaryCursor.fingerAction == GLFW_PRESS;
#endif
}

#if !defined(__ANDROID__)
bool Input::isKeyHeld(uint32_t key) {
	return m_keyboardKeys[key];
}

bool Input::isKeyPressed(uint32_t key) {
	return m_keyboardKeys[key] && !m_previousKeyboardKeys[key];
}

bool Input::wasKeyReleased(uint32_t key) {
	return !m_keyboardKeys[key] && m_previousKeyboardKeys[key];
}

void Input::readGlfwInput(GLFWwindow* window) {
	m_previousKeyboardKeys = m_keyboardKeys;

	for (int i = 0; i < KEYMAX; i++) {
		m_keyboardKeys[i] = glfwGetKey(window, i);
	}

	glfwGetCursorPos(window, &m_primaryCursor.x, &m_primaryCursor.y);
	m_lastPrimaryCursor = m_primaryCursor;
	m_primaryCursor.fingerAction = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
}
#else
void Input::readAndroidInput(int32_t action, int32_t index, double x, double y) {
	m_lastPrimaryCursor = m_primaryCursor;
	m_lastSecondaryCursor = m_secondaryCursor;

	if (index == 0) {
		m_primaryCursor.fingerAction = action;
		m_primaryCursor.x = x;
		m_primaryCursor.y = y;
	}
	else {
		m_secondaryCursor.fingerAction = action;
		m_secondaryCursor.x = x;
		m_secondaryCursor.y = y;
	}
}

#endif
