cmake_minimum_required(VERSION 3.19.2)

project(brrrr VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

# set a path for third-party dir
set(THIRD_PARTY "${CMAKE_CURRENT_SOURCE_DIR}/third_party")

# Add raylib library
add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES IMPORTED_LOCATION "${THIRD_PARTY}/raylib/libraylib.a")

# Your existing code for sources
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${THIRD_PARTY}/Dear-ImGui/*.cpp"
    "${THIRD_PARTY}/rlImGui/*.cpp"
)
add_executable(brrrr "${MY_SOURCES}")

# Your existing code for include directory
target_include_directories(brrrr PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    "${THIRD_PARTY}"
    "${THIRD_PARTY}/raylib/include"
    "${THIRD_PARTY}/raylib-cpp/include"
    "${THIRD_PARTY}/Dear-ImGui"
    "${THIRD_PARTY}/rlImGui"
    "${THIRD_PARTY}/rlImGui/extras"
)

target_compile_definitions(brrrr PUBLIC ASSETS="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
target_link_libraries(brrrr raylib)
