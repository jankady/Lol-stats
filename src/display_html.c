
#include "../header/display_html.h"

#include "utility.h"

#define MAX_BUFFER_SIZE 256


void display_chart(const char* output_file, const league_players_array_t* league_players)
{
    write_file(output_file, "<h1>League of Legends Player Statistics</h1>\n");
    write_file(output_file, "<h2>Player Overview</h2>\n");
    write_file(output_file, "<table>\n<tr>"
        "<th>Player</th>"
        "<th>Games</th>"
        "<th>Wins</th>"
        "<th>Win Rate</th>"
        "<th>K/D/A</th>"
        "<th>KDA Ratio</th>"
        "<th>ELO</th>"
        "</tr>\n");

    for (int i = 0; i < league_players->count; i++) {
        league_player_t* player = &league_players->players[i];
        float winrate = player->games_played != 0 ? ((float) player->total_wins * 100.0f) / (float) player->games_played: 0.0f;
        float kda_ratio = (float) (player->kills + player->assists) / (float)(player->deaths > 0 ? player->deaths : 1);

        char row[MAX_BUFFER_SIZE];
        snprintf(row, sizeof(row),
            "<tr>"
            "<td><strong>%s</strong></td>"
            "<td>%d</td>"
            "<td>%d</td>"
            "<td>%.1f%%</td>"
            "<td>%d/%d/%d</td>"
            "<td>%.2f</td>"
            "<td>%d</td>"
            "</tr>\n",
            player->player_name,
            player->games_played,
            player->total_wins,
            winrate,
            player->kills,
            player->deaths,
            player->assists,
            kda_ratio,
            player->elo
        );
        write_file(output_file, row);
    }
    write_file(output_file, "</table>\n");
}

void display_footer(char* output_file)
{

}

void display_site(char* output_file, league_players_array_t* league_players)
{
    write_file(output_file, "<!DOCTYPE html>\n<html>\n<head>\n"
        "<meta charset='utf-8'>\n"
        "<title>League of Legends Statistics</title>\n"
        "<style>\n" // default styling
        "body { font-family: Arial, sans-serif; margin: 20px; background: #0a1428; color: #c9d1d9; }\n"
        "h1 { color: #58a6ff; text-align: center; }\n"
        "h2 { color: #58a6ff; margin-top: 40px; }\n"
        "table { border-collapse: collapse; width: 100%; margin: 20px 0; background: #161b22; }\n"
        "th, td { border: 1px solid #30363d; padding: 12px; text-align: left; }\n"
        "th { background-color: #21262d; color: #58a6ff; font-weight: bold; }\n"
        "tr:hover { background-color: #1c2128; }\n"
        ".chart-container { margin: 30px 0; }\n"
        "</style>\n"
        "</head>\n<body>\n");
    display_chart(output_file, league_players);
    write_file(output_file, "</body>\n</html>\n");
}
