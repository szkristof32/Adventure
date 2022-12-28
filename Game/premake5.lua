project "Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"src/**.cpp",
		"src/**.h"
	}
	
	includedirs
	{
		"%{wks.location}/WhizzEngine/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.assimp}"
	}
	
	links
	{
		"WhizzEngine"
	}
	
	defines
	{
		"GLFW_INCLUDE_NONE"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines "WZ_PLATFORM_WINDOWS"
	
	filter "configurations:Debug"
		defines "WZ_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "WZ_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "WZ_DIST"
		runtime "Release"
		optimize "on"