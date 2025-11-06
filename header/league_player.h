#pragma once
#include <stdio.h>

typedef struct LeaguePlayer {
    int player_id;
    char player_name[50];
    int kills;
    int assists;
    int deaths;
    int played_as_blue;
    int played_as_red;
    int total_wins;
    int wins_as_blue;
    int wins_as_red;
    int games_played;
    float elo;
} league_player_t;

typedef struct {
    league_player_t* players;
    int count;
    int capacity;
} league_players_array_t;

league_players_array_t* init_league_players(FILE* file_player_names, int max_players);

league_player_t* create_league_player(int player_id, const char* player_name);

void set_kills(league_players_array_t players_array, int player_id, int kills);
int get_kills(league_players_array_t players_array, int player_id);

void set_assists(league_players_array_t players_array, int player_id, int assists);
int get_assists(league_players_array_t players_array, int player_id);

void set_deaths(league_players_array_t players_array, int player_id, int deaths);
int get_deaths(league_players_array_t players_array, int player_id);

void set_played_as_blue(league_players_array_t players_array, int player_id, int played_as_blue);
int get_played_as_blue(league_players_array_t players_array, int player_id);

void set_played_as_red(league_players_array_t players_array, int player_id, int played_as_red);
int get_played_as_red(league_players_array_t players_array, int player_id);

void set_total_wins(league_players_array_t players_array, int player_id, int total_wins);
int get_total_wins(league_players_array_t players_array, int player_id);

void set_wins_as_blue(league_players_array_t players_array, int player_id, int wins_as_blue);
int get_wins_as_blue(league_players_array_t players_array, int player_id);

void set_wins_as_red(league_players_array_t players_array, int player_id, int wins_as_red);
int get_wins_as_red(league_players_array_t players_array, int player_id);

void set_games_played(league_players_array_t players_array, int player_id, int games_played);
int get_games_played(league_players_array_t players_array, int player_id);

void set_elo(league_players_array_t players_array, int player_id, float elo);
int get_elo(league_players_array_t players_array, int player_id);