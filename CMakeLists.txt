cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(test VERSION 0.1.0 LANGUAGES CXX)

# Sources
file(GLOB_RECURSE sources src/*.[hc]pp)

# Executable
add_executable(${PROJECT_NAME} ${sources})
target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Dependencies
find_package(benchmark CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE benchmark::benchmark_main)

find_package(Boost 1.73.0 CONFIG REQUIRED COMPONENTS headers regex)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::headers Boost::regex)

find_package(re2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE re2::re2)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
