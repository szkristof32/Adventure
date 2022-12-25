#pragma once

#include "Application.h"

#ifdef WZ_PLATFORM_WINDOWS

extern WhizzEngine::Application* WhizzEngine::CreateApplication();

int main(int argc, char** argv)
{
	auto app = WhizzEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif