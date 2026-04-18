/*
* Vulkan Example base class
*
* Copyright (C) 2016-2024 by Sascha Willems - www.saschawillems.de
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#pragma once

#ifdef _WIN32
#pragma comment(linker, "/subsystem:windows")
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#else
#error More migration needed
#endif

#include <iostream>
#include <chrono>
#include <sys/stat.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <string>
#include <sstream>
#include <array>
#include <numeric>

//#include "vulkan/vulkan.h" // PETEHUF_TODO: remove

#include "macros.h"
#include "camera.hpp"
#include "keycodes.hpp"

#include "VulkanDevice.hpp"
#include "VulkanSwapChain.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_sdl3.h>
#include <imgui/backends/imgui_impl_sdlgpu3.h>

class VulkanExampleBase
{
private:	
	float fpsTimer = 0.0f;
	uint32_t frameCounter = 0;
	uint32_t destWidth;
	uint32_t destHeight;
	// bool resizing = false;
	void handleMouseMove(int32_t x, int32_t y);
	// PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallback;
	// PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallback;
	// VkDebugReportCallbackEXT debugReportCallback;
	// struct MultisampleTarget {
	// 	struct {
	// 		VkImage image;
	// 		VkImageView view;
	// 		VkDeviceMemory memory;
	// 	} color;
	// 	struct {
	// 		VkImage image;
	// 		VkImageView view;
	// 		VkDeviceMemory memory;
	// 	} depth;
	// } multisampleTarget;
protected:
	// VkInstance instance;
	// VkPhysicalDevice physicalDevice;
	// VkPhysicalDeviceProperties deviceProperties;
	// VkPhysicalDeviceFeatures deviceFeatures;
	// VkPhysicalDeviceMemoryProperties deviceMemoryProperties;
	SDL_GPUDevice* device;
	vks::VulkanDevice *vulkanDevice;
	vks::DummyQueue* queue;
	// VkFormat depthFormat;
	// VkCommandPool cmdPool;
	// VkRenderPass renderPass;
	// std::vector<VkFramebuffer>frameBuffers;
	uint32_t imageIndex = 0;
	// VkDescriptorPool descriptorPool;
	// VkPipelineCache pipelineCache;
	VulkanSwapChain swapChain;
	std::string title = "SDL3 GPU Example";
	std::string name = "sdl3GpuExample";
	void windowResize();
public: 
	static std::vector<const char*> args;
	bool prepared = false;
	uint32_t width = 1280;
	uint32_t height = 720;
	float frameTimer = 1.0f;
	Camera camera;
	glm::vec2 mousePos;
	bool paused = false;
	uint32_t lastFPS = 0;

	struct Settings {
		bool validation = false;
		bool fullscreen = false;
		bool vsync = false;
		bool multiSampling = true;
		//VkSampleCountFlagBits sampleCount = VK_SAMPLE_COUNT_4_BIT;
	} settings;
	
	// struct DepthStencil {
	// 	VkImage image;
	// 	VkDeviceMemory mem;
	// 	VkImageView view;
	// } depthStencil;

	struct GamePadState {
		glm::vec2 axisLeft = glm::vec2(0.0f);
		glm::vec2 axisRight = glm::vec2(0.0f);
	} gamePadState;

	struct MouseButtons {
		bool left = false;
		bool right = false;
		bool middle = false;
	} mouseButtons;

	SDL_Window* window;
	HWND window_WIN32; // PETEHUF_TODO: remove
	HINSTANCE windowInstance; // PETEHUF_TODO: remove

	void setupWindow();
	SDL_AppResult handleMessages(void* appstate, SDL_Event* event);

	VulkanExampleBase();
	virtual ~VulkanExampleBase();
	
	void initVulkan();

	//virtual VkResult createInstance(bool enableValidation);
	virtual void render() = 0;
	virtual void windowResized();
	virtual void setupFrameBuffer();
	virtual void prepare();
	virtual void fileDropped(std::string filename);

	void initSwapchain();
	void setupSwapChain();

	void renderFrame();
};
