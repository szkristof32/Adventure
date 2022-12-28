#pragma once

#include "Core.h"
#include "Window.h"

#include "WhizzEngine/Events/Event.h"
#include "WhizzEngine/Events/ApplicationEvent.h"

#include "WhizzEngine/Rendering/MasterRenderer.h"

namespace WhizzEngine {

	class WZ_API GameManager {
	public:
		static void Init();
		static void Update(Ref<VertexArray> vao); // TODO: remove this later
		static void CleanUp();

		static bool ShouldClose();

		static void OnEvent(Event& e);

		static MasterRenderer* GetRenderer() { return s_Renderer; }
	private:
		static bool OnWindowCloseEvent(WindowCloseEvent& e);
	private:
		static Window* s_Window;
		static bool s_CloseFlag;

		static MasterRenderer* s_Renderer;
	};

}