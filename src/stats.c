#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/stats.h"
#include "../header/league_player.h"
#include "../header/utility.h"

#define MAX_PLAYERS_NUM 20
#define MAX_BUFFER_SIZE 256

void remove_tailing(char *line) {
    if (!line) return;
    line[strcspn(line, "\r\n")] = '\0'; // odstrani \n a \r z konce retezce
}

int handle_output_file(char *file_output_path) {
    //add later
    return 0;
}

int handle_player_names_file(int player_id, const league_players_array_t *players_array) {

    for (int i = 0; i < players_array->count; i++) {
        if (players_array->players[i].player_id == player_id) {
            return 0;
        }
    }

    return 1;
}

int player_exist(char *buffer, league_players_array_t *players_array) {
    remove_tailing(buffer);
    for (int i = 0; i < 3; i++) {
        if ((unsigned long) i * 2 >= strlen(buffer) || strlen(buffer) != 5) {
            fprintf(stderr, "Chyba formatu souboru: ocekavano 'id,id,id', nalezeno '%s'\n", buffer);
            return 1;
        }
        int player_id = buffer[i * 2] - '0'; // convert char to int i subsctract asci values
        if (handle_player_names_file(player_id, players_array) != 0) {
            fprintf(stderr, "Hrac s ID '%c' nebyl nalezen v souboru hracu\n", player_id);

            return 1;
        }
    }
    return 0;
}

int check_word(char *buffer, const char *expected_word) {
    remove_tailing(buffer);
    if (strcmp(expected_word, "match") == 0) {
        if (strcmp(buffer, "match") != 0) {
            fprintf(stderr, "Chyba formatu souboru: ocekavano 'match', nalezeno '%s'\n", buffer);
            return 1;
        }
    } else if (strcmp(expected_word, "winner_team") == 0) {
        if (strcmp(buffer, "red") != 0 && strcmp(buffer, "blue") != 0) {
            fprintf(stderr, "Chyba formatu souboru: ocekavano 'blue' nebo 'red', nalezeno '%s'\n", buffer);
            return 1;
        }
    } else {
        fprintf(stderr, "Chyba formatu souboru nalezeno neplatne slovo: '%s'\n", buffer);
        return 1;
    }

    return 0;
}

int start_stats(const char *file_match_path, const char *file_player_names_path, char *file_output_path) {
    FILE *file_match = read_file(file_match_path);
    FILE *file_player_names = read_file(file_player_names_path);
    if (file_match == NULL || file_player_names == NULL) {
        if (file_match)
            close_file(file_match);
        if (file_player_names)
            close_file(file_player_names);
        return 1;
    }
    clear_file(file_output_path);
    printf("zacinam\n");
    int buffer_size = MAX_BUFFER_SIZE;
    char *buffer = malloc(MAX_BUFFER_SIZE * sizeof(char));
    if (!buffer) {
        fprintf(stderr, "Chyba alokace pameti pro stats_start\n");
        return 1;
    }
    league_players_array_t *league_players = init_league_players(file_player_names, MAX_PLAYERS_NUM);
    if (league_players == NULL) {
        free(buffer);
        close_file(file_match);
        close_file(file_player_names);
        return 1;
    }

    // read first line from match file and check if it is "match"
    fgets(buffer, buffer_size, file_match);
    if (check_word(buffer, "match") != 0) {
        free(buffer);
        free(league_players->players);
        free(league_players);
        close_file(file_match);
        close_file(file_player_names);
        return 1;
    }

    // read second line from match file and check if read team players exist
    fgets(buffer, buffer_size, file_match);
    if (player_exist(buffer, league_players) != 0) {
        free(buffer);
        free(league_players->players);
        free(league_players);
        close_file(file_match);
        close_file(file_player_names);
        return 1;
    }

    // read third line from match file and check red team statistics
    fgets(buffer, buffer_size, file_match);
    // TO DO: implement red team statistics check

    // read fourth line from match file and check if blue team players exist
    fgets(buffer, buffer_size, file_match);
    if (player_exist(buffer, league_players) != 0) {
        free(buffer);
        free(league_players->players);
        free(league_players);
        close_file(file_match);
        close_file(file_player_names);
        return 1;
    }

    // read third line from match file and check blue team statistics
    fgets(buffer, buffer_size, file_match);
    // TO DO: implement blue team statistics check

    // read sixth line from match file and winner team
    fgets(buffer, buffer_size, file_match);
    if (check_word(buffer, "winner_team") != 0) {
        free(buffer);
        free(league_players->players);
        free(league_players);
        close_file(file_match);
        close_file(file_player_names);
        return 1;
    }

    handle_output_file(file_output_path);
    free(buffer);
    free(league_players->players);
    free(league_players);
    close_file(file_match);
    close_file(file_player_names);
    return 0;
}
