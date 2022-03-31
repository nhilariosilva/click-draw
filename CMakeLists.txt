cmake_minimum_required(VERSION 3.10.2)

project(Click)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/glm/include)

list(APPEND GLFW_LIBRARIES
  "${X11_Xrandr_LIB}" "${X11_Xxf86vm_LIB}" "${X11_Xcursor_LIB}"
	"${X11_Xinerama_LIB}" "${X11_Xinput_LIB}"
	"${CMAKE_THREAD_LIBS_INIT}" -lrt -ldl -lm -lX11 -pthread)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glad)

file(GLOB_RECURSE SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/lib/libglfw3.a)
target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/external/glm/lib/libglm_static.a)
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES} glad)
