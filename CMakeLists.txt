cmake_minimum_required(VERSION 3.16)

project(OpenGL_Course
	VERSION 0.1.0
	DESCRIPTION "OpenGL and C++ study project"
	LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 99)

# lets clangd / clang-tidy pick up the flags without a build
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
foreach(config DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config} "${CMAKE_BINARY_DIR}/bin")
endforeach()

# defines the targets glad, glfw, glm, gl2d, imgui, stb_image, stb_truetype and raylib
add_subdirectory(dependencies)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
	glfw
	glad
	glm
	gl2d
	imgui
	stb_image
	stb_truetype)

if (MSVC)
	target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /W3)
	target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
	target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()
