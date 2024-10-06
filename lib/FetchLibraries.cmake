cmake_minimum_required(VERSION 3.14)

include(FetchContent)

# Nlohmann Json
# Version 3.11.2
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.11.2
        )
FetchContent_MakeAvailable(json)
