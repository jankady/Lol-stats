#pragma once

void remove_tailing(char* line);

int handle_output_file(char* file_output_path);

int handle_player_names_file(char player_id, FILE* file_player_names);

int start_stats(char* arg1, char* arg2, char* arg3);