#Author Zhivko Petrov

cmake_minimum_required(VERSION 3.10.2)

project(
    resource_utils
    LANGUAGES CXX
    VERSION 1.0.0
)

find_package(utils REQUIRED)
   
set(_INC_FOLDER_NAME include)
set(_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${_INC_FOLDER_NAME}/${PROJECT_NAME})
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(
    ${PROJECT_NAME} 
    STATIC
        ${_INC_DIR}/common/ResourceFileHeader.h
        ${_INC_DIR}/defines/ResourceDefines.h
        ${_INC_DIR}/defines/SoundDefines.h
        ${_INC_DIR}/resource_loader/ResourceLoader.h
        ${_INC_DIR}/structs/CombinedStructs.h
        ${_INC_DIR}/structs/DataHeader.h
        ${_INC_DIR}/structs/FontData.h
        ${_INC_DIR}/structs/ResourceData.h
        ${_INC_DIR}/structs/SoundData.h
        
        ${_SRC_DIR}/common/ResourceFileHeader.cpp
        ${_SRC_DIR}/defines/SoundDefines.cpp
        ${_SRC_DIR}/resource_loader/ResourceLoader.cpp
        ${_SRC_DIR}/structs/CombinedStructs.cpp
        ${_SRC_DIR}/structs/DataHeader.cpp
        ${_SRC_DIR}/structs/ResourceData.cpp
        ${_SRC_DIR}/structs/FontData.cpp
        ${_SRC_DIR}/structs/SoundData.cpp
)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${_INC_FOLDER_NAME}>
        $<INSTALL_INTERFACE:${_INC_FOLDER_NAME}>
)

target_link_libraries(
    ${PROJECT_NAME} 
    PUBLIC
        utils::utils
)

set_target_cpp_standard(${PROJECT_NAME} 20)
enable_target_warnings(${PROJECT_NAME})
set_target_visibility(${PROJECT_NAME})
install_and_export_target(${PROJECT_NAME} ${_INC_FOLDER_NAME})

if(NOT DISABLE_ROS_TOOLING)
    enable_ros_tooling_for_target(
        ${PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/package.xml
    )
endif()

#invoke include-what-you-use (if it's enabled) for the current project
if(USE_IWYU)
    enable_target_include_what_you_use(${PROJECT_NAME})
endif(USE_IWYU)
                      
if(BUILD_LIKE_POSITION_INDEPENDANT_CODE)
    enable_target_position_independent_code(${PROJECT_NAME})
endif()  
