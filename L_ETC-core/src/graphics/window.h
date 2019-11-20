#pragma once
#include <iostream>
#include "../initializers.h"
#include "Vulkan/vulkaninstance.h"
#include "Vulkan/vulkanphysicaldevice.h"
#include "Vulkan/VulkanDevice.h"
#include "Vulkan/VulkanSwapChain.h"
#include "Vulkan/VulkanGraphicsPipeline.h"
#include "Vulkan/VulkanRenderPass.h"
#include "Vulkan/VulkanBuffer.h"
#include "Vulkan/VulkanFrameBuffer.h"

#include <GLFW/glfw3.h>
#include<set>
//#include "font/fontmanager.h"
//#include "texturemanager.h"
#include "../audio/audiomanager.h"

namespace letc {namespace graphics {
#define MAX_KEYS 1024
#define MAX_BUTTONS 32

	const int MAX_FRAMES_IN_FLIGHT = 2;

	class Window {
	public:
	private:


		friend struct GLFWwindow;
		const char* m_title;
		int m_width, m_height;
		GLFWwindow *m_window;
		bool m_closed;

		bool m_keysThisFrame[MAX_KEYS];
		bool m_keysLastFrame[MAX_KEYS];
		bool m_keysDown[MAX_KEYS];
		bool m_buttonsThisFrame[MAX_BUTTONS];
		bool m_buttonsLastFrame[MAX_BUTTONS];
		bool m_buttonsDown[MAX_BUTTONS];
		double mx, my;

		//VULKAN:
		// THESE SHOULD NOT BE POINTERS (PROBABLY)
		VulkanInstance* m_vkInstance;
		VulkanPhysicalDevice* m_vkPhysicalDevice;
		VulkanDevice* m_vkLogicalDevice;
		VkSurfaceKHR m_vkSurface;
		VulkanSwapChain* m_vkSwapChain;
		VulkanRenderPass* m_vkRenderPass;
		VulkanGraphicsPipeline* m_vkGraphicsPipeline;
		VulkanFrameBuffer* m_vkFrameBuffers;
		std::vector<VkCommandBuffer> m_vkCommandBuffers;
		std::vector<VkSemaphore> m_imageAvailableSemaphores;
		std::vector<VkSemaphore> m_renderFinishedSemaphores;
		std::vector<VkFence> m_inFlightFences;
		std::vector<VkFence> m_imagesInFlight;
		size_t m_currentFrame = 0;

		void recreateSwapChain();
		void cleanupSwapChain();
		

	public:
		Window(const char *title, int width, int height);
		~Window();
		bool closed() const;
		void update();

		inline int getWidth() const { return Window::m_width; };
		inline int getHeight() const { return Window::m_height; };
		inline VulkanDevice* getVulkanDevice() { return m_vkLogicalDevice; };

		bool keyDown(unsigned int keycode) const;
		bool keyPressed(unsigned int keycode) const;
		bool mouseButtonDown(unsigned int button) const;
		bool mouseButtonPressed(unsigned int button) const;
		void getMousePos(double& x, double& y) const;


		
	private:
		bool init();
		friend void window_resize_callback(GLFWwindow* window, int width, int height);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

		//TODO: VK
		void initVulkan();
		void drawVulkanFrame();
		void cleanupVulkan();
		std::vector<const char*> getRequiredExtensions();


	};


	//static void GLAPIENTRY openglCallbackFunction(GLenum source,
	//		GLenum type,
	//		GLuint id,
	//		GLenum severity,
	//		GLsizei length,
	//		const GLchar* message,
	//		const void* userParam);


}}