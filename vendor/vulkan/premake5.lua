project "vulkan"
	language         "C++"
	cppdialect       "C++23"
	kind             "StaticLib"
	staticruntime    "On"
	enablemodules    "On"
	buildstlmodules  "On"
	warnings         "Extra"
	externalwarnings "Off"

	includedirs {
		"$(VULKAN_SDK)\\Include", 
	}
	libdirs {
		"$(VULKAN_SDK)\\Lib", 
	}
	files {
		"include/vulkan_hpp.ixx", 
	}
	
	links {
		"vulkan-1.lib", 
	}
