local ROOT = "./"
local WATTYVERSION = "0.24"
local CORE = "Watty-Core"

local LIBNAME = CORE .. "_v" .. WATTYVERSION


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
  project (CORE)
    kind "StaticLib"
    language "C++"
    targetdir (ROOT .. "bin/".. "%{cfg.longname}") 
    targetname(LIBNAME)
  
    defines {"_LIB"}
  	defines {"CRT_SECURE_NO_WARNINGS","_CRT_NONSTDC_NO_DEPRECATE", "WITH_SDL2", "WATTYVERSION=".. WATTYVERSION}

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
      ROOT .. CORE .. "/ext/glad/src/*",
  	  ROOT .. CORE .. "/ext/soloud/src/audiosource/**.c*",
	  ROOT .. CORE .. "/ext/soloud/src/backend/sdl/**.c*",
	  ROOT .. CORE .. "/ext/soloud/src/filter/**.c*",
	  ROOT .. CORE .. "/ext/soloud/src/core/**.c*"

    }

	includedirs {
	  ROOT .. CORE .. "/ext/sdl/include"
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
 		ROOT .. CORE .. "/ext/soloud/src/audiosource/**.c*",
		ROOT .. CORE .. "/ext/soloud/src/filter/**.c*",
		ROOT .. CORE .. "/ext/soloud/src/core/**.c*"

		}

    }


    sysincludedirs
    {
      SourceDir, -- include root source directory to allow for absolute include paths
      ROOT .. CORE .. "/ext/GLFW/include/",
      ROOT .. CORE .. "/ext/FreeImage/include/",
      ROOT .. CORE .. "/ext/freetype/include/",
      ROOT .. CORE .. "/ext/freetype-gl/",
      ROOT .. CORE .. "/ext/imgui/include/",
      ROOT .. CORE .. "/ext/glad/include/",
	  ROOT .. CORE .. "/ext/soloud/include/"
    }


  libdirs
    {
    	ROOT .. CORE .. "/ext/FreeImage/lib/%{cfg.longname}/",
    	ROOT .. CORE .. "/ext/GLFW/lib/%{cfg.longname}/",
    	ROOT .. CORE .. "/ext/Freetype/lib/%{cfg.longname}/",
    	ROOT .. CORE .. "/ext/opengl/lib/%{cfg.longname}/"

    }

    links
    {
   	"glfw3",
    "FreeImage",
    "FreeType",
    "opengl32"
    }

   