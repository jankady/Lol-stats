#include "../header/utility.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

int close_file(FILE* file) {

    if (!fclose(file)) {
        return 0;
    }
    print_error(24, strerror(errno),0);
    return 1;

}

FILE* read_file(const char* file_path) {

    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        print_error(23, strerror(errno),0);
        return NULL;
    }
    return file;
}

int clear_file(const char* file_path) {

    FILE* file = fopen(file_path, "w");
    if (file == NULL) {
        print_error(22, strerror(errno),0);
        return 1;
    }

    close_file(file);
    return 0;
}

int write_file(const char* file_path, char* content) {
    FILE* file = fopen(file_path, "a");
    if (file == NULL) {
        print_error(23, strerror(errno),0);
        return 1;
    }
    if (fputs(content, file) == EOF) {
        print_error(21, strerror(errno),0);
        close_file(file);
        return 1;
    }

    close_file(file);
    return 0;
}

int validate_argument(char* argument) {

    FILE *file = read_file(argument);

    if (!file) {
        print_error(20, argument,0);
        return 1;
    }
    close_file(file);
    return 0;
}

void remove_tailing(char* line)
{
    if (!line) return;
    line[strcspn(line, "\r\n")] = '\0'; // odstrani \n a \r z konce retezce
}

void print_error(int error_code, const char* message, int number_as_message) {
    switch (error_code){
        case 0: // Generic error
            printf("spatny pocet argumentu ocekavano: <soubor se zapasy> <soubor se jmeny hracu> <vystupni soubor>\n");
            break;
        case 1: // Error for memory allocation
            fprintf(stderr, "Chyba alokace pameti pro %s\n", message);
            break;
        case 2: // Error Match for file format in check_word
            fprintf(stderr, "Chyba formatu souboru: ocekavano 'match', nalezeno '%s'\n", message);
            break;
        case 3: // Error Player ID not found in player file in player_exist
            fprintf(stderr, "Hrac s ID '%d' nebyl nalezen v souboru hracu\n", number_as_message);
            break;
        case 4: // Error Player ID duplicated in one match in player_exist
            fprintf(stderr, "Hrac s ID '%d' je uveden vicekrat v jednom zapase\n", number_as_message);
            break;
        case 5: // Error format for player IDs in player_exist
            fprintf(stderr, "Chyba formatu souboru: ocekavano 'id,id,id', nalezeno '%s'\n", message);
            break;
        case 6: // Error KDA format in player_KDA
            fprintf(stderr, "Chyba formatu souboru: ocekavano 'kills;assists;deaths' pro kazdeho hrace, nalezeno '%s'\n", message);
            break;
        case 7: // Error Negative Kills in player_KDA
            fprintf(stderr, "Chyba formatu souboru: statistiky hrace nemohou byt zaporne, nalezeno '%s'\n", message);
            break;
        case 9: // Error for invalid word in check_word
            fprintf(stderr, "Chyba formatu souboru nalezeno neplatne slovo: '%s'\n", message);
            break;
        case 10: // Error when winner team is not red or blue in check_word
            fprintf(stderr, "Chyba formatu souboru: ocekavano 'blue' nebo 'red', nalezeno '%s'\n", message);
            break;
        case 11: // Error formatting when writing player in handle_output_file
            fprintf(stderr,"Chyba fomatovani pro hrace s id: '%d'\n", number_as_message);
            break;
        case 20:
            fprintf(stderr, "Spatny argument nalezeno: %s\n",message);
            break;
        case 21:
            fprintf(stderr,"Doslo k chybe pri zapisu do souboru: %s\n", message);
            break;
        case 22:
            fprintf(stderr,"Doslo k chybe pri vytvareni souboru: %s\n", message);
            break;
        case 23:
            fprintf(stderr,"Doslo k chybe pri otevirani souboru: %s\n", message);
            break;
        case 24:
            fprintf(stderr,"Doslo k chybe pri zavirani souboru: %s\n", message);
            break;

        default:
            fprintf(stderr, "Neznamy error\n");
    }
}

