cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Project)
enable_language(CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 
set(CMAKE_VERBOSE_MAKEFILE TRUE) 

set(SOURCE_FILES
        src/main.cpp
        include/Alien.h
        include/AlienFactory.h
        include/EntityFactory.h
        include/PlayerFactory.h
        include/ProjectileFactory.h
        include/CollisionDetector.h
        src/CollisionDetector.cpp
        src/AlienFactory.cpp
        include/AlienProjectile.h
        include/PlayerProjectile.h
        src/AlienProjectile.cpp
        src/PlayerProjectile.cpp
        include/PlayerProjectileFactory.h
        include/AlienProjectileFactory.h
        include/ProjectileFactory.h
        src/PlayerProjectileFactory.cpp
        src/ProjectileFactory.cpp
        src/AlienProjectileFactory.cpp
        src/EntityFactory.cpp
        src/PlayerFactory.cpp
        src/ProjectileFactory.cpp
        include/Screen.h
        include/Play.h
        src/Play.cpp
        include/Gamestate.h
        src/Screen.cpp
        src/Gamestate.cpp
        include/Menu.h
        src/Menu.cpp
        include/Bunker.h
        include/Entity.h
        include/Game.h
        include/Gamemanager.h
        include/Player.h
        include/Projectile.h
        src/Alien.cpp
        src/Bunker.cpp
        src/Entity.cpp
        src/Game.cpp
        src/Gamemanager.cpp
        src/Player.cpp
        src/Projectile.cpp
        src/animation.cpp
        include/animation.h
        src/AnimManager.cpp
        include/AnimManager.h
        src/GameOver.cpp
        include/GameOver.h)

add_executable(Project ${SOURCE_FILES})

target_include_directories(Project PUBLIC include)

#SMFL
find_package(SFML 2.4 COMPONENTS graphics window system REQUIRED)
target_link_libraries(Project sfml-graphics sfml-window sfml-system)

#TESTs
find_package (Boost 1.60.0 COMPONENTS unit_test_framework REQUIRED)

# Test source files
set(SOURCE_TEST_FILES
        test/master.cpp
        test/TestEntity.cpp
        test/TestAnimation.cpp
        test/TestGame.cpp
        src/CollisionDetector.cpp
        src/AlienFactory.cpp
        src/AlienProjectile.cpp
        src/PlayerProjectile.cpp
        src/PlayerProjectileFactory.cpp
        src/ProjectileFactory.cpp
        src/AlienProjectileFactory.cpp
        src/EntityFactory.cpp
        src/PlayerFactory.cpp
        src/ProjectileFactory.cpp
        src/Play.cpp
        src/Screen.cpp
        src/Gamestate.cpp
        src/Menu.cpp
        src/Alien.cpp
        src/Bunker.cpp
        src/Entity.cpp
        src/Game.cpp
        src/Gamemanager.cpp
        src/Player.cpp
        src/Projectile.cpp
        src/animation.cpp
        src/AnimManager.cpp
        src/GameOver.cpp
        test/TestGamemanager.cpp
        test/TestCollisionDetector.cpp
        test/TestScreen.cpp

)

add_executable(TestProject ${SOURCE_TEST_FILES})

target_include_directories(TestProject PUBLIC include ${Boost_INCLUDE_DIRS})

target_link_libraries(TestProject
        Boost::unit_test_framework
        sfml-graphics sfml-window sfml-system
)
