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