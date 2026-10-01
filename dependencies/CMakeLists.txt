# Every target defined here is a plain CMake target name, so src/*.cpp can just do:
#
#   target_link_libraries(my_target PRIVATE glfw glad glm gl2d imgui stb_image stb_truetype)
#
# Only the upstream projects that ship their own CMakeLists.txt are pulled in with
# add_subdirectory() (glfw, glm, gl2d). Everything else is wired up by hand so the
# vendored folders stay byte-identical to their upstream checkout.

# gl2d still declares cmake_minimum_required(VERSION 3.1), which CMake >= 4 rejects.
# This is the documented escape hatch that keeps its policies at the old defaults.
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# --------------------------------------------------------------------------------------
# gl2d - 2D renderer built on OpenGL.
# Pulled in after glm/glad/stb_* below, because its CMakeLists.txt links them by name.
# --------------------------------------------------------------------------------------
add_subdirectory(gl2d/gl2d)

# --------------------------------------------------------------------------------------
# glad - OpenGL extension loader, generated for core profile 4.3.
# 4.3 is the minimum core profile that provides GL_DEBUG_OUTPUT / glDebugMessageCallback,
# which include/openglErrorReporting.h needs. src/main.cpp still asks GLFW for a 3.3
# core context, which is fine: the driver exposes the debug output entry points
# regardless of the context version.
# --------------------------------------------------------------------------------------
add_library(glad STATIC "${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c")
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/glad/include")
target_compile_definitions(glad PRIVATE GLAD_GLAPI_EXPORT=)

# --------------------------------------------------------------------------------------
# glfw - window and context creation. Builds both X11 and Wayland back ends.
# --------------------------------------------------------------------------------------
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS   OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS    OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL       OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11     ON  CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND ON  CACHE BOOL "" FORCE)
add_subdirectory(glfw)

# --------------------------------------------------------------------------------------
# glm - header only math library.
# --------------------------------------------------------------------------------------
set(GLM_BUILD_LIBRARY OFF CACHE BOOL "" FORCE)
set(GLM_BUILD_TESTS   OFF CACHE BOOL "" FORCE)
set(GLM_BUILD_INSTALL OFF CACHE BOOL "" FORCE)
set(GLM_ENABLE_CXX_17 ON  CACHE BOOL "" FORCE)
add_subdirectory(glm)

# --------------------------------------------------------------------------------------
# stb_image / stb_truetype - single header libraries from nothings/stb.
# Option A links a prebuilt static library, Option B hands you the headers only and you
# provide the implementation yourself with the usual STB_*_IMPLEMENTATION define.
# Either way both targets expose <stb_image.h> and <stb_image/stb_image.h>.
# --------------------------------------------------------------------------------------
set(STB_PRECOMPILED_IMPLEMENTATION
	ON
	CACHE BOOL "Compile the stb implementation into the stb_image/stb_truetype libraries")

if (STB_PRECOMPILED_IMPLEMENTATION)
	add_library(stb_image STATIC "${CMAKE_CURRENT_SOURCE_DIR}/glue/src/stb_image.cpp")
	add_library(stb_truetype STATIC "${CMAKE_CURRENT_SOURCE_DIR}/glue/src/stb_truetype.cpp")
else()
	add_library(stb_image INTERFACE)
	add_library(stb_truetype INTERFACE)
endif()

foreach(stb_target stb_image stb_truetype)
	target_include_directories(${stb_target} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/stb")
	# makes the <stb_image/stb_image.h> spelling that gl2d uses resolve
	target_include_directories(${stb_target} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/glue/compat")
endforeach()

# --------------------------------------------------------------------------------------
# imgui - Dear ImGui, docking branch, with the GLFW and OpenGL3 back ends.
# Add imgui/imgui_demo.cpp to the list below if you want ImGui::ShowDemoWindow().
# --------------------------------------------------------------------------------------
add_library(imgui STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp")

target_include_directories(imgui PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/imgui"
	"${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends")

# imgui_impl_glfw.cpp includes <GLFW/glfw3.h>
target_link_libraries(imgui PRIVATE glfw)

# --------------------------------------------------------------------------------------
# raylib - built as a standalone CMake project, NOT as a subdirectory.
#
# raylib bundles its own GLFW and creates a target literally named "glfw" when it cannot
# find a system one (raylib/cmake/GlfwImport.cmake). Adding it with add_subdirectory()
# next to the real GLFW above would be a duplicate target and fail at configure time.
# So `cmake --build <build> --target raylib` configures and installs it on its own into
# dependencies/raylib/out, and the targets below point at that install.
#
# It is deliberately not linked into the course executable: raylib owns the window, the
# GL context and its own GLFW, so combining it with the GLFW + imgui path above means
# two GL loaders and two GLFW copies in one binary.
# --------------------------------------------------------------------------------------
set(RAYLIB_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/raylib")
set(RAYLIB_BUILD_DIR  "${RAYLIB_SOURCE_DIR}/build")
set(RAYLIB_OUT_DIR    "${RAYLIB_SOURCE_DIR}/out")

find_library(RAYLIB_LIBRARY
	NAMES raylib
	PATHS "${RAYLIB_OUT_DIR}/lib"
	NO_DEFAULT_PATH)

find_path(RAYLIB_INCLUDE_DIR
	NAMES raylib.h
	PATHS "${RAYLIB_OUT_DIR}/include"
	NO_DEFAULT_PATH)

add_library(raylib INTERFACE)
add_library(raylib_static ALIAS raylib)

if (RAYLIB_LIBRARY AND RAYLIB_INCLUDE_DIR)
	target_include_directories(raylib INTERFACE "${RAYLIB_INCLUDE_DIR}")
	target_link_libraries(raylib INTERFACE "${RAYLIB_LIBRARY}")
	message(STATUS "raylib: using prebuilt ${RAYLIB_LIBRARY}")
else()
	message(STATUS "raylib: not built yet, run `cmake --build <build-dir> --target raylib_build`.")
endif()

add_custom_target(raylib_build
	COMMAND "${CMAKE_COMMAND}" -S "${RAYLIB_SOURCE_DIR}" -B "${RAYLIB_BUILD_DIR}"
		-DCMAKE_BUILD_TYPE=$<IF:$<BOOL:${CMAKE_BUILD_TYPE}>,${CMAKE_BUILD_TYPE},Release>
		-DCMAKE_INSTALL_PREFIX=${RAYLIB_OUT_DIR}
		-DCMAKE_INSTALL_LIBDIR=lib
		-DBUILD_EXAMPLES=OFF
		-DBUILD_SHARED_LIBS=OFF
	COMMAND "${CMAKE_COMMAND}" --build "${RAYLIB_BUILD_DIR}" --target install
	USES_TERMINAL
	COMMENT "Configuring and installing raylib into dependencies/raylib/out")
