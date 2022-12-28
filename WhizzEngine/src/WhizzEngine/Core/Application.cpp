#include "Application.h"

namespace WhizzEngine {

	Application* Application::s_Instance;

	Application::Application()
		: m_Window(1600, 900, 60, "Whizz Engine", false, true)
	{
		s_Instance = this;
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (!m_CloseFlag)
		{
			m_Window.OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(WZ_BIND_EVENT_FN(Application::OnClose));

		m_Window.OnEvent(e);
	}

	bool Application::OnClose(WindowCloseEvent& e)
	{
		m_CloseFlag = true;
		return true;
	}

}