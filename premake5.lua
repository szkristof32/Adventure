include "Dependencies.lua"

workspace "Adventure"
	architecture "x86_64"
	startproject "Game"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
	include "WhizzEngine/vendor/GLFW"
	include "WhizzEngine/vendor/Glad"
	include "WhizzEngine/vendor/assimp"
group ""

include "Game"
include "WhizzEngine"