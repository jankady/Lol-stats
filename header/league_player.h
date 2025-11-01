#pragma once

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