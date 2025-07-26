#include "application.hpp"
#include <iostream>
#include "log.hpp"

bool Application::init() {
	m_renderer.init();
	return true;
}

bool Application::update() {
#if !defined(__ANDROID__)
	if (glfwWindowShouldClose(m_renderer.getWindow()))
		return false;
#endif

	m_renderer.draw();

#if !defined(__ANDROID__)
	glfwPollEvents();
	m_input.readGlfwInput(m_renderer.getWindow());
	glfwSwapBuffers(m_renderer.getWindow());
#endif
	return true;
}


bool Application::cleanup() {
	return false;
}

Renderer* Application::getRenderer() {
	return &m_renderer;
}

Input* Application::getInput() {
	return &m_input;
}
