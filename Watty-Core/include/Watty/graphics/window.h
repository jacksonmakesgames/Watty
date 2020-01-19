﻿#pragma once
#include <iostream>
//#include <GL/glew.h>
#//include <glad/glad.h>
#include <ext/glad/include/glad/glad.h>
#include <ext/GLFW/include/GLFW/glfw3.h>
#include <ext/imgui/include/imgui/imgui.h>
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "font/fontmanager.h"
#include "../audio/audiomanager.h"

#include "../math/vector4.h"


namespace letc {namespace graphics {
#define MAX_KEYS 1024
#define MAX_BUTTONS 32

	static class Window {
	protected:
		bool isResizeable;
		bool isFullScreen;
	public:
		static bool useVSync;
	private:
		friend struct GLFWwindow;
		const char* m_Title;
		int m_Width, m_Height;
		GLFWwindow *m_Window;
		bool m_Closed;

		bool m_keysThisFrame[MAX_KEYS];
		bool m_keysLastFrame[MAX_KEYS];
		bool m_keysFirstFrameDown[MAX_KEYS];
		bool m_buttonsThisFrame[MAX_BUTTONS];
		bool m_buttonsLastFrame[MAX_BUTTONS];
		bool m_buttonsFirstFrameDown[MAX_BUTTONS];
		double mx, my;

		int m_refreshRate;


	public:
		Window(const char *title, int width, int height, bool resizeable, bool fullscreen=false);
		~Window();
		bool closed() const;
		void update();
		void listenForInput();
		void clear() const;

		inline int getWidth() const { return Window::m_Width; };
		inline int getHeight() const { return Window::m_Height; };

		bool keyWasPressed(unsigned int keycode) const;
		bool keyIsDown(unsigned int keycode) const;
		bool keyWasReleased(unsigned int keycode) const;
		bool mouseButtonWasPressed(unsigned int button) const;
		bool mouseButtonIsDown(unsigned int button) const;
		bool mouseButtonWasReleased(unsigned int button) const;
		void getMousePos(double& x, double& y) const;
		static void toggleVSync();
		static void setVSync(bool state);

		inline int getRefreshRate() { return m_refreshRate; };

		
	private:
		bool init();
		friend void window_resize_callback(GLFWwindow* window, int width, int height);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	};


	static void GLAPIENTRY openglCallbackFunction(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam);


}}