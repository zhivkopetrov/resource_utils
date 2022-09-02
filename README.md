# resource_utils

**A static C++ library, which provides auto-generated description for assets**

Supported assets:
- Images
- Fonts
- Sounds


The assets:
- are generated from a command line tool  called "resource_builder".
The tool can be found here - https://github.com/zhivkopetrov/tools
- can easily be imported with this library using the ResourceLoader class 

The library is optimized for fast compilation.


**Usage from plain CMake**
- consume directly with find_package(resource_utils) in a CMakeLists.txt
- Link against your target with suitable access modifier
```
target_link_libraries(
    ${PROJECT_NAME} 
    PUBLIC
        resource_utils::resource_utils
)
```
- Example usage project: https://github.com/zhivkopetrov/dev_battle.git


**Usage as part of ROS(catkin) / ROS2(colcon) meta-build systems**
- consume directly with find_package(utils) in the package CMakeLists.txt
- Link agains your target
- The library automatically exposes ans install it's artifacts following ROS/ROS2 structure
- Example usage project: https://github.com/zhivkopetrov/robotics_v1


**Dependencies**
- cmake_helpers - https://github.com/zhivkopetrov/cmake_helpers.git
- The provided library CMakeLists.txt assumes the helpers.cmake from cmake_helpers repo have already been included
- utils - https://github.com/zhivkopetrov/utils


**Platform support**
- Tested on Unix, Windows
- Never tested on Mac