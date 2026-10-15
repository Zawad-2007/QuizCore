#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERR_STR "\033[31mFILE error\n"
#define qgets(buf, fstream) fgets(buf, sizeof(buf), fstream)

typedef struct
{
    char player_name[30];
    char subject_name[30];
    int total_questions;
    int correct_answers;
    int incorrect_answers;
    double accuracy;
} QuizResult;

void rem_newline(char *string, int size);

void clear_screen();

void print_divider(char ch, int length);

void print_ascii_art(char filename[20]);

void print_banner();

void print_menu();

void start_quiz_session();

void run_quiz(char *u_name, int s_choice);

void display_help();
