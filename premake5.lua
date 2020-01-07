local ROOT = "./"

---------------------------------
-- [ WORKSPACE CONFIGURATION   --
---------------------------------

workspace("Watty")

  configurations { "Debug", "Release" }                   -- Optimization/General config mode in VS
  platforms      { "Win32", "Win64", "Mac64" }            -- Dropdown platforms section in VS

  local project_action = "UNDEFINED"
  -- _ACTION is the argument passed into premake5 when you run it.
    if _ACTION ~= nill then
    	project_action = _ACTION
	end
	if _ACTION == "clean" then
		print("Cleaning")
   		os.rmdir(ROOT .. "Make/")
	end

  location( ROOT .. "Make/" .. project_action ) -- Where the project files (vs project, solution, etc) go


  -------------------------------
  -- [ COMPILER/LINKER CONFIG] --
  -------------------------------
  filter "configurations:Debug"    defines { "DEBUG" }  symbols  "On"
  filter "configurations:Release"  defines { "NDEBUG" } optimize "On"
  defines {"CRT_SECURE_NO_WARNINGS","_CRT_NONSTDC_NO_DEPRECATE"}



filter { "platforms:*32" } architecture "x86"
filter { "platforms:*64" } architecture "x86_64"


filter { "system:windows", "action:vs*"}
    flags         { "MultiProcessorCompile", "NoMinimalRebuild" }
    linkoptions   { "/ignore:4099" }      -- Ignore library pdb warnings when running in debug


  -- building makefiles
  filter { "action:gmake" }
    flags { "C++11" } 


  -- building make files on mac specifically
  filter { "system:macosx", "action:gmake"}
    toolset "clang"

  filter {}  -- clear filter when you know you no longer need it!

 -------------------------------
  -- [ PROJECT CONFIGURATION ] --
  ------------------------------- 
  local CORE = "Watty-Core"

  project (CORE)
    kind "StaticLib"
    language "C++"
    targetdir (ROOT .. "bin/".. "%{cfg.longname}") 
    targetname(CORE)
  
    defines {"_LIB"}
  	defines {"CRT_SECURE_NO_WARNINGS","_CRT_NONSTDC_NO_DEPRECATE", "WITH_SDL2"}

    --------------------------------------
    -- [ PROJECT FILES CONFIGURATIONS ] --
    --------------------------------------
    local SourceDir = ROOT .. CORE .. "/"
    files
    { 
      SourceDir .. "**.h", 
      SourceDir .. "**.hpp", 
      SourceDir .. "ext/freetype-gl/*.c",
      SourceDir .. "**.cpp",
      SourceDir .. "**.tpp",
      ROOT .. "Dependencies/glad/src/*",
  	  ROOT .. "Dependencies/soloud/src/audiosource/**.c*",
	  ROOT .. "Dependencies/soloud/src/backend/sdl/**.c*",
	  ROOT .. "Dependencies/soloud/src/filter/**.c*",
	  ROOT .. "Dependencies/soloud/src/core/**.c*"

    }

	includedirs {
	  ROOT .. "Dependencies/sdl/include"
	}

    vpaths 
    {
      ["Header Files/*"] = { 
        SourceDir .. "**.h", 
        SourceDir .. "**.hxx", 
        SourceDir .. "**.hpp",
      },
      ["Source Files/*"] = { 
        SourceDir .. "**.cxx", 
        SourceDir .. "**.cpp",
        SourceDir .. "**.c",
      },
    
	["Source Files/ext/SoLoud/*"]={
 		ROOT .. "Dependencies/soloud/src/audiosource/**.c*",
		ROOT .. "Dependencies/soloud/src/filter/**.c*",
		ROOT .. "Dependencies/soloud/src/core/**.c*"

		}

    }

    filter { "files:**.tpp" }
      flags {"ExcludeFromBuild"}

    filter {}

    sysincludedirs
    {
      SourceDir, -- include root source directory to allow for absolute include paths
      ROOT .. "Dependencies/GLFW/include/",
      ROOT .. "Dependencies/FreeImage/include/",
      ROOT .. CORE .. "/ext/freetype/include/",
      ROOT .. CORE .. "/ext/freetype-gl/",
      ROOT .. "Dependencies/imgui/include/",
      ROOT .. "Dependencies/glad/include/",
      ROOT .. "Dependencies/soloud/src/**",
	  ROOT .. "Dependencies/soloud/include"
    }

   

-------------------------------
  -- [ PROJECT CONFIGURATION ] --
  ------------------------------- 
  local PROJECT = "PhysicsDemo"
  project(PROJECT)
    kind "ConsoleApp" -- "WindowApp" removes console
    language "C++"
    targetdir (ROOT .. "bin/".."%{cfg.longname}".."/Demos/") -- Where the output binary goes. This will be generated when we build from the makefile/visual studio project/etc.
    targetname (PROJECT) -- the name of the executable saved to 'targetdir'
  
  	defines {"CRT_SECURE_NO_WARNINGS","_CRT_NONSTDC_NO_DEPRECATE", "GLFW_DLL"}
  
  --------------------------------------
    -- [ PROJECT FILES CONFIGURATIONS ] --
    --------------------------------------
    local SourceDir = ROOT .. "Demos/".. PROJECT .. "/"

    files
    { 
      SourceDir .. "**.h", 
      SourceDir .. "**.hpp", 
      SourceDir .. "**.cpp",
      SourceDir .. "**.tpp"
    }

    vpaths 
    {
      ["Header Files/*"] = { 
        SourceDir .. "**.h", 
        SourceDir .. "**.hxx", 
        SourceDir .. "**.hpp",
      },
      ["Source Files/*"] = { 
        SourceDir .. "**.cxx", 
        SourceDir .. "**.cpp",
      }
  	}

    sysincludedirs
    {
      SourceDir, 
      ROOT .. CORE .. "/src/",
      ROOT .. "Dependencies/GLFW/include/",
      ROOT .. "Dependencies/glad/include/",
      ROOT .. "Dependencies/FreeImage/include/",
      ROOT .. "Dependencies/imgui/include/",
      ROOT .. CORE .. "/ext/freetype-gl/",
      ROOT .. CORE .. "/ext/freetype/include/"
    }

	filter { "files:**.tpp" }
      flags {"ExcludeFromBuild"}
   	filter {}

    libdirs
    {

    	ROOT .. "bin/".."%{cfg.longname}",
    	ROOT .. "bin/".."%{cfg.longname}/Demos/",

    	ROOT .. "Dependencies/FreeImage/lib/%{cfg.longname}/",
    	ROOT .. "Dependencies/GLFW/lib/%{cfg.longname}/",
    	ROOT .. "Dependencies/Freetype/lib/%{cfg.longname}/",
    	ROOT .. "Dependencies/opengl/lib/%{cfg.longname}/"

    }

    links
    {
  	CORE,
   	"glfw3",
    "FreeImage",
    "FreeType",
    "opengl32"
    }

-------------------------------
  -- [ PROJECT CONFIGURATION ] --
  ------------------------------- 
  local PROJECT = "SimpleGame"
  project(PROJECT)
    kind "ConsoleApp" -- "WindowApp" removes console
    language "C++"
    targetdir (ROOT .. "bin/".."%{cfg.longname}".."/Demos/") -- Where the output binary goes. This will be generated when we build from the makefile/visual studio project/etc.
    targetname (PROJECT) -- the name of the executable saved to 'targetdir'
  
  	defines {"CRT_SECURE_NO_WARNINGS","_CRT_NONSTDC_NO_DEPRECATE", "GLFW_DLL"}
  
  --------------------------------------
    -- [ PROJECT FILES CONFIGURATIONS ] --
    --------------------------------------
    local SourceDir = ROOT .. "Demos/".. PROJECT .. "/"

    files
    { 
      SourceDir .. "**.h", 
      SourceDir .. "**.hpp", 
      SourceDir .. "**.cpp",
      SourceDir .. "**.tpp"
    }

    vpaths 
    {
      ["Header Files/*"] = { 
        SourceDir .. "**.h", 
        SourceDir .. "**.hxx", 
        SourceDir .. "**.hpp",
      },
      ["Source Files/*"] = { 
        SourceDir .. "**.cxx", 
        SourceDir .. "**.cpp",
      }
  	}

    sysincludedirs
    {
      SourceDir, 
      ROOT .. CORE .. "/src/",
      ROOT .. "Dependencies/GLFW/include/",
      ROOT .. "Dependencies/glad/include/",
      ROOT .. "Dependencies/FreeImage/include/",
      ROOT .. "Dependencies/imgui/include/",
      ROOT .. CORE .. "/ext/freetype-gl/",
      ROOT .. CORE .. "/ext/freetype/include/"
    }

	filter { "files:**.tpp" }
      flags {"ExcludeFromBuild"}
   	filter {}
   	
    libdirs
    {

    	ROOT .. "bin/".."%{cfg.longname}",
    	ROOT .. "bin/".."%{cfg.longname}/Demos/",

    	ROOT .. "Dependencies/FreeImage/lib/%{cfg.longname}/",
    	ROOT .. "Dependencies/GLFW/lib/%{cfg.longname}/",
    	ROOT .. "Dependencies/Freetype/lib/%{cfg.longname}/",
    	ROOT .. "Dependencies/opengl/lib/%{cfg.longname}/"

    }

    links
    {
  	CORE,
   	"glfw3",
    "FreeImage",
    "FreeType",
    "opengl32"
    }


-------------------------------
  -- [ PROJECT CONFIGURATION ] --
  ------------------------------- 
  local PROJECT = "PlatformerDemo"
  project(PROJECT)
    kind "ConsoleApp" -- "WindowApp" removes console
    language "C++"
    targetdir (ROOT .. "bin/".."%{cfg.longname}".."/Demos/") -- Where the output binary goes. This will be generated when we build from the makefile/visual studio project/etc.
    targetname (PROJECT) -- the name of the executable saved to 'targetdir'
  
  	defines {"CRT_SECURE_NO_WARNINGS","_CRT_NONSTDC_NO_DEPRECATE", "GLFW_DLL"}
  
  --------------------------------------
    -- [ PROJECT FILES CONFIGURATIONS ] --
    --------------------------------------
    local SourceDir = ROOT .. "Demos/".. PROJECT .. "/"

    files
    { 
      SourceDir .. "**.h", 
      SourceDir .. "**.hpp", 
      SourceDir .. "**.cpp",
      SourceDir .. "**.tpp"
    }

    vpaths 
    {
      ["Header Files/*"] = { 
        SourceDir .. "**.h", 
        SourceDir .. "**.hxx", 
        SourceDir .. "**.hpp",
      },
      ["Source Files/*"] = { 
        SourceDir .. "**.cxx", 
        SourceDir .. "**.cpp",
      }
  	}

    sysincludedirs
    {
      SourceDir, 
      ROOT .. CORE .. "/src/",
      ROOT .. "Dependencies/GLFW/include/",
      ROOT .. "Dependencies/glad/include/",
      ROOT .. "Dependencies/FreeImage/include/",
      ROOT .. "Dependencies/imgui/include/",
      ROOT .. CORE .. "/ext/freetype-gl/",
      ROOT .. CORE .. "/ext/freetype/include/"
    }

	filter { "files:**.tpp" }
      flags {"ExcludeFromBuild"}
   	filter {}
   	
    libdirs
    {

    	ROOT .. "bin/".."%{cfg.longname}",
    	ROOT .. "bin/".."%{cfg.longname}/Demos/",

    	ROOT .. "Dependencies/FreeImage/lib/%{cfg.longname}/",
    	ROOT .. "Dependencies/GLFW/lib/%{cfg.longname}/",
    	ROOT .. "Dependencies/Freetype/lib/%{cfg.longname}/",
    	ROOT .. "Dependencies/opengl/lib/%{cfg.longname}/"

    }

    links
    {
  	CORE,
   	"glfw3",
    "FreeImage",
    "FreeType",
    "opengl32"
    }

-------------------------------
  -- [ PROJECT CONFIGURATION ] --
  ------------------------------- 
  local PROJECT = "ConwaysGameOfLife"
  project(PROJECT)
    kind "ConsoleApp" -- "WindowApp" removes console
    language "C++"
    targetdir (ROOT .. "bin/".."%{cfg.longname}".."/Demos/") -- Where the output binary goes. This will be generated when we build from the makefile/visual studio project/etc.
    targetname (PROJECT) -- the name of the executable saved to 'targetdir'
  
  	defines {"CRT_SECURE_NO_WARNINGS","_CRT_NONSTDC_NO_DEPRECATE", "GLFW_DLL"}
  
  --------------------------------------
    -- [ PROJECT FILES CONFIGURATIONS ] --
    --------------------------------------
    local SourceDir = ROOT .. "Demos/".. PROJECT .. "/"

    files
    { 
      SourceDir .. "**.h", 
      SourceDir .. "**.hpp", 
      SourceDir .. "**.cpp",
      SourceDir .. "**.tpp"
    }

    vpaths 
    {
      ["Header Files/*"] = { 
        SourceDir .. "**.h", 
        SourceDir .. "**.hxx", 
        SourceDir .. "**.hpp",
      },
      ["Source Files/*"] = { 
        SourceDir .. "**.cxx", 
        SourceDir .. "**.cpp",
      }
  	}

    sysincludedirs
    {
      SourceDir, 
      ROOT .. CORE .. "/src/",
      ROOT .. "Dependencies/GLFW/include/",
      ROOT .. "Dependencies/glad/include/",
      ROOT .. "Dependencies/FreeImage/include/",
      ROOT .. "Dependencies/imgui/include/",
      ROOT .. CORE .. "/ext/freetype-gl/",
      ROOT .. CORE .. "/ext/freetype/include/"
    }

	filter { "files:**.tpp" }
      flags {"ExcludeFromBuild"}
   	filter {}
   	
    libdirs
    {

    	ROOT .. "bin/".."%{cfg.longname}",
    	ROOT .. "bin/".."%{cfg.longname}/Demos/",

    	ROOT .. "Dependencies/FreeImage/lib/%{cfg.longname}/",
    	ROOT .. "Dependencies/GLFW/lib/%{cfg.longname}/",
    	ROOT .. "Dependencies/Freetype/lib/%{cfg.longname}/",
    	ROOT .. "Dependencies/opengl/lib/%{cfg.longname}/"

    }

    links
    {
  	CORE,
   	"glfw3",
    "FreeImage",
    "FreeType",
    "opengl32"
    }