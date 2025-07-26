#include "input.hpp"
#include "input.hpp"
#include "input.hpp"
#include "input.hpp"

Input::Input() {
	for (int i = 0; i < KEYMAX; i++) {
		m_keyboardKeys[i] = false;
		m_previousKeyboardKeys[i] = false;
	}
}

CursorPos Input::getPrimaryCursor() const {
	return m_primaryCursor;
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
}
#else
void Input::readAndroidInput(uint32_t action, double x, double y) {

}
#endif
