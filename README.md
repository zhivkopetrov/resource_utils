# resource_utils

## A static C++ library, which provides auto-generated description for assets
The library is optimized for fast compilation.

Supported assets:
- Images
- Sprites
- Fonts
- Sounds (streaming music and sound chunks)

The assets:
- are generated from a command line tool called "resource_builder".
The tool can be found here - https://github.com/zhivkopetrov/tools
- can easily be imported with this library using the ResourceLoader class 

## Usage from plain CMake
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

## Usage as part of ROS1(catkin) / ROS2(colcon) meta-build systems
- consume directly with find_package(resource_utils) in the package CMakeLists.txt
- Link agains your target
- The library automatically exposes ans install it's artifacts following ROS1/ROS2 structure
- Example usage project: https://github.com/zhivkopetrov/robotics_v1

## Dependencies
- cmake_helpers - https://github.com/zhivkopetrov/cmake_helpers.git
- utils - https://github.com/zhivkopetrov/utils

## Supported Platforms
Linux:
  - g++ (9.3 and above)
    - Tested up to g++ 12.1
  - clang++ (10 and above)
    - Tested up to clang++ 14.0
  - Emscripten (3.1.28 and above)
    - emcc/em++
  - Robot Operating System 2 (ROS2)
    - Through colcon meta-build system (CMake based)
  - Robot Operating System 1 (ROS1)
    - Through catkin meta-build system (CMake based)
      - Due to soon ROS1 end-of-life catkin builds are not actively supported

Windows:
  - MSVC++ (14.20 and above) Visual Studio 2019
    - Tested up to 17.30 Visual Studio 2022
  - Emscripten (3.1.28 and above)
    - emcc/em++
    - NOTE: non-MSVC CMake build generator is needed
      - For example: ninja
  - ROS1/ROS2
    - Although the code is ROS compatible, actual ROS functionalities have not been tested on Windows