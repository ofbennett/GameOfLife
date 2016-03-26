cuda_add_executable(game_of_life main.cu)
cuda_add_library(world_library World.cu)
target_link_libraries(game_of_life world_library)
