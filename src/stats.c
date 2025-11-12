#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/stats.h"

#include "display_html.h"
#include "../header/league_player.h"
#include "../header/utility.h"

#define MAX_PLAYERS_NUM 20
#define MAX_BUFFER_SIZE 256


void end_program(int end_num, char* buffer, league_players_array_t* league_players,
    FILE* file_match, FILE* file_player_names)
{
    free(buffer);
    buffer = NULL;
    clear_league_players(league_players);
    close_file(file_match);
    close_file(file_player_names);
    exit(end_num);
}

int handle_output_file(league_players_array_t* league_players, char* output_file)
{
    int buffer_size = MAX_BUFFER_SIZE * sizeof(char);
    char* buffer = malloc(buffer_size +1);
    if (!buffer) {
        print_error(1, "handle_output_file",0);
        return 1;
    }
    for (int i = 0; i < league_players->count; i++)
    {
        int text = snprintf(buffer, buffer_size,
            "ID: %d, Name: %s, Games Played: %d, Kills: %d, Assists: %d, Deaths: %d,"
            " Played as Red: %d, Played as Blue: %d, Total Wins: %d, Wins as Red: %d, Wins as Blue: %d\n",
            league_players->players[i].player_id,
            league_players->players[i].player_name,
            league_players->players[i].games_played,
            league_players->players[i].kills,
            league_players->players[i].assists,
            league_players->players[i].deaths,
            league_players->players[i].played_as_red,
            league_players->players[i].played_as_blue,
            league_players->players[i].total_wins,
            league_players->players[i].wins_as_red,
            league_players->players[i].wins_as_blue);
        if (text < 0 || text >= buffer_size) {
            print_error(11, "",league_players->players[i].player_id);
            return 1;
        }
        write_file(output_file, buffer);
    }
    free(buffer);
    return 0;
}

int player_exist(char* buffer, league_players_array_t* players_array, char* team_color, int* playing_ids)
{
    remove_tailing(buffer);
    char* token = strtok(buffer, ",");
    if (!token) {
        print_error(5, buffer,0);
        return 1;
    }
    int player_id = atoi(token);
    for (int i = 0; i < 3; i++)
    {
        if (id_exists(players_array, player_id) != 0)
        {
            print_error(3, "",player_id);
            return 1;
        }
        for (int j = 0; j < 6; j++)
        {
            if (playing_ids[j] == player_id)
            {
                print_error(4, "",player_id);
                return 1;
            }
        }
        if (strcmp(team_color, "red") == 0)
        {
            playing_ids[i] = player_id;
            set_played_as_red(players_array, player_id, get_played_as_red(players_array, player_id) + 1);
        }
        else if (strcmp(team_color, "blue") == 0)
        {
            playing_ids[i + 3] = player_id;
            set_played_as_blue(players_array, player_id, get_played_as_blue(players_array, player_id) + 1);
        }
        set_games_played(players_array, player_id, get_games_played(players_array, player_id) + 1);

        char* temp_token = strtok(NULL, ","); // check format
        if (i == 2)
        {
            if (temp_token != NULL)
            {
                print_error(5, buffer,0);
                return 1;
            }
            return 0;
        }
        if (temp_token == NULL)
        {
            print_error(5, buffer,0);
            return 1;
        }
        player_id = atoi(temp_token);
    }
    return 0;
}

int check_word(char* buffer,league_players_array_t* league_players, const char* expected_word, int *playing_ids)
{
    remove_tailing(buffer);
    if (strcmp(expected_word, "match") == 0)
    {
        if (strcmp(buffer, "match") != 0)
        {
            print_error(2,buffer,0);
            return 1;
        }
    }
    else if (strcmp(expected_word, "winner_team") == 0)
    {
        if (strcmp(buffer, "red") == 0)
        {
            for (int i = 0; i < 3; i++)
            {
                set_total_wins(league_players,playing_ids[i], get_total_wins(league_players,playing_ids[i]) + 1);
                set_wins_as_red(league_players,playing_ids[i], get_wins_as_red(league_players ,playing_ids[i]) + 1);
            }
                return 0;
        }
        if (strcmp(buffer, "blue") == 0)
        {
            for (int i = 3; i < 6; i++)
            {
                set_total_wins(league_players,playing_ids[i], get_total_wins(league_players,playing_ids[i]) + 1);
                set_wins_as_blue(league_players,playing_ids[i], get_wins_as_blue(league_players ,playing_ids[i]) + 1);
            }
            return 0;
        }
        print_error(10,buffer,0);
        return 1;
    }
    else
    {
        print_error(9, buffer,0);
        return 1;
    }

    return 0;
}

int player_KDA(char* buffer, league_players_array_t* league_players, char* team_color, int* playing_ids)
{
    remove_tailing(buffer);
    // i need to use strtok_r because i am doing a nested searching for kills, assists and deaths
    char* one_player_pointer = NULL ; // uset to store the rest of the buffer after the first strtok_r
    char* one_player_stats = strtok_r(buffer, ",", &one_player_pointer);
    for (int i = 0; i < 3; i++)
    {
        if (one_player_stats == NULL)
        {
            print_error(6, buffer,0);
            return 1;
        }
        char* temp_token = strtok(one_player_stats, ";");
        if (temp_token == NULL)
        {
            print_error(6, buffer,0);
            return 1;
        }
        int kills =  atoi(temp_token);
        temp_token = strtok(NULL, ";");
        if (temp_token == NULL)
        {
            print_error(6, buffer,0);
            return 1;
        }
        int assists = atoi(temp_token);
        temp_token = strtok(NULL, ";");
        if (temp_token == NULL)
        {
            print_error(6, buffer,0);
            return 1;
        }
        int deaths = atoi(temp_token);
        if (kills < 0 || assists < 0 || deaths < 0)
        {
            print_error(7,buffer,0);
            return 1;
        }
        if (strcmp(team_color, "red") == 0)
        {
            set_kills(league_players, playing_ids[i], get_kills(league_players, playing_ids[i]) + kills);
            set_assists(league_players, playing_ids[i], get_assists(league_players, playing_ids[i]) + assists);
            set_deaths(league_players, playing_ids[i], get_deaths(league_players, playing_ids[i]) + deaths);
        }
        else if (strcmp(team_color, "blue") == 0)
        {
            set_kills(league_players, playing_ids[i+3], get_kills(league_players, playing_ids[i+3]) + kills);
            set_assists(league_players, playing_ids[i+3], get_assists(league_players, playing_ids[i+3]) + assists);
            set_deaths(league_players, playing_ids[i+3], get_deaths(league_players, playing_ids[i+3]) + deaths);
        }
        one_player_stats = strtok_r(NULL, ",", &one_player_pointer); // check format
        if (i == 2)
        {
            if (one_player_stats != NULL)
            {
                print_error(6, buffer,0);
                return 1;
            }
            return 0;
        }
        if (one_player_stats == NULL)
        {
            print_error(6, buffer,0);
            return 1;
        }
    }
    return 0;
}

void start_main_loop(char* buffer, int buffer_size, FILE* file_match, FILE* file_player_names,
    league_players_array_t* league_players, int* playing_ids, char* output_file)
{
    while (fgets(buffer, buffer_size, file_match) != NULL) {
        // read first line from match file and check if it is "match"
        if (check_word(buffer, league_players, "match", playing_ids) != 0)
        {
            end_program(1, buffer, league_players, file_match, file_player_names);
        }
        // read second line from match file and check if red team players exist
        fgets(buffer, buffer_size, file_match);
        if (player_exist(buffer, league_players, "red", playing_ids) != 0)
        {
            end_program(1, buffer, league_players, file_match, file_player_names);
        }
        // read third line from match file and check red team statistics
        fgets(buffer, buffer_size, file_match);
        if (player_KDA(buffer, league_players, "red", playing_ids) != 0)
        {
            end_program(1, buffer, league_players, file_match, file_player_names);
        }
        // read fourth line from match file and check if blue team players exist
        fgets(buffer, buffer_size, file_match);
        if (player_exist(buffer, league_players, "blue", playing_ids) != 0)
        {
            end_program(1, buffer, league_players, file_match, file_player_names);
        }
        // read third line from match file and check blue team statistics
        fgets(buffer, buffer_size, file_match);
        if (player_KDA(buffer, league_players, "blue", playing_ids) != 0)
        {
            end_program(1, buffer, league_players, file_match, file_player_names);
        }
        // read sixth line from match file and winner team
        fgets(buffer, buffer_size, file_match);
        if (check_word(buffer, league_players, "winner_team", playing_ids) != 0)
        {
            end_program(1, buffer, league_players, file_match, file_player_names);
        }
        // reset players after each match
        for (int i = 0; i < 6; i++) playing_ids[i] = -1;
    }

    // after all matches are processed, write to output file
    display_site(output_file, league_players);
}

int start_stats(const char* file_match_path, const char* file_player_names_path, char* file_output_path)
{
    FILE* file_match = read_file(file_match_path);
    FILE* file_player_names = read_file(file_player_names_path);
    if (file_match == NULL || file_player_names == NULL)
    {
        fprintf(stderr, "Chyba otevreni jednoho ze souboru\n");
        if (file_match)
            close_file(file_match);
        if (file_player_names)
            close_file(file_player_names);

        return 1;
    }
    if (clear_file(file_output_path) != 0)
    {
        fprintf(stderr, "Chyba vynulovani vystupniho souboru\n");
        close_file(file_match);
        close_file(file_player_names);
        return 1;
    }

    int buffer_size = MAX_BUFFER_SIZE;
    char* buffer = malloc(buffer_size * sizeof(char) +1);
    if (!buffer)
    {
        print_error(1, "stats_start",0);
        return 1;
    }
    league_players_array_t* league_players = init_league_players(file_player_names, MAX_PLAYERS_NUM);
    if (league_players == NULL)
    {
        free(buffer);
        close_file(file_match);
        close_file(file_player_names);
        return 1;
    }
    int playing_ids[6] = {-1};
    start_main_loop(buffer, buffer_size, file_match, file_player_names, league_players, playing_ids, file_output_path);
    end_program(0, buffer, league_players, file_match, file_player_names);
    free(buffer);
    return 0;
}