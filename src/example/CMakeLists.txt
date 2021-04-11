add_executable(example_fuzz pa_fuzz.c)

target_include_directories(example_fuzz PUBLIC
                           "${PROJECT_SOURCE_DIR}/include"
                           )

target_link_libraries(example_fuzz PUBLIC ${libportaudio})
