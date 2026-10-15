#include"../include/functions.h"

void rem_newline(char *string, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (string[i] == '\n')
        {
            string[i] = '\0';
            break;
        }
    }
}

void clear_screen()
{
    printf("\033[H\033[J"); //"\033[H"->Takes cursor to home screen
                            //"\033[J"->Clears the whole screen
    fflush(stdout);         // Flushes the stdout buffer (used for safety)
}

void print_divider(char ch, int length)
{
    for (int i = 0; i < length; i++)
    {
        putchar(ch);
    }
    putchar('\n');
}
void print_ascii_art(char filename[20])
{
    FILE *fp = fopen(filename, "r");
    char c = fgetc(fp);
    while (c != '*') //'*' is used at the beginning of the comment and end of the ascii art
    {
        putchar(c);
        c = fgetc(fp);
    }
}

void print_banner()
{
    printf("\033[36m\033[1m");
    print_divider('=', 70);
    print_ascii_art("ascii-art-quizcore.txt");
    print_divider('=', 70);
    printf("\033[33m"
           "               Test Your Skills & Challenge Your Mind!        \n"
           "\033[0m");
    printf("\n");
}

void print_menu()
{
    printf("  1. Start a New Quiz\n");
    printf("  2. View Scores & Leaderboard\n");
    printf("  3. How to Play & Custom Subjects\n");
    printf("  4. Exit\n\n");
}

void start_quiz_session()
{
    clear_screen();
    print_banner();

    static char username[30];
    printf("Enter your name : ");
    fgets(username, 30, stdin);
    rem_newline(username, strlen(username));

    int sub_choice;
    printf("Choose any one subject given below :\n");
    printf("1.Structured Programming\n");
    printf("2.Discrete Mathematics\n");
    printf("3.Physics\n");
    printf("4.Mathematics\n");
    while (1)
    {
        scanf("%d", &sub_choice);
        getchar(); // grabs '\n' from input buffer
        if (sub_choice >= 1 && sub_choice <= 4)
            break;
    }

    // printf("name : %s\n",username);
    // printf("sub choice : %d\n", sub_choice);

    run_quiz(username, sub_choice);
}

void run_quiz(char *u_name, int s_choice)
{
    static QuizResult qr;
    strcpy(qr.player_name, u_name);

    FILE *ques_file;
    switch (s_choice)
    {
    case 1:
        strcpy(qr.subject_name, "Structured Programming");
        break;

    case 2:
        strcpy(qr.subject_name, "Discrete Mathematics");
        break;

    case 3:
        strcpy(qr.subject_name, "Physics");
        break;

    case 4:
        strcpy(qr.subject_name, "Mathematics");
        break;
    }

    char *filepath = (char *)malloc(100);

    if (filepath != NULL)
    {
        strcpy(filepath, "Questions/");
        strcat(filepath, qr.subject_name);
        strcat(filepath, ".txt");

        ques_file = fopen(filepath, "r");
        free(filepath);
        if (ques_file == NULL)
        {
            printf(ERR_STR);
        }
        
    }
    else
        printf(ERR_STR);

    // Start extracting questions from here
    /*Technique :  Filename already represents the subject. So, there will be no subject name
                   in the file. So,
                   1. We will read every 5 lines from the file as is and wait for the answer
                   2. extract answer and and check user's input
                   3. print correct or incorrect and increment the value of current number if correct
    */
    char question[200];
    char options_a[100];
    char options_b[100];
    char options_c[100];
    char options_d[100];
    char answer[100];
    char divider[100];
    char input[10];
    int ques_index = 0;

    while (1)
    {
        if (qgets(question, ques_file) != NULL)
        {
            if (qgets(options_a, ques_file) == NULL ||
                qgets(options_b, ques_file) == NULL ||
                qgets(options_c, ques_file) == NULL ||
                qgets(options_d, ques_file) == NULL ||
                qgets(answer, ques_file) == NULL ||
                qgets(divider, ques_file) == NULL)
            {
                printf(ERR_STR);
            }
            else
            {
                ques_index++;
                qr.total_questions++;
            }

            printf("%d.%s%s%s%s%s", ques_index, question, options_a, options_b, options_c, options_d);
            printf("answer (A/B/C/D): ");
            if (fgets(input, 3, stdin) == NULL)
            {
                printf("Input error\n");
            }
            if (strcmp(answer, input) == 0)
            {
                printf("Correct!\n");
                qr.correct_answers++;
            }
            else
            {
                printf("Incorrect!\n");
                printf("Correct answer : %s\n", answer);
            }
        }

        else
        {
            qr.accuracy = ((double)qr.correct_answers / qr.total_questions) * 100;
            fclose(ques_file);
            printf("No more questions in file\n");
            printf("Press enter to see results.\n");
            getchar();

            printf("Player name       : %s\n", qr.player_name);
            printf("Subject           : %s\n", qr.subject_name);
            printf("Total Questions   : %d\n", qr.total_questions);
            printf("Correct answers   : %d\n", qr.correct_answers);
            printf("Incorrect answers : %d\n", qr.total_questions - qr.correct_answers);
            printf("Accuracy          : %.2lf%%\n", qr.accuracy);
            break;;
        }
    }
}

void display_help()
{
    clear_screen();
    print_ascii_art("ascii-art-help.txt");
    printf("\n=== How to Play ===\n");
    printf("1. Choose a subject from the menu to start a quiz.\n");
    printf("2. Each question has four options: A, B, C, and D.\n");
    printf("3. Enter the letter of your chosen answer.\n");
    printf("4. Correct answers increase your score by one point.\n");
    printf("5. Incorrect answers do not add to your score.\n");
    printf("6. Your final score is shown when the quiz ends.\n");

    printf("\n=== Adding Custom Questions ===\n");
    printf("Create a text file for the subject and place it where the program can find it.\n");
    printf("Write each question using this seven-line format:\n\n");
    printf("Question text\n");
    printf("A) First option\n");
    printf("B) Second option\n");
    printf("C) Third option\n");
    printf("D) Fourth option\n");
    printf("Correct letter (A, B, C, or D)\n");
    printf("---\n");

    printf("\nRepeat that format for each question. Keep each question and option\n");
    printf("short enough to fit the corresponding buffers in the program.\n");
}