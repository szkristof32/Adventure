#include "Window.h"

#include "WhizzEngine/Core/Application.h"
#include "WhizzEngine/Events/Events.h"
#include "WhizzEngine/Core/Log.h"

#include <glad/glad.h>

namespace WhizzEngine
{

	Window::Window(u32 width, u32 height, int fps, const std::string& title, bool fullscreen, bool vsync)
		: m_Fps(fps), m_Fullscreen(fullscreen)
	{
		m_Data.Width = width;
		m_Data.Height = height;
		m_Data.Title = title;
		m_Data.VSync = vsync;

		glfwInit();
		const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		SetWindowHints(vidMode);
		NewWindow(vidMode);
		ApplyWindowSettings(vidMode);
		CreateEventCallbacks();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::SetWindowHints(const GLFWvidmode* vidMode)
	{
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_REFRESH_RATE, vidMode->refreshRate);
		glfwWindowHint(GLFW_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_VERSION_MINOR, 3);
	}

	void Window::NewWindow(const GLFWvidmode* vidMode)
	{
		if (m_Fullscreen)
		{
			m_Window = glfwCreateWindow(vidMode->width, vidMode->height, m_Data.Title.c_str(), glfwGetPrimaryMonitor(), nullptr);
		}
		else
		{
			m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
			glfwSetWindowPos(m_Window, (vidMode->width - m_Data.Width) / 2, (vidMode->height - m_Data.Height) / 2);
		}
	}

	void Window::ApplyWindowSettings(const GLFWvidmode* vidMode)
	{
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (status == 0)
		{
			WZ_CORE_CRITICAL("Failed to initialise glad.");
			return;
		}
		WZ_CORE_INFO("OpenGL Info:");
		WZ_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		WZ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		WZ_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		glfwSetWindowUserPointer(m_Window, &m_Data);
		glfwSetWindowSizeLimits(m_Window, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE);
		glfwShowWindow(m_Window);
		SetVSync(m_Data.VSync);
	}

	void Window::CreateEventCallbacks()
	{
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				Application::Get()->OnEvent(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				Application::Get()->OnEvent(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					Application::Get()->OnEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					Application::Get()->OnEvent(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, true);
					Application::Get()->OnEvent(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				Application::Get()->OnEvent(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					Application::Get()->OnEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					Application::Get()->OnEvent(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				Application::Get()->OnEvent(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				Application::Get()->OnEvent(event);
			});
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled ? 1 : 0);
		m_Data.VSync = enabled;
	}

	void Window::GoFullscreen(bool fullscreen)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);
		if (fullscreen)
		{
			SwitchToFullScreen(monitor, vidMode);
		}
		else
		{
			SwitchToWindowed(vidMode);
		}
		m_Fullscreen = fullscreen;
	}

	void Window::SwitchToFullScreen(GLFWmonitor* monitor, const GLFWvidmode* vidMode)
	{
		m_DesiredWidth = m_Data.Width;
		m_DesiredHeight = m_Data.Height;
		glfwSetWindowMonitor(m_Window, monitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);
		glfwSwapInterval(m_Data.VSync ? 1 : 0);
	}

	void Window::SwitchToWindowed(const GLFWvidmode* vidMode)
	{
		glfwSetWindowMonitor(m_Window, NULL, 0, 0, m_DesiredWidth, m_DesiredHeight, vidMode->refreshRate);
		glfwSetWindowPos(m_Window, (vidMode->width - m_DesiredWidth) / 2, (vidMode->height - m_DesiredHeight) / 2);
	}

}