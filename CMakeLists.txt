cmake_minimum_required(VERSION 3.12)

project(bill_tracker)
set(CMAKE_CXX_STANDARD 20)

option(BUILD_TESTS "Create the unit tests for the project." True)
option(BUILD_EXAMPLES "Create examples for the project." True)


# Add libraries to project
add_subdirectory(lib)

# Add project components
add_subdirectory(src/lib)
add_subdirectory(src/ui)
add_subdirectory(src/app)
