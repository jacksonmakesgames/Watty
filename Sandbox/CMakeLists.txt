project (Sandbox)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY		${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

add_executable(Sandbox src/Sandbox.cpp)

target_link_directories(Sandbox
	PRIVATE ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}
	)

message(${LIBNAME})

target_link_libraries(Sandbox
	PRIVATE ${LIBNAME}
	)


set_property(TARGET Sandbox PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
