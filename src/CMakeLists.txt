add_executable(game_of_life main.cpp)
add_library(world_library world.cpp)
target_link_libraries(game_of_life world_library)
