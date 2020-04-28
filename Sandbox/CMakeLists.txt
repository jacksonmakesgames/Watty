# set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
if(EMSCRIPTEN)

endif()
project (Sandbox)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY		${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

add_executable(Sandbox src/Sandbox.cpp)

set_target_properties(Sandbox PROPERTIES
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

target_link_directories(Sandbox
	PRIVATE ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}
	)


target_link_libraries(Sandbox
	PRIVATE ${LIBNAME}
	)


