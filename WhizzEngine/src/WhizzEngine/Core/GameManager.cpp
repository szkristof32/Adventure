#include "GameManager.h"

#include "Log.h"

namespace WhizzEngine {

	Window* GameManager::s_Window;
	bool GameManager::s_CloseFlag = false;

	void GameManager::Init()
	{
		Log::Init();
		s_Window = new Window(1600, 900, 120, "Whizz Engine", false, true);
	}

	void GameManager::Update()
	{
		s_Window->OnUpdate();
	}

	void GameManager::CleanUp()
	{
		delete s_Window;
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