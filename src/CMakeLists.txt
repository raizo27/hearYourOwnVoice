add_executable(speaker hearYourOwnVoice.c)
  
target_include_directories(speaker PUBLIC
                            "${PROJECT_SOURCE_DIR}/include")
 
target_link_libraries(speaker PUBLIC ${libportaudio})

add_subdirectory(example)
