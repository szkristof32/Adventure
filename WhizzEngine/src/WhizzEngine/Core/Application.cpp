#include "Application.h"

namespace WhizzEngine {

	Application* Application::s_Instance;

	Application::Application()
	{
		s_Instance = this;
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (true);
	}

}