#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace WhizzEngine {

	class WZ_API Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define WZ_CORE_TRACE(...)    ::WhizzEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define WZ_CORE_INFO(...)     ::WhizzEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WZ_CORE_WARN(...)     ::WhizzEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WZ_CORE_ERROR(...)    ::WhizzEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WZ_CORE_CRITICAL(...) ::WhizzEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define WZ_TRACE(...)         ::WhizzEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define WZ_INFO(...)          ::WhizzEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define WZ_WARN(...)          ::WhizzEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define WZ_ERROR(...)         ::WhizzEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define WZ_CRITICAL(...)      ::WhizzEngine::Log::GetClientLogger()->critical(__VA_ARGS__)