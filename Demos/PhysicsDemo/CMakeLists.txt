
project (PhysicsDemo)

add_executable(PhysicsDemo 		src/main.cpp)


set_property(TARGET PhysicsDemo PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")


