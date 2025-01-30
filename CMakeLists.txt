cmake_minimum_required(VERSION 3.4)

#Configuration parameters of cmake
set(CMAKE_CXX_COMPILER g++)#requires g++ to be available on PATH
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Project)
enable_language(CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 
set(CMAKE_VERBOSE_MAKEFILE TRUE) 

#Source files here
set(SOURCE_FILES
        include/Alien.h
        include/Bunker.h
        include/Entity.h
        include/Filemanager.h
        include/Game.h
        include/Gamemanager.h
        include/Player.h
        include/Projectile.h
        src/Alien.cpp
        src/Bunker.cpp
        src/Entity.cpp
        src/Filemanager.cpp
        src/Game.cpp
        src/Gamemanager.cpp
        src/Player.cpp
        src/Projectile.cpp
        src/main.cpp
        src/animation.cpp
        include/animation.h
        src/AnimManager.cpp
        include/AnimManager.h
        src/Brick.cpp
        include/Brick.h)

add_executable(Project ${SOURCE_FILES})

target_include_directories(Project PUBLIC include)

#SMFL
find_package(SFML 2.4 COMPONENTS graphics window system REQUIRED)
target_link_libraries(Project sfml-graphics sfml-window sfml-system)

#TESTs
find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

#Test source files here
set(SOURCE_TEST_FILES
        test/master.cpp)

add_executable(TestProject ${SOURCE_TEST_FILES})

target_include_directories(TestProject PUBLIC include)

target_link_libraries (TestProject
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

enable_testing()

add_test(NAME Test COMMAND TestProject
        --report_level=detailed
        --log_level=all
        --color_output=yes)

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})