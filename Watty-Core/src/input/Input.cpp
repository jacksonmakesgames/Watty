#include <input/Input.h>
namespace letc {

	bool Input::m_keysThisFrame[MAX_KEYS]				;
	bool Input::m_keysLastFrame[MAX_KEYS]				;
	bool Input::m_keysFirstFrameDown[MAX_KEYS]			;
	bool Input::m_buttonsThisFrame[MAX_BUTTONS]		;
	bool Input::m_buttonsLastFrame[MAX_BUTTONS]		;
	bool Input::m_buttonsFirstFrameDown[MAX_BUTTONS]	;

	double Input::scrolledThisFrameY = 0;
	double Input::mx, Input::my = 0;

	void Input::listenForInput() {

		for (int i = 0; i < MAX_KEYS; i++) {
			m_keysFirstFrameDown[i] = false;
		}
		// handle input:
		for (size_t i = 0; i < MAX_KEYS; i++) {
			m_keysFirstFrameDown[i] = m_keysThisFrame[i] && !m_keysLastFrame[i]; // first frame pressed
		}
		memcpy(&m_keysLastFrame, m_keysThisFrame, sizeof(bool) * MAX_KEYS);

		for (size_t i = 0; i < MAX_BUTTONS; i++) {
			m_buttonsFirstFrameDown[i] = m_buttonsThisFrame[i] && !m_buttonsLastFrame[i];
		}
		memcpy(&m_buttonsLastFrame, m_buttonsThisFrame, sizeof(bool) * MAX_BUTTONS);
	}

	void Input::setKeyThisFrame(int key, bool down){
		m_keysThisFrame[key] = down;
	}

	void Input::setButtonThisFrame(int button, bool down){
		m_buttonsThisFrame[button] = down;
	}

	void Input::updateMousePos(double x, double y){
		mx = x;
		my = y;
	}

	void Input::init(){
			for (int i = 0; i < MAX_KEYS; i++) {
				m_keysThisFrame[i] = false;
				m_keysLastFrame[i] = false;
				m_keysFirstFrameDown[i] = false;
			}
			for (int i = 0; i < MAX_BUTTONS; i++) {
				m_buttonsThisFrame[i] = false;
				m_buttonsLastFrame[i] = false;
				m_buttonsFirstFrameDown[i] = false;
			}
		
	}

	void Input::resetScroll(){
		scrolledThisFrameY = 0;
	}

	bool Input::keyIsDown(unsigned int keycode) {
		// if the key is down this frame
		if (keycode >= MAX_KEYS) {
			// TODO: log an error
			return false;
		}
		return m_keysThisFrame[keycode];
	}


	bool Input::keyWasPressed(unsigned int keycode)  {
		// If this is the first frame a key is down
		if (keycode >= MAX_KEYS) {
			// TODO: log an error
			return false;
		}
		return m_keysFirstFrameDown[keycode];
	}


	bool Input::mouseButtonWasPressed(unsigned int button)  {
		if (button >= MAX_BUTTONS) {
			// TODO: log an error
			return false;
		}
		return m_buttonsFirstFrameDown[button];
	}


	bool Input::mouseButtonIsDown(unsigned int button)  {
		if (button >= MAX_BUTTONS) {
			// TODO: log an error
			return false;
		}
		return m_buttonsThisFrame[button];
	}


	bool Input::mouseButtonWasReleased(unsigned int button)  {
		if (button >= MAX_BUTTONS) {
			// TODO: log an error
			return false;
		}
		return (m_buttonsLastFrame[button] && !m_buttonsThisFrame[button]);
	}


	bool Input::keyWasReleased(unsigned int key)  {
		if (key >= MAX_KEYS) {
			// TODO: log an error
			return false;
		}
		return  (m_keysLastFrame[key] && !m_keysThisFrame[key]);;
	}


	void Input::getMousePos(double& x, double& y)  {
		x = mx;
		y = my;
	}



	//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//	Input::setKeyThisFrame(key, action != GLFW_RELEASE);

	//	//Window* win = (Window*)glfwGetWindowUserPointer(window);
	//	//win->m_keysThisFrame[key] = action != GLFW_RELEASE;


	//}


	//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	//	Input::setButtonThisFrame(button, action != GLFW_RELEASE);

	//	//Window* win = (Window*)glfwGetWindowUserPointer(window);
	//	//win->m_buttonsThisFrame[button] = action != GLFW_RELEASE;

	//}


	//void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	//	Input::updateMousePos(xpos, ypos);

	//	//Window* win = (Window*)glfwGetWindowUserPointer(window);
	//	//win->mx = xpos;
	//	//win->my = ypos;

	//}


	//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	//	Input::scrolledThisFrameY = yoffset;

	//	//Window* win = (Window*)glfwGetWindowUserPointer(window);
	//	//win->scrolledThisFrameY = yoffset;
	//}

}