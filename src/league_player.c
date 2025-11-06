#include "../header/league_player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

league_player_t *create_league_player(int player_id, const char *player_name) {
    league_player_t *player = (league_player_t *) malloc(sizeof(league_player_t));
    if (!player) {
        fprintf(stderr, "Chyba alokace pameti pro league_player_t\n");
        return NULL;
    }
    player->player_id = player_id;
    strncpy(player->player_name, player_name, sizeof(player->player_name) - 1);
    player->player_name[sizeof(player->player_name) - 1] = '\0'; // Ensure null-termination
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
