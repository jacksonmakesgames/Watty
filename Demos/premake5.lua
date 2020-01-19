local ROOT = "./"
local WATTYVERSION = "0.24"
local CORE = "Watty-Core"
local LIBNAME = CORE .. "_v" .. WATTYVERSION
local WATTYDIR = ROOT .. "../"
local COREDIR = WATTYDIR .. CORE .. "/"

---------------------------------
-- [ WORKSPACE CONFIGURATION   --
---------------------------------
workspace("Demos")

  configurations { "Debug", "Release" }                   -- Optimization/General config mode in VS
  platforms      { "Win32", "Win64", "Mac64" }            -- Dropdown platforms section in VS

  local project_action = "UNDEFINED"
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
  local PROJECT = "PhysicsDemo"
  project(PROJECT)
    kind "ConsoleApp" -- "WindowApp" removes console
    language "C++"
    targetdir (ROOT .. "bin/".."%{cfg.longname}") -- Where the output binary goes. This will be generated when we build from the makefile/visual studio project/etc.
    targetname (PROJECT) -- the name of the executable saved to 'targetdir'
    
    local SourceDir = ROOT .. PROJECT .. "/"

    files { 
      SourceDir .. "**.h", 
      SourceDir .. "**.hpp", 
      SourceDir .. "**.cpp",
      SourceDir .. "**.tpp"
    }

    vpaths {
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

  sysincludedirs {
      SourceDir,
      COREDIR .. "include/",
      COREDIR
      }

    libdirs {
     WATTYDIR .. "bin/" .. "%{cfg.longname}/"
    }

    links {
      LIBNAME
    }

-------------------------------
  -- [ PROJECT CONFIGURATION ] --
  ------------------------------- 
  local PROJECT = "SimpleGame"
  project(PROJECT)
    kind "ConsoleApp" -- "WindowApp" removes console
    language "C++"
    targetdir (ROOT .. "bin/".."%{cfg.longname}") -- Where the output binary goes. This will be generated when we build from the makefile/visual studio project/etc.
    targetname (PROJECT) -- the name of the executable saved to 'targetdir'
    local SourceDir = ROOT .. PROJECT .. "/"

    files { 
      SourceDir .. "**.h", 
      SourceDir .. "**.hpp", 
      SourceDir .. "**.cpp",
      SourceDir .. "**.tpp"
    }

    vpaths {
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

    sysincludedirs{
      SourceDir, 
      COREDIR .. "include/",
      COREDIR 


    }
   
    libdirs{
     WATTYDIR .. "bin/" .. "%{cfg.longname}/"
    }

    links{
      LIBNAME
    }


-------------------------------
  -- [ PROJECT CONFIGURATION ] --
  ------------------------------- 
  local PROJECT = "PlatformerDemo"
  project(PROJECT)
    kind "ConsoleApp" -- "WindowApp" removes console
    language "C++"
    targetdir (ROOT .. "bin/".."%{cfg.longname}") -- Where the output binary goes. This will be generated when we build from the makefile/visual studio project/etc.
    targetname (PROJECT) -- the name of the executable saved to 'targetdir'
    local SourceDir = ROOT .. PROJECT .. "/"

    files { 
      SourceDir .. "**.h", 
      SourceDir .. "**.hpp", 
      SourceDir .. "**.cpp",
      SourceDir .. "**.tpp"
    }

    vpaths {
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

    sysincludedirs {
      SourceDir, 
      COREDIR .. "include/",
      COREDIR


    }

    libdirs {
      WATTYDIR .. "bin/" .. "%{cfg.longname}/"
    }

    links {
      LIBNAME
    }


-------------------------------
  -- [ PROJECT CONFIGURATION ] --
  ------------------------------- 
  local PROJECT = "ConwaysGameOfLife"
  project(PROJECT)
    kind "ConsoleApp" -- "WindowApp" removes console
    language "C++"
    targetdir (ROOT .. "bin/".."%{cfg.longname}") -- Where the output binary goes. This will be generated when we build from the makefile/visual studio project/etc.
    targetname (PROJECT) -- the name of the executable saved to 'targetdir'
    local SourceDir = ROOT .. PROJECT .. "/"

    files { 
      SourceDir .. "**.h", 
      SourceDir .. "**.hpp", 
      SourceDir .. "**.cpp",
      SourceDir .. "**.tpp"
    }

    vpaths {
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

    sysincludedirs {
      SourceDir, 
      COREDIR .. "include/",
      COREDIR


    }

    libdirs {
     WATTYDIR .. "bin/" .. "%{cfg.longname}/"
    }

    links {
      LIBNAME
    }
