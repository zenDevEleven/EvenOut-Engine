workspace "Engine"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "EvenOut Engine"
	location "Engine"
	kind "StaticLib"
	language "C++"
	
	filter "system:windows"
		cppdialect "C++latest"
		staticruntime "On"
		systemversion "latest"

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Xenon")
		}

project "Xenon"
	location "Xenon"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	filter "system:windows"
		cppdialect "C++latest"
		staticruntime "On"
		systemversion "latest"