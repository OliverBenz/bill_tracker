set(libTargetName billTrackerLib)

# Sources
set(libHeaders bill.hpp shop.hpp file.hpp dateHandler.hpp dataHandler.hpp IDataAccessHandler.hpp fileAccessHandler.hpp)
set(libSources dateHandler.cpp dataHandler.cpp fileAccessHandler.cpp)

add_library(${libTargetName} STATIC ${libHeaders} ${libSources})

# Linking
target_link_libraries(${libTargetName} nlohmann_json::nlohmann_json fmt::fmt)
set_target_properties(${libTargetName} PROPERTIES FOLDER "${ideFolderSource}")

# Setup project settings
set_project_warnings(${libTargetName})  # Which warnings to enable
set_compile_options(${libTargetName})   # Which extra compiler flags to enable
set_output_directory(${libTargetName})  # Set the output directory of the library

target_compile_definitions(${libTargetName} PRIVATE RESOURCE_PATH_SETTINGS="${CMAKE_SOURCE_DIR}/resources/settings.json")