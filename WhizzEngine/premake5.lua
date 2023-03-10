project "WhizzEngine"
	kind "SharedLib"
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
	
	defines
	{
		"GLFW_INCLUDE_NONE"
	}
	
	includedirs
	{
		"src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.assimp}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"WZ_PLATFORM_WINDOWS",
			"WZ_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
		}

	
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