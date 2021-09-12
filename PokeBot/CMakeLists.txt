cmake_minimum_required (VERSION 3.6)
project(example)

add_executable(PokeBot Source.cpp
SleepyHandler/PokeBotClient.h SleepyHandler/PokeBotClient.cpp
Pokemon/PokemonDatabase.h Pokemon/PokemonDatabase.cpp
Map/Generator.h Map/Generator.cpp 
"Users/Server.h" "Users/Server.cpp" 
"Users/User.cpp" "Users/User.h"
Pokemon/Encounter.h Pokemon/Encounter.cpp)


add_subdirectory(deps/sleepy-discord)
target_link_libraries(PokeBot sleepy-discord)
target_link_options(PokeBot PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/FORCE:MULTIPLE>)