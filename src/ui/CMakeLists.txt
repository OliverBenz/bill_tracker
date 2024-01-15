# ----- External Libraries -----
find_package(Qt6 REQUIRED COMPONENTS Gui Widgets Charts)

set(CMAKE_AUTOMOC ON) # Qt6 Settings
set(CMAKE_AUTORCC ON) # Qt6 Settings
set(CMAKE_AUTOUIC ON) # Qt6 Settings


# ----- Setup project -----
set(targetName "billTrackerUi")

set(headers
    ${CMAKE_CURRENT_LIST_DIR}/application.hpp
    ${CMAKE_CURRENT_LIST_DIR}/aboutDialog.hpp
    ${CMAKE_CURRENT_LIST_DIR}/toolBar.hpp

    ${CMAKE_CURRENT_LIST_DIR}/views/addBillView.hpp
    ${CMAKE_CURRENT_LIST_DIR}/views/billTableView.hpp
    ${CMAKE_CURRENT_LIST_DIR}/views/settingsView.hpp

    ${CMAKE_CURRENT_LIST_DIR}/models/addBillModel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/models/billTableModel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/models/settingsModel.hpp
)

set(sources
    ${CMAKE_CURRENT_LIST_DIR}/application.cpp
    ${CMAKE_CURRENT_LIST_DIR}/aboutDialog.cpp
    ${CMAKE_CURRENT_LIST_DIR}/toolBar.cpp

    ${CMAKE_CURRENT_LIST_DIR}/views/addBillView.cpp
    ${CMAKE_CURRENT_LIST_DIR}/views/billTableView.cpp
    ${CMAKE_CURRENT_LIST_DIR}/views/settingsView.cpp

    ${CMAKE_CURRENT_LIST_DIR}/models/addBillModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/models/billTableModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/models/settingsModel.cpp
)

add_library(${targetName} STATIC ${headers} ${sources})


# Link to thread module for maths functions.
target_link_libraries(${targetName} PRIVATE billTrackerLib Qt6::Gui Qt6::Widgets Qt6::Charts)
target_include_directories(${targetName} PRIVATE "${CMAKE_SOURCE_DIR}/src")
set_target_properties(${targetName} PROPERTIES FOLDER "${ideFolderSource}")

# Setup project settings
set_project_warnings(${targetName})  # Which warnings to enable
set_compile_options(${targetName})   # Which extra compiler flags to enable
set_output_directory(${targetName})  # Set the output directory of the library

# Copy header files to output after build
# copy_headers_to_output(${targetName} "${headers}")

# Specify version
target_compile_definitions(${targetName} PUBLIC VERSION_MAJOR=0)
target_compile_definitions(${targetName} PUBLIC VERSION_MINOR=0)
target_compile_definitions(${targetName} PUBLIC VERSION_PATCH=1)

# System installation
# install(TARGETS ${targetName} DESTINATION lib)
# install(FILES ${headers} DESTINATION include/!!Target!!)
