workspace "chroma-vk"
	startproject "run"
	architecture "x64"
	
	configurations { 
		"Debug", 
		"Release", 
	}

	includedir = {
		["glad"  ] = "vendor/glad/include", 
		["glfw"  ] = "vendor/glfw/include", 
		["glm"   ] = "vendor/glm/include", 
		["stb"   ] = "vendor/stb/include", 
		["vulkan"] = "vendor/vulkan/include", 
	}

	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		runtime   "Debug"
		symbols   "On"
		
		targetdir "%{wks.location}/bin/debug/windows/%{prj.name}"
		objdir    "%{wks.location}/build/debug/windows/%{prj.name}"
	
	filter "configurations:Release"
		runtime   "Release"
		optimize  "On"
		
		targetdir "%{wks.location}/bin/release/windows/%{prj.name}"
		objdir    "%{wks.location}/build/release/windows/%{prj.name}"

group "Application"
	project "chroma-vk"
		location         "chroma-vk"
		language         "C++"
		cppdialect       "C++23"
		kind             "StaticLib"
		staticruntime    "On"
		enablemodules    "On"
		buildstlmodules  "On"
		warnings         "Extra"
		externalwarnings "Off"
		
		includedirs {
			"chroma-vk/source", 
			
			"%{includedir.glad}", 
			"%{includedir.glfw}", 
			"%{includedir.glm}", 
			"%{includedir.stb}", 
			"%{includedir.vulkan}", 
			
			--remove
			"$(VULKAN_SDK)\\Include", 
		}
		libdirs {
			"$(VULKAN_SDK)\\Lib", 
		}
		files {
			"chroma-vk/**.ixx", 	
		}
		links {
			"glad", 
			"glfw", 
			"glm", 
			"stb", 
			"vulkan", 
			
			--remove
			"vulkan-1.lib", 
		}

	project "run"
		location         "run"
		language         "C++"
		cppdialect       "C++23"
		kind             "ConsoleApp"
		staticruntime    "On"
		enablemodules    "On"
		buildstlmodules  "On"
		warnings         "Extra"
		externalwarnings "Off"
		
		includedirs {
			"chroma-vk/source", 
		}
		files {
			"run/source.cpp",  
		}
		links {
			"chroma-vk", 
		}

group "Dependencies"
	include "vendor/glad"
	include "vendor/glfw"
	include "vendor/glm"
	include "vendor/stb"
	include "vendor/vulkan"
group ""