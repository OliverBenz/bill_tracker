cmake_minimum_required(VERSION 3.11)
include(FetchContent)

# nlohmann json
message(STATUS "Fetching nlohmann json from github.")
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.10.5
    )
FetchContent_MakeAvailable(json)