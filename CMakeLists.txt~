#################################################
# Projeto Kagami
#################################################

project(Kagami)
cmake_minimum_required(VERSION 3.0)

if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()


################################################################################
# COMPILER
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


################################################################################
# CMake variables
set(${PROJECT_NAME}_ROOT_DIR         ${CMAKE_SOURCE_DIR})

SET(CMAKE_MODULE_PATH                ${${PROJECT_NAME}_ROOT_DIR}/cmake)
SET(CMAKE_CURRENT_BINARY_DIR            ${${PROJECT_NAME}_ROOT_DIR}/build)
SET(CMAKE_INSTALL_PREFIX             ${${PROJECT_NAME}_ROOT_DIR}/bin)


################################################################################
# OpenGL

find_package(OpenGL REQUIRED)

include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
        message(Error "OpenGL not found")
endif(NOT OPENGL_FOUND)


################################################################################
# GLEW

#If you have an error with GLEW use this command:  sudo apt-get install libglew-dev

find_package(GLEW REQUIRED)
#include_directories(${GLEW_INCLUDE_DIRS})
#add_definitions(${GLEW_DEFINITIONS})

if(GLEW_FOUND)
		include_directories(${GLEW_INCLUDE_DIRS})
    	link_libraries(${GLEW_LIBRARIES})
    	add_definitions(${GLEW_DEFINITIONS})
endif(GLEW_FOUND)
if(NOT GLEW_FOUND)
		message(Error "GLEW not found")
endif(NOT GLEW_FOUND)


################################################################################
# GLFW

#When including GLFW as part of your build, you probably don't want to build the GLFW tests, examples and documentation. To disable these, set the corresponding cache variables before adding the GLFW source tree.
#set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw-3.1.2/)
include_directories(external/glfw-3.1.2/include)


################################################################################
# GLM

include_directories(external/glm-0.9.7.1/) #Using a current compiled version of GLM for this computer, I used this from the OpenGL tutorial	

#The commands bellow arent supported anymore by cmake, so the glm library was downloaded
#manually and included in the project by the command right up.


#find_package(GLM REQUIRED)
#include_directories(${GLM_INCLUDE_DIRS})
#link_directories(${GLM_LIBRARY_DIRS})
#add_definitions(${GLM_DEFINITIONS})

#if(NOT GLM_FOUND)
#        message(Error "GLM not found")
#endif(NOT GLM_FOUND)


################################################################################
# FILES
set(HDRS
    Entities/Entity.hpp
    Entities/Component.hpp
)


set(SRCS
	main.cpp
    Entities/Entity.cpp
    Entities/Component.cpp
)

################################################################################
# EXEC
add_executable(${PROJECT_NAME} ${HDRS} ${SRCS})


# LIBS
set(LIBS
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES} 
    glfw
    ${GLFW_LIBRARIES}
    #${GLUT_LIBRARIES}
    ${GLM_LIBRARIES}
    
)

# LINK
target_link_libraries(${PROJECT_NAME} ${LIBS})


#Install


















