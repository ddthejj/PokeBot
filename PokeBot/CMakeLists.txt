cmake_minimum_required (VERSION 3.6)
project(example)

add_executable(PokeBot Source.cpp
SleepyHandler/PokeBotClient.h SleepyHandler/PokeBotClient.cpp
Pokemon/PokemonDatabase.h Pokemon/PokemonDatabase.cpp
Map/Generator.h Map/Generator.cpp 
Users/Server.h Users/Server.cpp
Users/User.cpp Users/User.h
Event/Event.h Event/Event.cpp
Event/Encounter.h Event/Encounter.cpp 
 Event/Release.h Event/Release.cpp 
 "Pokemon/Evolution.h" "Pokemon/Evolution.cpp"
  "Pokemon/PokemonInstance.h" "Pokemon/PokemonInstance.cpp"  "Map/Region.h" "Map/Area.h")


add_subdirectory(deps/sleepy-discord)
target_link_libraries(PokeBot sleepy-discord)
target_link_options(PokeBot PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/FORCE:MULTIPLE>)

option(WITH_VLD "With Visual Leak Detection" OFF)
if(WITH_VLD AND MSVC)
  message("Enabling Visual Leak Detector")
  find_library(VLD vld
    HINTS "deps/")
  find_file(VLD_H vld.h
    HINTS "c:/Program Files (x86)/Visual Leak Detector/include" "c:/Program Files/Visual Leak Detector/include")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FIwinsock2.h")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \"/FI${VLD_H}\"")
  get_filename_component(VLD_LIBRARY_DIR "${VLD}" PATH)
  link_directories("${VLD_LIBRARY_DIR}")
endif()