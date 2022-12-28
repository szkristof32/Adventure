#include "GameManager.h"

#include "Log.h"

namespace WhizzEngine {

	Window* GameManager::s_Window;
	bool GameManager::s_CloseFlag = false;
	MasterRenderer* GameManager::s_Renderer;

	void GameManager::Init()
	{
		Log::Init();
		s_Window = new Window(1600, 900, 120, "Whizz Engine", false, true);
		s_Renderer = new MasterRenderer();
	}

	void GameManager::Update(Ref<VertexArray> vao)
	{
		s_Renderer->Render(vao);
		s_Window->OnUpdate();
	}

	void GameManager::CleanUp()
	{
		delete s_Window;
		delete s_Renderer;
	}

	bool GameManager::ShouldClose()
	{
		return s_CloseFlag;
	}

	void GameManager::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(GameManager::OnWindowCloseEvent);
		
		s_Window->OnEvent(e);
	}

	bool GameManager::OnWindowCloseEvent(WindowCloseEvent& e)
	{
		s_CloseFlag = true;
		return true;
	}

}