#pragma once

#include "Core.h"
#include "Window.h"

#include "WhizzEngine/Events/Event.h"
#include "WhizzEngine/Events/ApplicationEvent.h"

namespace WhizzEngine {

	class WZ_API GameManager {
	public:
		static void Init();
		static void Update();
		static void CleanUp();

		static bool ShouldClose();

		static void OnEvent(Event& e);
	private:
		static bool OnWindowCloseEvent(WindowCloseEvent& e);
	private:
		static Window* s_Window;
		static bool s_CloseFlag;
	};

}