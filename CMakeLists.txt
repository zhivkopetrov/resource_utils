#Author Zhivko Petrov

cmake_minimum_required(VERSION 3.10.2)

if(TARGET resource_utils)
    return()
endif()

if(NOT CMAKE_HELPERS_INCLUDED)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers.cmake)
endif()

project(resource_utils)
   
set(_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/resource_utils")

add_library(
    ${PROJECT_NAME} 
    STATIC
        "${_SRC_DIR}/common/ResourceFileHeader.cpp"
        "${_SRC_DIR}/defines/SoundDefines.cpp"
        "${_SRC_DIR}/resource_loader/ResourceLoader.cpp"
        "${_SRC_DIR}/structs/CombinedStructs.cpp"
        "${_SRC_DIR}/structs/DataHeader.cpp"
        "${_SRC_DIR}/structs/ResourceData.cpp"
        "${_SRC_DIR}/structs/FontData.cpp"
        "${_SRC_DIR}/structs/SoundData.cpp"
)

set_target_cpp_standard(${PROJECT_NAME} 17)
enable_target_warnings(${PROJECT_NAME})
set_target_visibility(${PROJECT_NAME})

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        VERSION 1.0.0
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(NOT TARGET utils)
    add_subdirectory(utils)
endif()

#Linker dependacies
target_link_libraries(
    ${PROJECT_NAME} 
    PUBLIC
        utils   # -lutils.a
)
        
#invoke include-what-you-use (if it's enabled) for the current project
if(USE_IWYU)
    enable_target_include_what_you_use(${PROJECT_NAME})
endif(USE_IWYU)
                      
if(BUILD_LIKE_POSITION_INDEPENDANT_CODE)
    enable_target_position_independent_code(${PROJECT_NAME})
endif()  



