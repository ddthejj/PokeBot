cmake_minimum_required (VERSION 3.6)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")
project(PokeBot_Proj)


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
  "Pokemon/PokemonInstance.h" "Pokemon/PokemonInstance.cpp"  
  "Map/Region.h" "Map/Region.cpp"
  "Map/Area.h" "Map/Area.cpp"
  )

add_subdirectory(deps/sleepy-discord)
target_link_libraries(PokeBot sleepy-discord)
target_link_options(PokeBot PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/FORCE:MULTIPLE>)
