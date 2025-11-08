#include "../header/league_player.h"
#include "../header/utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER_SIZE 256

league_player_t *create_league_player(int player_id, const char *player_name) {
    league_player_t *player = malloc(sizeof(league_player_t));
    if (!player) {
        fprintf(stderr, "Chyba alokace pameti pro league_player_t\n");
        return NULL;
    }
    player->player_id = player_id;
    strncpy(player->player_name, player_name, sizeof(player->player_name) - 1);
    player->player_name[sizeof(player->player_name) - 1] = '\0'; // make sure string is ended with \0
    player->kills = 0;
    player->assists = 0;
    player->deaths = 0;
    player->played_as_blue = 0;
    player->played_as_red = 0;
    player->total_wins = 0;
    player->wins_as_blue = 0;
    player->wins_as_red = 0;
    player->games_played = 0;
    player->elo = 1000.0f; // Initial ELO rating
    return player;
}

league_players_array_t* init_league_players(FILE* file_player_names, const int max_players) {
    league_player_t* players_arr = malloc(max_players * sizeof(league_player_t));
    if (!players_arr) {
        fprintf(stderr, "Chyba alokace pameti pro init_league_players\n");
        return NULL;
    }
    char* buffer = malloc(MAX_BUFFER_SIZE * sizeof(char));
    if (!buffer) {
        free(players_arr);
        fprintf(stderr, "Chyba alokace pameti pro init_league_players buffer\n");
        return NULL;
    }
    int player_count = 0;
    while (fgets(buffer, MAX_BUFFER_SIZE, file_player_names) && player_count < max_players) {
        char* player_id = strtok(buffer, ",");
        char* player_name = strtok(NULL, "\n");

        league_player_t* new_player = create_league_player(atoi(player_id), player_name);
        if (!new_player) {
            free(buffer);
            free(players_arr);
            return NULL;
        }
        players_arr[player_count] = *new_player;
        free(new_player);
        player_count++;
    }
    league_players_array_t *league_players = malloc(sizeof(league_players_array_t));
    league_players->players = players_arr;
    league_players->count = player_count;
    league_players->capacity = max_players;
    free(buffer);
    return league_players;
}

int id_exists(league_players_array_t* players_array, int player_id) {
    for (int i = 0; i < players_array->count; i++) {
        if (players_array->players[i].player_id == player_id) {
            return 0;
        }
    }
    return 1;
}


void set_kills(league_players_array_t* players_array, int player_id, int kills) {

    for (int i = 0; i < players_array->count; i++) {
        if (players_array->players[i].player_id == player_id) {
            players_array->players[i].kills = kills;
            return;
        }
    }
}
int get_kills(league_players_array_t* players_array, int player_id) {

    for (int i = 0; i < players_array->count; i++) {
        if (players_array->players[i].player_id == player_id) {
            return players_array->players[i].kills;
        }
    }
    return -1;
}


void set_assists(league_players_array_t* players_array, int player_id, int assists);

void set_deaths(league_players_array_t* players_array, int player_id, int deaths);

void set_played_as_blue(league_players_array_t* players_array, int player_id, int played_as_blue);

void set_played_as_red(league_players_array_t* players_array, int player_id, int played_as_red);

void set_total_wins(league_players_array_t* players_array, int player_id, int total_wins);

void set_wins_as_blue(league_players_array_t* players_array, int player_id, int wins_as_blue);

void set_wins_as_red(league_players_array_t* players_array, int player_id, int wins_as_red);

void set_games_played(league_players_array_t* players_array, int player_id, int games_played);