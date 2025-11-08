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

int player_exist(char *buffer, league_players_array_t *players_array, char* team_color, int* playing_ids) {
    remove_tailing(buffer);
    for (int i = 0; i < 3; i++) {
        if ((unsigned long) i * 2 >= strlen(buffer)) {
            fprintf(stderr, "Chyba formatu souboru: ocekavano 'id,id,id', nalezeno '%s'\n", buffer);
            return 1;
        }
        int player_id = buffer[i * 2] - '0'; // convert char to int i subsctract asci values
        if (id_exists(players_array, player_id) != 0) {
            fprintf(stderr, "Hrac s ID '%c' nebyl nalezen v souboru hracu\n", player_id);

            return 1;
        }

        for (int j = 0; j < 6; j++) {
            if (playing_ids[j] == player_id) {
                fprintf(stderr, "Hrac s ID '%d' je uveden vicekrat v jednom zapase\n", player_id);
                return 1;
            }
        }
        set_games_played(players_array, player_id, get_games_played(players_array, player_id) + 1);
        set_played_as_red(players_array, player_id, get_played_as_red(players_array, player_id) + 1);
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
    int playing_ids[6] = {-1};
    printf("zacinam\n");

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

    // read second line from match file and check if red team players exist
    fgets(buffer, buffer_size, file_match);
    if (player_exist(buffer, league_players, "red", playing_ids) != 0) {
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
    if (player_exist(buffer, league_players, "blue", playing_ids) != 0) {
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
