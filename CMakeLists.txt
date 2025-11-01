cmake_minimum_required(VERSION 4.0)
project(Lol_stats C)

set(CMAKE_C_STANDARD 11)

# Use explicit source files and add header include directory
add_executable(Lol_stats
    main.c
    src/stats.c
    src/utility.c
        src/league_player.c
        header/league_player.h
)

target_include_directories(Lol_stats PRIVATE ${CMAKE_SOURCE_DIR}/header)
