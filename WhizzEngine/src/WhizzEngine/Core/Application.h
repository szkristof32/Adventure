#pragma once

#include "Core.h"
#include "Window.h"

#include "WhizzEngine/Events/Event.h"
#include "WhizzEngine/Events/ApplicationEvent.h"

namespace WhizzEngine {

	class WZ_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		static Application* Get() { return s_Instance; }
	private:
		bool OnClose(WindowCloseEvent& e);
	private:
		static Application* s_Instance;

		Window m_Window;
		bool m_CloseFlag = false;
	};

	Application* CreateApplication();

}