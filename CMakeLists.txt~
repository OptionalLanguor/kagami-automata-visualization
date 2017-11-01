#################################################
# Projeto Kagami - Automata Visualization
#################################################

project(Kagami)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_PREFIX_PATH "/home/aluno/Kagami/kagami-automata-visualization")

if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
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
SET(PROJECT_SOURCE_DIR 				${PROJECT_NAME})


################################################################################
# External - Compile external dependencies

add_subdirectory (external)

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

#find_package(GLEW REQUIRED)
#include_directories(${GLEW_INCLUDE_DIRS})
#add_definitions(${GLEW_DEFINITIONS})

#if(GLEW_FOUND)
#		include_directories(${GLEW_INCLUDE_DIRS})
#    	link_libraries(${GLEW_LIBRARIES})
#    	add_definitions(${GLEW_DEFINITIONS})
#endif(GLEW_FOUND)
#if(NOT GLEW_FOUND)
#		message(Error "GLEW not found")
#endif(NOT GLEW_FOUND)

#add_subdirectory(external/glew-1.13.0/)
include_directories(external/glew-1.13.0/include/)


################################################################################
# GLFW

#When including GLFW as part of your build, you probably don't want to build the GLFW tests, examples and documentation. To disable these, set the corresponding cache variables before adding the GLFW source tree.
#set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#add_subdirectory(external/glfw-3.1.2/)
include_directories(external/glfw-3.1.2/include/GLFW)


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
# PROJECT FOLDERS DIRECTORIES

include_directories(Entities)
include_directories(common)


################################################################################


# FILES
set(HDRS
	Entities/Engine.hpp
    Entities/Entity.hpp
    Entities/Component.hpp
    Entities/System.hpp
    Entities/RendererSystem.hpp
    Entities/RenderableComponent.hpp
    common/shader.hpp
    common/texture.hpp
    common/controls.hpp
    common/objloader.hpp
)

set(SRCS
	main.cpp
	Entities/Engine.cpp
    Entities/Entity.cpp
    Entities/Component.cpp
    Entities/System.cpp
    Entities/RendererSystem.cpp
	common/shader.cpp
    common/texture.cpp
    common/controls.cpp
    common/objloader.cpp
)

set(SHADERS
	TransformVertexShader.vertexshader
	TextureFragmentShader.fragmentshader
)

################################################################################
# Definitions
add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)


# EXEC
add_executable(${PROJECT_NAME} ${HDRS} ${SRCS} ${SHADERS})


# LIBS
set(LIBS
    ${OPENGL_LIBRARIES}
    #${GLEW_LIBRARIES} 
    glfw
    GLEW_1130
    #${GLFW_LIBRARIES}
    #${GLUT_LIBRARIES}
    ${GLM_LIBRARIES}
    
)

# LINK
target_link_libraries(${PROJECT_NAME} ${LIBS})

# Xcode and Visual working directories
set_target_properties(${PROJECT_NAME} PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/")

#Install

SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )

