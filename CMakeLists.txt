# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.15)


set(ROOT 						${CMAKE_SOURCE_DIR})
set(WATTYVERSION 				0.28)
set(CORE 						Watty-Core)
set(LIBNAME 					Watty_v${WATTYVERSION})
set(COREDIR 					${CMAKE_SOURCE_DIR}/${CORE}/)
set(CORENAME 					Core_Engine_v${WATTYVERSION})

set(CMAKE_CONFIGURATION_TYPES 	Debug Release Web)

include_directories(
	${COREDIR}
	${COREDIR}include
	${COREDIR}include/Watty
	${CMAKE_SOURCE_DIR}/dependencies/imgui
	${CMAKE_SOURCE_DIR}/dependencies/imgui/examples
	${CMAKE_SOURCE_DIR}/dependencies/glm/include
	${CMAKE_SOURCE_DIR}/dependencies/tiny_obj_loader/include
	${CMAKE_SOURCE_DIR}/dependencies/glfw/include
	${CMAKE_SOURCE_DIR}/dependencies/stb
	${CMAKE_SOURCE_DIR}/dependencies/box2d/include
	${CMAKE_SOURCE_DIR}/dependencies/soloud/include
	${CMAKE_SOURCE_DIR}/dependencies/json/include
	${CMAKE_SOURCE_DIR}/dependencies/emscripten/system/include
	)
add_compile_definitions(
	WATTYRESDIR="${CMAKE_SOURCE_DIR}/${CORE}/res/"
	WATTYVERSION=${WATTYVERSION}
	_LIB
	CRT_SECURE_NO_WARNINGS
	_CRT_NONSTDC_NO_DEPRECATE
	WITH_MINIAUDIO
	WATTY_OPENGL
	)


if(EMSCRIPTEN)

	add_compile_definitions(WATTY_EMSCRIPTEN)
	set(CMAKE_BUILD_TYPE Web)
	set(CMAKE_STATIC_LIBRARY_PREFIX_CPP "")

	include(${CMAKE_SOURCE_DIR}/dependencies/box2d.js/Box2D_v2.3.1/Box2D/UseBox2D.cmake)

	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -s ENVIRONMENT=web -s LLD_REPORT_UNDEFINED -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1 -s WASM=0 -std=c++17 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 --memory-init-file 0")
	set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} ${CMAKE_SOURCE_DIR}/dependencies/box2d.js/box2d.o")
	
	add_subdirectory(Watty-Core)
	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -o Sandbox.html -s USE_GLFW=3 --embed-file ${COREDIR}/res -s TOTAL_MEMORY=27MB")

	project (Watty_Engine)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY	 	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY	 	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY		${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

	add_subdirectory(dependencies/imgui)
	
	add_library(${LIBNAME} STATIC
		$<TARGET_OBJECTS:imgui>
		$<TARGET_OBJECTS:${CORENAME}>
	)

	add_subdirectory(Sandbox)

else()


cmake_policy(SET CMP0015 NEW)
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
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
set (USE_MSVC_RUNTIME_LIBRARY_DLL ON)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR})

set(CMAKE_STATIC_LIBRARY_PREFIX_CPP "")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dependencies/lib/${CMAKE_BUILD_TYPE}")
set(CMAKE_INSTALL_LIBDIR "${CMAKE_SOURCE_DIR}/dependencies/lib/${CMAKE_BUILD_TYPE}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE CMAKE_FILES 		"${CMAKE_SOURCE_DIR}/**/CMakeLists.txt")

if (WIN32)
# Remove 'lib' prefix for shared libraries on Windows
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
#   message(STATUS "Deleting obj files")
#   execute_process(COMMAND "del ./*.dir*")
endif ()

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

include_directories(${CMAKE_SOURCE_DIR}/dependencies/glad/include)

add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/imgui)
add_subdirectory(dependencies/soloud)
add_subdirectory(dependencies/box2d)
add_subdirectory(dependencies/glad)

# add_subdirectory(dependencies/emscripten)
add_subdirectory(Watty-Core)
#TODO consider that maybe object files dont work with emscripten? -> add a case for this and make it another static library 
##LIB
project (Watty_Engine)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY	 	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY		${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
add_library(${LIBNAME} STATIC
$<TARGET_OBJECTS:glfw>
$<TARGET_OBJECTS:soloud>
$<TARGET_OBJECTS:box2d>
$<TARGET_OBJECTS:glad>
$<TARGET_OBJECTS:imgui>
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

endif()