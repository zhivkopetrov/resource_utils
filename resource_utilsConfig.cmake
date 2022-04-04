include(CMakeFindDependencyMacro)

#find_dependency will correctly forward REQUIRED or QUIET args to the consumer
#find_package is only for internal use
find_dependency(cmake_helpers REQUIRED)
find_dependency(utils REQUIRED)

if(NOT TARGET resource_utils::resource_utils)
  include(${CMAKE_CURRENT_LIST_DIR}/resource_utilsTargets.cmake)
endif()

# This is for catkin compatibility.
set(resource_utils_LIBRARIES resource_utils::resource_utils)

get_target_property(
    resource_utils_INCLUDE_DIRS
    resource_utils::resource_utils
    INTERFACE_INCLUDE_DIRECTORIES
)

