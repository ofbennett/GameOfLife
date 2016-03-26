cuda_add_executable(test_GoL test_main.cu test_cases.cu)
target_link_libraries(test_GoL world_library)
