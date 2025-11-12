
#include "../header/display_html.h"

#include "utility.h"

#define MAX_BUFFER_SIZE 256

void display_header(char* output_file);

void display_chart(char* output_file, league_players_array_t* league_players)
{

}

void display_footer(char* output_file);

void display_site(char* output_file, league_players_array_t* league_players)
{
    write_file(output_file, "<!DOCTYPE html>\n<html>\n<head>\n"
        "<meta charset='utf-8'>\n"
        "<title>League of Legends Statistics</title>\n"
        "<style>\n"
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
}
