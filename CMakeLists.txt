# CMakeList.txt : CMake project for KlemmUITemplate, include source and define
# project specific logic here.
#

# Name of the project/executable
set(TARGET_NAME "KlemmUITemplate")
# C++ source code directory
set(SOURCE_DIR "src/")
# UI sheet directory
set(MARKUP_DIR "ui/")
# Directory where the generated UI headers should be placed
set(MARKUP_HEADER_DIR "${SOURCE_DIR}/ui")
# Directory where the shader files will be placed
set(APP_SHADER_DIR "app/shaders")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(${TARGET_NAME})

file(
	GLOB_RECURSE
	SOURCE_FILES
	"${SOURCE_DIR}/**.cpp"
)

# Add source to this project's executable.
add_executable(${TARGET_NAME} ${SOURCE_FILES})

# On Windows, release builds shouldn't have a console.
# Debug builds will have one. Remove this condition if you don't want this behavior.
if (WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
	target_link_options(${TARGET_NAME} PRIVATE "/Subsystem:Windows")
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 20)
endif()

add_subdirectory("dependencies/KlemmUI/" "deps/KlemmUI")

target_link_libraries(${TARGET_NAME} PRIVATE KlemmUI)

# Parse UI files and generate C++ headers for them.
# Ninja doesn't re-check dependencies after running the command, so it has to be run twice.
add_subdirectory("dependencies/KlemmUI/Markup" "deps/bin")

add_custom_target(
	WriteHeaders
	COMMENT "Running build command."
)

add_custom_command(
	TARGET WriteHeaders
	COMMAND $<TARGET_FILE:KlemmUIHT> -i ${CMAKE_SOURCE_DIR}/${MARKUP_DIR} -o ${CMAKE_SOURCE_DIR}/${MARKUP_HEADER_DIR}
)

add_dependencies(WriteHeaders KlemmUIHT)
add_dependencies(${TARGET_NAME} WriteHeaders)

# Copy KlemmUI shader files into the app dir
add_custom_command(
	TARGET ${TARGET_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/dependencies/KlemmUI/Shaders ${CMAKE_SOURCE_DIR}/${APP_SHADER_DIR}
)
