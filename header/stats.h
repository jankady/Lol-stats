#pragma once
#include "league_player.h"

void remove_tailing(char* line);

int handle_output_file(char* file_output_path);

int handle_player_names_file(int player_id, const league_players_array_t* players_array);

int start_stats(const char* arg1, const char* arg2, char* arg3);