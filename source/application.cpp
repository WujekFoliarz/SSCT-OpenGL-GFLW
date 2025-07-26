#include "application.hpp"
#include <iostream>
#include "log.hpp"

bool Application::init() {
	m_renderer.init();
	return true;
}

bool Application::update() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#if !defined(__ANDROID__)
	if (glfwWindowShouldClose(m_renderer.getWindow()))
		return false;

	glfwPollEvents();
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
