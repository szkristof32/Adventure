#pragma once

#include <GLFW/glfw3.h>
#include <string>

#include "WhizzEngine/Core/Core.h"

namespace WhizzEngine
{

	class WZ_API Window
	{
	public:
		Window(u32 width, u32 height, int fps, const std::string& title, bool fullscreen, bool vsync);
		~Window();

		void OnUpdate();

		u32 GetWidth() { return m_Data.Width; }
		u32 GetHeight() { return m_Data.Height; }
		int GetFps() { return m_Fps; }
		bool IsVSync() { return m_Data.VSync; }
		void SetVSync(bool enabled);

		float GetAspectRatio() { return (float)m_Data.Width / (float)m_Data.Height; }
		bool IsFullscreen() { return m_Fullscreen; }
		void GoFullscreen(bool fullscreen);
	private:
		void SetWindowHints(const GLFWvidmode* vidMode);
		void NewWindow(const GLFWvidmode* vidMode);
		void ApplyWindowSettings(const GLFWvidmode* vidMode);
		void CreateEventCallbacks();

		void SwitchToFullScreen(GLFWmonitor* monitor, const GLFWvidmode* vidMode);
		void SwitchToWindowed(const GLFWvidmode* vidMode);
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
		};

		WindowData m_Data;
		u32 m_DesiredWidth, m_DesiredHeight;
		int m_Fps;
		bool m_Fullscreen;
	};

}