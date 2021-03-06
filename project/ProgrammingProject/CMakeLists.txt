# Add as a subdirectory SimpleRenderEngineProject using add_subdirectory
IF (NOT DEFINED all_libs)
    message( FATAL_ERROR "This CMakeLists.txt must be included using the command add_subdirectory(name)" )
ENDIF (NOT DEFINED all_libs)
# Ensure SimpleRenderEngineProject is up-to-date
IF (WIN32)
    IF (NOT DEFINED DLLFileList)
        message( FATAL_ERROR "The SimpleRenderEngineProject has been updated. Clone the project (https://github.com/mortennobel/SimpleRenderEngineProject) again the project again and start over." )
    ENDIF(NOT DEFINED DLLFileList)
ENDIF(WIN32)

# Add hpp and cpp files to Snake variable
file(GLOB Scroller
        "*.hpp"
        "*.h"
        "*.cpp"
        )

# Compile cpp files (from Snake variable)
add_executable(Exercise9-scroller ${Scroller})
target_link_libraries(Exercise9-scroller ${all_libs})

# copy files to dest
file(COPY scroller.json scroller.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY scroller.json scroller.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)

IF (WIN32)
    # Copy dll files to ${CMAKE_CURRENT_BINARY_DIR}/Debug
    file(COPY ${DLLFileList} DESTINATION Debug)
    file(COPY ${DLLFileList} DESTINATION Release)

    # Set working directory to ${CMAKE_CURRENT_BINARY_DIR}/Debug
    set_target_properties(Exercise9-scroller PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Debug)
ENDIF(WIN32)
