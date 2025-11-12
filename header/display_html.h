#pragma once

#include "league_player.h"

void display_header(char* output_file);

void display_chart(char* output_file, league_players_array_t* league_players);

void display_footer(char* output_file);

void display_site(char* output_file, league_players_array_t* league_players);
