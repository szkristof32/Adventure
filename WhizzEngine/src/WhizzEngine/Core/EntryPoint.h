#pragma once

#ifdef WZ_PLATFORM_WINDOWS

extern WhizzEngine::Application* WhizzEngine::CreateApplication();

int main(int argc, char** argv)
{
	WhizzEngine::Log::Init();

	auto app = WhizzEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif