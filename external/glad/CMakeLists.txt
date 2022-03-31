cmake_minimum_required(VERSION 3.10.2)

project(GLAD)

add_library(glad STATIC glad.c)

# The directory in with is the HEADER that will be linked to the static file library
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


# Commented just to see if it would work. Maybe I'll get this to run this later
#if(UNIX)
#        target_link_libraries(glad -ldl)
#endif(UNIX)

#set_target_properties(glad PROPERTIES
#        OUTPUT_NAME "glad"
#        FOLDER "GLAD")
