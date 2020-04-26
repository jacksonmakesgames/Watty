# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.15)


if(POLICY CMP0079)
  cmake_policy(SET CMP0091 NEW)
endif()
if(POLICY CMP0079)
  cmake_policy(SET CMP0079 NEW)
endif()
set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_CXX_STANDARD 			17)
set(CMAKE_CXX_EXTENSIONS 		OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CONFIGURATION_TYPES 	Debug Release)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
set (USE_MSVC_RUNTIME_LIBRARY_DLL ON)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR})

set(CMAKE_STATIC_LIBRARY_PREFIX_CPP "")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dependencies/lib/${CMAKE_BUILD_TYPE}")
set(CMAKE_INSTALL_LIBDIR "${CMAKE_SOURCE_DIR}/dependencies/lib/${CMAKE_BUILD_TYPE}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE CMAKE_FILES 		"${CMAKE_SOURCE_DIR}/**/CMakeLists.txt")

# Remove 'lib' prefix for shared libraries on Windows
if (WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

set(ROOT 						${CMAKE_SOURCE_DIR})
set(WATTYVERSION 				0.27)
set(CORE 						Watty-Core)
set(LIBNAME 					Watty_v${WATTYVERSION})
set(COREDIR 					${CMAKE_SOURCE_DIR}/${CORE}/)
set(CORENAME 					Core_Engine_v${WATTYVERSION})

include_directories(
	${COREDIR}
	${COREDIR}include
	${COREDIR}include/Watty
	${COREDIR}include/ext
	${COREDIR}ext/imgui/include
	${COREDIR}ext/glm/include
	${COREDIR}ext/soloud/include
	${COREDIR}ext/tiny_obj_loader/include
	)


include_directories(${CMAKE_SOURCE_DIR}/dependencies/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/stb)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/SDL/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/box2d/include)

add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

add_compile_definitions(
	WATTYRESDIR="${CMAKE_SOURCE_DIR}/${CORE}/res/"
	WATTYVERSION=${WATTYVERSION}
	_LIB
	CRT_SECURE_NO_WARNINGS
	_CRT_NONSTDC_NO_DEPRECATE
	WITH_SDL2
	WATTY_OPENGL
	)

##DEPS:
add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/SDL)
add_subdirectory(dependencies/box2d)
add_subdirectory(dependencies/glad)



add_subdirectory(Watty-Core)

##LIB
project (Watty_Engine)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY	 	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY		${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})


## Compile:
add_library(${LIBNAME} STATIC
	$<TARGET_OBJECTS:glfw>
	$<TARGET_OBJECTS:SDL2main>
	$<TARGET_OBJECTS:box2d>
	$<TARGET_OBJECTS:glad>
	$<TARGET_OBJECTS:${CORENAME}>
	)

set_target_properties(${LIBNAME} 	
	PROPERTIES
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

set_target_properties( ${LIBNAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}
)



set_target_properties(${CORENAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}
)
# ## Link
target_link_directories(${CORENAME}
	PUBLIC ${COREDIR}ext/FreeImage/lib/${CMAKE_BUILD_TYPE}	
	)

target_link_libraries(${CORENAME}
	PUBLIC opengl32
	)


add_subdirectory(Sandbox)

# foreach (flag CMAKE_C_FLAGS
# 		CMAKE_C_FLAGS_DEBUG
# 		CMAKE_C_FLAGS_RELEASE
# 		CMAKE_C_FLAGS_MINSIZEREL
# 		CMAKE_C_FLAGS_RELWITHDEBINFO)

# 	    if (${flag} MATCHES "/MD")
# 	        string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
# 	    endif()
# 	    if (${flag} MATCHES "/MDd")
# 	        string(REGEX REPLACE "/MDd" "/MTd" ${flag} "${${flag}}")
# 	    endif()
# 	endforeach()
