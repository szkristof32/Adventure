workspace "WhizzEngine"
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

include "Game"
include "WhizzEngine"