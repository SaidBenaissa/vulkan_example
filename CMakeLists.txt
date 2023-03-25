cmake_minimum_required(VERSION 3.10)

project(vulkan_example)

# Add MoltenVK library
find_library(MOLTENVK_LIB MoltenVK PATHS ${CMAKE_SOURCE_DIR}/external/MoltenVK/MoltenVK.xcframework/MacOS)

# Add GLFW library
find_package(glfw3 REQUIRED)

# Add Vulkan library
find_package(Vulkan REQUIRED)

# Add source files
set(SOURCES main.cpp)

# Create executable
add_executable(vulkan_example ${SOURCES})

# Link libraries
target_link_libraries(vulkan_example ${MOLTENVK_LIB} glfw Vulkan::Vulkan)
