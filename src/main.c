#include"../include/functions.h"

int main()
{
    clear_screen();
    int menu_opt;
    while(1)
    {
        print_banner();
        print_menu();
        scanf("%d", &menu_opt);
        getchar();      //grabs '\n' from input buffer
        if (!(menu_opt >= 1 && menu_opt <= 4))
        {
            printf("Invaid input. Valid inputs : 1-4. Enter to reselect input.\n");
            getchar(); // Using getchar() to make the program to wait for a keystroke,
                       // as in the next iteration the text will get wiped out instantly
            clear_screen();
        }           

        switch (menu_opt)
        {
        case 1:
            start_quiz_session();
            break;
        case 2:
            printf("Feature not available\n\nPress Enter to exit\n");
            getchar();
            clear_screen();
            break;
        case 3:
            display_help();
            printf("\n\nPress Enter to exit help menu\n\n");
            getchar();
            clear_screen();
            break;
        case 4:
            clear_screen();
            print_banner();
            printf("\033[32m"
                   "\nThank you for playing QuizCore! Have a great day!\n\n"
                   "\033[0m");
            return 0;
        }
    }

    

    //printf("Loop breaked\n");
    getchar();
    clear_screen();

    return 0;
}