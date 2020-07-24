# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.15)


set(ROOT 						${CMAKE_SOURCE_DIR})
set(WATTYVERSION 				0.30.0)
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
	${CMAKE_SOURCE_DIR}/dependencies/freetype-gl
	${CMAKE_SOURCE_DIR}/dependencies/freetype/include
	${CMAKE_SOURCE_DIR}/dependencies/soloud/include
	${CMAKE_SOURCE_DIR}/dependencies/json/include
	${CMAKE_SOURCE_DIR}/dependencies/emscripten/system/include
	)
add_compile_definitions(
	WATTY_RES_DIR="${CMAKE_SOURCE_DIR}/${CORE}/res/"
	WATTY_VERSION="${WATTYVERSION}"
	_LIB
	CRT_SECURE_NO_WARNINGS
	_CRT_NONSTDC_NO_DEPRECATE
	WITH_MINIAUDIO
	WATTY_OPENGL
	FT2_BUILD_LIBRARY
	)

	

include_directories(${CMAKE_SOURCE_DIR}/dependencies/box2d/Box2D_v2.3.1)

add_subdirectory(dependencies/box2d)
add_subdirectory(dependencies/soloud)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY	 	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY	 	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY		${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

set(CMAKE_STATIC_LIBRARY_PREFIX_CPP "")

if(EMSCRIPTEN)

	add_compile_definitions(WATTY_EMSCRIPTEN)
	set(CMAKE_BUILD_TYPE Web)

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -s ALLOW_MEMORY_GROWTH=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s ENVIRONMENT=web -s LLD_REPORT_UNDEFINED -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1 --embed-file ${COREDIR}/res --use-preload-plugins --no-heap-copy")
	
	add_subdirectory(Watty-Core)
	remove_definitions(GL_WITH_GLAD)
	project (Watty_Engine)

	add_subdirectory(dependencies/imgui)
	add_subdirectory(dependencies/freetype)
	add_subdirectory(dependencies/freetype-gl)
	
	add_library(${LIBNAME} STATIC
		$<TARGET_OBJECTS:soloud>
		$<TARGET_OBJECTS:imgui>
		$<TARGET_OBJECTS:Box2D>
		$<TARGET_OBJECTS:freetype>
		$<TARGET_OBJECTS:freetype-gl>
		$<TARGET_OBJECTS:${CORENAME}>
	)

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

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	file(GLOB_RECURSE CMAKE_FILES 		"${CMAKE_SOURCE_DIR}/**/CMakeLists.txt")

	if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
	message(SEND_ERROR "In-source builds are not allowed.")
	endif ()

	add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")
	
	include_directories(${CMAKE_SOURCE_DIR}/dependencies/glad/include)
	
	add_compile_definitions(GL_WITH_GLAD) # for freetype

	add_subdirectory(dependencies/glfw)
	add_subdirectory(dependencies/glad)
	add_subdirectory(dependencies/imgui)
	add_subdirectory(dependencies/freetype)
	add_subdirectory(dependencies/freetype-gl)


	add_subdirectory(Watty-Core)

	project (Watty_Engine)

	add_library(${LIBNAME} STATIC
		$<TARGET_OBJECTS:glfw>
		$<TARGET_OBJECTS:soloud>
		$<TARGET_OBJECTS:Box2D>
		$<TARGET_OBJECTS:glad>
		$<TARGET_OBJECTS:imgui>
		$<TARGET_OBJECTS:freetype>
		$<TARGET_OBJECTS:freetype-gl>
		$<TARGET_OBJECTS:${CORENAME}>
	)



endif()

add_subdirectory(Sandbox)


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
