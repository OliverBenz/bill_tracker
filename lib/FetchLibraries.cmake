cmake_minimum_required(VERSION 3.14)

include(FetchContent)

# fmt
# Version 9.1.0
FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG        a33701196adfad74917046096bf5a2aa0ab0bb50
        )

FetchContent_MakeAvailable(fmt)
set_target_properties(fmt PROPERTIES FOLDER "${ideFolderExternal}")


# Nlohmann Json
# Version 3.11.2
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.11.2
        )
FetchContent_MakeAvailable(json)
