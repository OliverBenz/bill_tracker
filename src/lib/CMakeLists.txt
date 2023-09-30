set(targetName "billTrackerLib")

# Sources
set(headers 
    ${CMAKE_CURRENT_LIST_DIR}/bill.hpp 
    ${CMAKE_CURRENT_LIST_DIR}/shop.hpp 
    ${CMAKE_CURRENT_LIST_DIR}/file.hpp 
    ${CMAKE_CURRENT_LIST_DIR}/dateHandler.hpp 
    ${CMAKE_CURRENT_LIST_DIR}/dataHandler.hpp 
    ${CMAKE_CURRENT_LIST_DIR}/IDataAccessHandler.hpp 
    ${CMAKE_CURRENT_LIST_DIR}/fileAccessHandler.hpp
)
set(sources 
    ${CMAKE_CURRENT_LIST_DIR}/dateHandler.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/dataHandler.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/fileAccessHandler.cpp
)

add_library(${targetName} STATIC ${headers} ${sources})

# Linking
target_link_libraries(${targetName} nlohmann_json::nlohmann_json fmt::fmt)
set_target_properties(${targetName} PROPERTIES FOLDER "${ideFolderSource}")

# Setup project settings
set_project_warnings(${targetName})  # Which warnings to enable
set_compile_options(${targetName})   # Which extra compiler flags to enable
set_output_directory(${targetName})  # Set the output directory of the library

target_compile_definitions(${targetName} PRIVATE RESOURCE_PATH_SETTINGS="${CMAKE_SOURCE_DIR}/resources/settings.json")
