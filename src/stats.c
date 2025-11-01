#pragma once
#include <stdio.h>
#include "../header/stats.h"
#include <stdlib.h>
#include <string.h>

#include "../header/utility.h"

void remove_tailing(char* line)
{
    if (!line) return;
    line[strcspn(line, "\r\n")] = '\0'; // odstrani \n a \r z konce retezce
}

int handle_player_names_file(char player_id, FILE* file_player_names)
{
    char* buffer = malloc(256 * sizeof(char)); // nastavim max 256 znaku na jeden radek
    if (!buffer)
    {
        printf("Chyba alokace pameti\n");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), file_player_names))
    {
        printf("Player name: %s", buffer);
    }
    free(buffer);
}

int handle_match_file(FILE* file_match, FILE* file_player_names)
{
    char* buffer = malloc(256 * sizeof(char)); // nastavim max 256 znaku na jeden radek
    if (!buffer)
    {
        printf("Chyba alokace pameti\n");
        return 1;
    }
    fgets(buffer, sizeof(buffer), file_match);
    remove_tailing(buffer);
    if (strcmp(buffer, "match") != 0)
    {
        printf("Chyba formatu souboru: ocekavano 'match', nalezeno '%s'\n", buffer);
        free(buffer);
        return 1;
    }
    handle_player_names_file('1', file_player_names);


    close_file(file_match);
    close_file(file_player_names);
    free(buffer);
    return 0;
}

void start_stats(char* file_match, char* file_player_names, char* file_output)
{
    printf("zacinam\n");
    handle_match_file(read_file(file_match), read_file(file_player_names));


}
