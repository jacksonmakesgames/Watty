local ROOT = "./"
local WATTYVERSION = "0.24"
local CORE = "Watty-Core"

local GRAPHICS_BACKEND = "opengl"
-- local GRAPHICS_BACKEND = "vulkan"


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
  
	cppdialect "C++17"

	if GRAPHICS_BACKEND == "vulkan"
		then defines{"WATTY_VULKAN", "GLFW_INCLUDE_VULKAN"}
	elseif GRAPHICS_BACKEND == "opengl"
		then defines{"WATTY_OPENGL"}
	end

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

      SourceDir .. "**.cpp",
      SourceDir .. "**.tpp",
  	  ROOT .. CORE .. "/ext/soloud/src/audiosource/**.c*",
	  ROOT .. CORE .. "/ext/soloud/src/backend/sdl/**.c*",
	  ROOT .. CORE .. "/ext/soloud/src/filter/**.c*",
	  ROOT .. CORE .. "/ext/soloud/src/core/**.c*"

    }

    if GRAPHICS_BACKEND == "opengl"
      then files{SourceDir .. "ext/freetype-gl/*.c", ROOT .. CORE .. "/ext/glad/src/*"}
    end

	includedirs {
	  ROOT .. CORE .. "/ext/sdl/include"
	}

    vpaths 
    {
      ["Header Files/*"] = { 
        SourceDir .. "**.h", 
        ROOT .. CORE .. "/**.h", 
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
	  ROOT .. CORE .. "/include/Watty/",
	  ROOT .. CORE .. "/include/ext/",
      ROOT .. CORE .. "/ext/GLFW/include/",
      ROOT .. CORE .. "/ext/FreeImage/include/",
      ROOT .. CORE .. "/ext/imgui/include/",
      ROOT .. CORE .. "/ext/glm/include/",
	  ROOT .. CORE .. "/ext/soloud/include/",
	  ROOT .. CORE .. "/ext/stb_image/include/",
	  ROOT .. CORE .. "/ext/tiny_obj_loader/include/"
    }
    if GRAPHICS_BACKEND == "vulkan"
	 	then sysincludedirs{ROOT .. CORE .. "/ext/vulkan/include/"}
		excludes{ROOT .. CORE .. "/src/graphics/opengl/**"}

	elseif GRAPHICS_BACKEND == "opengl"
		      
		then excludes{ROOT .. CORE .. "/src/graphics/vulkan/**"}
			sysincludedirs{	ROOT .. CORE .. "/ext/glad/include/",
							ROOT .. CORE .. "/ext/freetype-gl/",
							ROOT .. CORE .. "/ext/freetype/include/"}
	end

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
    "FreeType"
    }

    

	if GRAPHICS_BACKEND == "opengl"
		then links{"opengl32"}
	end

   

local PROJECT = "Sandbox"
	project(PROJECT)
kind "ConsoleApp" -- "WindowApp" removes console
language "C++"
targetdir (ROOT .. PROJECT .. "/bin/".."%{cfg.longname}") -- Where the output binary goes. This will be generated when we build from the makefile/visual studio project/etc.
targetname (PROJECT) -- the name of the executable saved to 'targetdir'

local SourceDir = ROOT .. "Sandbox/src/"

if GRAPHICS_BACKEND == "vulkan"
		then defines{"WATTY_VULKAN"}
	elseif GRAPHICS_BACKEND == "opengl"
		then defines{"WATTY_OPENGL"}
end

files{ 
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
  ROOT .. "include/",
  ROOT .. CORE .. "/",
  ROOT .. CORE .. "/include/Watty/",
}


libdirs{
	"bin/" .. "%{cfg.longname}/"
}


links{
  LIBNAME
}
