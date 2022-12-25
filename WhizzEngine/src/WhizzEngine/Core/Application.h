#pragma once

#include "Core.h"

namespace WhizzEngine {

	class WZ_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		static Application* Get() { return s_Instance; }
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();

}