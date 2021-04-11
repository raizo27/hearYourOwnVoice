cmake_minimum_required(VERSION 3.10)

project(HearYourOwnVoice)

find_file(libportaudio  NAMES libportaudio.so PATHS ${PROJECT_SOURCE_DIR}/lib/)

set(libbs ${PROJECT_SOURCE_DIR}/lib/libportaudio.so)

message(${libbs})

add_subdirectory(src)
