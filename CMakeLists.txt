cmake_minimum_required(VERSION 3.16)
project(Lol_stats C)

set(CMAKE_C_STANDARD 11)

# Sorce files
add_executable(Lol_stats
        main.c
        src/stats.c
        src/utility.c
        src/league_player.c
        src/display_html.c
)

target_include_directories(Lol_stats PRIVATE ${CMAKE_SOURCE_DIR}/header)
