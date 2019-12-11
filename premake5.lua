local ROOT = "./"


---------------------------------
-- [ WORKSPACE CONFIGURATION   --
---------------------------------
-- Setting up the workspace. A workspace can have multiple Projects. 
-- In visual studio a workspace corresponds to a solution.
workspace("LETC")

  configurations { "Debug", "Release" } -- Optimization/General config mode in VS
  platforms      { "x86" }            -- Dropdown platforms section in VS

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
  --flags "FatalWarnings" -- comment if you don't want warnings to count as errors
  --warnings "Extra"


  -- Here we are setting up what differentiates the configurations that we called "Debug" and "Release"
  filter "configurations:Debug"    defines { "DEBUG" }  symbols  "On"
  filter "configurations:Release"  defines { "NDEBUG" } optimize "On"
  defines {"GLEW_STATIC", "FT2_BUILD_LIBRARY", "CRT_SECURE_NO_WARNINGS","_CRT_NONSTDC_NO_DEPRECATE"}
  --     As an example, we can define a TESTING macro, as well as include extra files and libs:
  --      
  --         filter "configurations:Testing"
  --           defines {"TESTING"}
  --           files { "PATH/TO/TESTING/SOURCE" }
  --           links { "TESTING.lib" }
  --             
  --         filter {} -- clear the filter when done adding to it!


filter { "platforms:*86" } architecture "x86"

-- You can AND filters as follows:
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
  project "LETC-Core"
    kind "StaticLib"
    language "C++"
    targetdir (ROOT .. "bin") -- Where the output binary goes. This will be generated when we build from the makefile/visual studio project/etc.
    targetname "LETC-core" -- the name of the output saved to 'targetdir'
  
    defines {"_LIB"}
  	defines {"FT2_BUILD_LIBRARY", "CRT_SECURE_NO_WARNINGS","_CRT_NONSTDC_NO_DEPRECATE"}

    --------------------------------------
    -- [ PROJECT FILES CONFIGURATIONS ] --
    --------------------------------------
    local SourceDir = ROOT .. "L_ETC-core/";
    -- what files the visual studio project/makefile/etc should know about
    files
    { 
      SourceDir .. "**.h", 
      SourceDir .. "**.hpp", 
      --SourceDir .. "**.c",
      SourceDir .. "ext/freetype-gl/*.c",
      SourceDir .. "**.cpp",
      SourceDir .. "**.tpp",
      ROOT .. "Dependencies/glad/src/*"

    }

    print(SourceDir .. "**.h")
    -- Exclude template files from project (so they don't accidentally get compiled)
    filter { "files:**.tpp" }
      flags {"ExcludeFromBuild"}

    filter {} -- clear filter!


    -- setting up visual studio filters (basically virtual folders).
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
        SourceDir .. "**.c"

      },
    }

    -- You can use filters on files as well. 
    -- Whatever follows will then only apply to files that match the filter.

    -- For template files that are included in headers, we want to make sure that they don't accidentally get compiled.
    filter { "files:**.tpp" }
      flags {"ExcludeFromBuild"}

    filter {} -- clear filter!

    -- where to find header files that you might be including, mainly for library headers.
    sysincludedirs
    {
      SourceDir, -- include root source directory to allow for absolute include paths
      -- include the headers of any libraries/dlls you need
      ROOT .. "Dependencies/GLFW/include/",
      ROOT .. "Dependencies/gorilla-audio/include/",
      ROOT .. "Dependencies/FreeImage/include/",
      ROOT .. "L_ETC-core/ext/freetype/include/",
      ROOT .. "L_ETC-core/ext/freetype-gl/",
      ROOT .. "Dependencies/imgui/include/",
      ROOT .. "Dependencies/glad/include/"
    }


    -------------------------------------------
    -- [ PROJECT DEPENDENCY CONFIGURATIONS ] --
    -------------------------------------------

    -- basically a set of paths/rules for where to find libs/dlls/etc
    libdirs
    {
    	ROOT .. "Dependencies/gorilla-audio/bin/win32/",
    	--ROOT .. "Dependencies/GLEW/lib/",
    	ROOT .. "Dependencies/FreeImage/lib/",
    	ROOT .. "Dependencies/GLFW/lib-vc2019/",
    	ROOT .. "Dependencies/Freetype/lib/",

    	--ROOT .. "Dependencies/OpenGL32/"

      -- provide a path(s) for your libraries that are required when compiling.
      -- fmod, etc.
      -- example: 
      --     "./Source/Dependencies/fmod_version/lib"
      -- or to be more generic:
      --     "./Source/Dependencies/**/lib" which could be constructed from strings, like: 
      --     SourceDir .. "Dependencies/**/lib"
      --     
      -- NOTE: If you want to include debug/release specific libraries use tokens:
      --     %{cfg.buildcfg} evaluates to "Debug", "Release", etc.
      --     
      --     So if you structure your libraries to have a folder with "Debug" or "Release" 
      --     that contain the appropriate lib/dll/whatever then you can just do something like:
      --         SourceDir.."Dependencies/**/lib_%{cfg.buildcfg}" 
      --     Which will for example evaluate for:
      --          "/Source/Dependencies/fmod_01/lib_x32"
      --     Which you would put the 32 bit version of fmod's lib into.
    }

    links
    {
      -- A list of the actual library/dll names to include
      -- For example if you want to include fmod_123.lib you put "fmod_123" here. Just like when adding to visual studio's linker.
    "opengl32",
    "glfw3",
    "FreeImage",
    "gorilla"
    }
   

    -- Premake Note: for any of these you can call them inside of filters, for example:
    --        filter { "configurations:Debug" }
    --           links { "fmod_debug"}
    --        filter { "configurations:Release" }
    --           links { "fmod_release"}
    --           
    --        filter {} -- always clear your filter when done!
    --           
    -- This goes for files, libdirs, really any directives.

-------------------------------
  -- [ PROJECT CONFIGURATION ] --
  ------------------------------- 
  project "PhysicsDemo"
    kind "ConsoleApp" -- "WindowApp" removes console
    language "C++"
    targetdir (ROOT .. "bin/Demos/") -- Where the output binary goes. This will be generated when we build from the makefile/visual studio project/etc.
    targetname "PhysicsDemo" -- the name of the executable saved to 'targetdir'
  
  	defines {"FT2_BUILD_LIBRARY", "CRT_SECURE_NO_WARNINGS","_CRT_NONSTDC_NO_DEPRECATE"}
  
  --------------------------------------
    -- [ PROJECT FILES CONFIGURATIONS ] --
    --------------------------------------
    local SourceDir = ROOT .. "Demos/PhysicsDemo/";
    -- what files the visual studio project/makefile/etc should know about
    files
    { 
      -- all paths in premake can have * for wildcard.
      --     /Some/Path/*.txt     will find any .txt file in /Some/Path
      --     /Some/Path/**.txt    will find any .txt file in /Some/Path and any of its subdirectories
      SourceDir .. "**.h", 
      SourceDir .. "**.hpp", 
     -- SourceDir .. "**.c",
      SourceDir .. "**.cpp",
      SourceDir .. "**.tpp"
    }

    -- Exclude template files from project (so they don't accidentally get compiled)
    filter { "files:**.tpp" }
      flags {"ExcludeFromBuild"}

    filter {} -- clear filter!


    -- setting up visual studio filters (basically virtual folders).
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
      },
    }

    -- You can use filters on files as well. 
    -- Whatever follows will then only apply to files that match the filter.

    -- For template files that are included in headers, we want to make sure that they don't accidentally get compiled.
    filter { "files:**.tpp" }
      flags {"ExcludeFromBuild"}

    filter {} -- clear filter!

    -- where to find header files that you might be including, mainly for library headers.
    sysincludedirs
    {
      SourceDir, -- include root source directory to allow for absolute include paths
      -- include the headers of any libraries/dlls you need
      ROOT .. "L_ETC-core/src/",
      ROOT .. "Dependencies/GLFW/include/",
      ROOT .. "Dependencies/gorilla-audio/include/",
      ROOT .. "Dependencies/FreeImage/include/",
      ROOT .. "L_ETC-core/ext/freetype-gl/",
      ROOT .. "L_ETC-core/ext/freetype/include/",
      ROOT .. "Dependencies/imgui/include/",
      ROOT .. "Dependencies/glad/include/"


    }


    -------------------------------------------
    -- [ PROJECT DEPENDENCY CONFIGURATIONS ] --
    -------------------------------------------

    -- basically a set of paths/rules for where to find libs/dlls/etc
    libdirs
    {

    	ROOT .. "Dependencies/gorilla-audio/bin/win32/",
    	ROOT .. "Dependencies/FreeImage/lib/",
    	ROOT .. "Dependencies/GLFW/lib-vc2019/",
    	ROOT .. "bin/",
    	ROOT .. "Dependencies/Freetype/lib/"

    	--ROOT .. "Dependencies/OpenGL32/"

    }

    links
    {
      -- A list of the actual library/dll names to include
      -- For example if you want to include fmod_123.lib you put "fmod_123" here. Just like when adding to visual studio's linker.
    "LETC-core",
    "opengl32",
    "glfw3",
    "FreeImage",
    "gorilla"
    }

 	filter "configurations:Debug"  links{"freetype_debug"} 
    filter "configurations:Release"  links{"freetype_release"} 
    filter{}

-------------------------------
  -- [ PROJECT CONFIGURATION ] --
  ------------------------------- 
  project "SimpleGame"
    kind "ConsoleApp" -- "WindowApp" removes console
    language "C++"
    targetdir (ROOT .. "bin/Demos/") -- Where the output binary goes. This will be generated when we build from the makefile/visual studio project/etc.
    targetname "SimpleGame" -- the name of the executable saved to 'targetdir'
  
  	defines {"FT2_BUILD_LIBRARY", "CRT_SECURE_NO_WARNINGS","_CRT_NONSTDC_NO_DEPRECATE"}

   --------------------------------------
    -- [ PROJECT FILES CONFIGURATIONS ] --
    --------------------------------------
    local SourceDir = ROOT .. "Demos/SimpleGame/";
    -- what files the visual studio project/makefile/etc should know about
    files
    { 
      -- all paths in premake can have * for wildcard.
      --     /Some/Path/*.txt     will find any .txt file in /Some/Path
      --     /Some/Path/**.txt    will find any .txt file in /Some/Path and any of its subdirectories
      SourceDir .. "**.h", 
      SourceDir .. "**.hpp", 
      --SourceDir .. "**.c",
      SourceDir .. "**.cpp",
      SourceDir .. "**.tpp"
    }

    -- Exclude template files from project (so they don't accidentally get compiled)
    filter { "files:**.tpp" }
      flags {"ExcludeFromBuild"}

    filter {} -- clear filter!


    -- setting up visual studio filters (basically virtual folders).
    vpaths 
    {
      ["Header Files/*"] = { 
        SourceDir .. "**.h", 
        SourceDir .. "**.hxx", 
        SourceDir .. "**.hpp",
      },
      ["Source Files/*"] = { 
       -- SourceDir .. "**.c", 
        SourceDir .. "**.cxx", 
        SourceDir .. "**.cpp",
      },
    }

    -- You can use filters on files as well. 
    -- Whatever follows will then only apply to files that match the filter.

    -- For template files that are included in headers, we want to make sure that they don't accidentally get compiled.
    filter { "files:**.tpp" }
      flags {"ExcludeFromBuild"}

    filter {} -- clear filter!

    -- where to find header files that you might be including, mainly for library headers.
    sysincludedirs
    {
      SourceDir, -- include root source directory to allow for absolute include paths
      -- include the headers of any libraries/dlls you need
      ROOT .. "Dependencies/GLFW/include/",
      ROOT .. "Dependencies/gorilla-audio/include/",
      ROOT .. "Dependencies/FreeImage/include/",
      ROOT .. "L_ETC-core/ext/freetype/include/",
      ROOT .. "L_ETC-core/ext/freetype-gl/",
      ROOT .. "Dependencies/imgui/include/",
      ROOT .. "L_ETC-core/src/",
      ROOT .. "Dependencies/glad/include/"
      
    }


    -------------------------------------------
    -- [ PROJECT DEPENDENCY CONFIGURATIONS ] --
    -------------------------------------------

    -- basically a set of paths/rules for where to find libs/dlls/etc
    libdirs
    {

    	ROOT .. "bin/",
    	ROOT .. "Dependencies/gorilla-audio/bin/win32/",
    	ROOT .. "Dependencies/GLEW/lib/",
    	ROOT .. "Dependencies/FreeImage/lib/",
    	ROOT .. "Dependencies/GLFW/lib-vc2019/",
    	ROOT .. "Dependencies/Freetype/lib/",
    	

    	--ROOT .. "Dependencies/OpenGL32/"

    }

    links
    {
      -- A list of the actual library/dll names to include
      -- For example if you want to include fmod_123.lib you put "fmod_123" here. Just like when adding to visual studio's linker.
    "LETC-core",
    "opengl32",
    "glfw3",
    "FreeImage",
    "gorilla"
    }
    filter "configurations:Debug"  links{"freetype_debug"} 
    filter "configurations:Release"  links{"freetype_release"} 
    filter{}
