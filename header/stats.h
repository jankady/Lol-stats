#pragma once
#include "league_player.h"

void remove_tailing(char* line);

int handle_output_file(league_players_array_t* league_players, char* output_file);

int start_stats(const char* arg1, const char* arg2, char* arg3);