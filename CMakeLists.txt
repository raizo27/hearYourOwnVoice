cmake_minimum_required(VERSION 3.10)

project(HearYourOwnVoice)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/libportaudio.a  DESTINATION lib)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/portaudio.h  DESTINATION include)

find_file(libportaudio  NAMES libportaudio.so PATHS ${PROJECT_SOURCE_DIR}/lib/)

set(libbs ${PROJECT_SOURCE_DIR}/lib/libportaudio.so)

message(${libbs})

add_subdirectory(src)

install(TARGETS example_fuzz DESTINATION bin)
