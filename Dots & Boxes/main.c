#include <stdio.h>

#include "Game.h"

int Exit = 0, grid = 0, gametype, gamedifficulty;
char P1Name[30] = {' '};
char P2Name[30] = {' '};

int main_menu();

int One_player(int grid){
    int num;
    while(1){
        system("cls");
        printf("\n\t1. Easy");
        printf("\n\n\t2. Hard");
        printf("\n\n\t3. Main Menu");
        printf("\n\n\tEnter number: ");
        num = input();
        if(num == 1){
            gamedifficulty = 2;
            break;
        } else if(num == 2){
            gamedifficulty = 1;
            break;
        } else if(num == 3){
            return 0;
        }
    }

    printf("\n\n\tEnter player's one name: ");
    fflush(stdin);
    scanf("%[^\n]", P1Name);
    return Game(gamedifficulty, P1Name, "Computer", grid, '\0');
}

int Two_player(int grid){
    printf("\n\n\tEnter player's one name: ");
    fflush(stdin);
    scanf("%[^\n]", P1Name);

    printf("\n\tEnter player's two name: ");
    fflush(stdin);
    scanf("%[^\n]", P2Name);

    return Game(0, P1Name, P2Name, grid, '\0');
}

int New_game(){
    int New_game_key = 0, Player_key = 0;
    while(1){
        system("cls");
        printf("\n\tEnter game mode:");
        printf("\n\n\t1. Beginner (2x2)");
        printf("\n\n\t2. Expert (5x5)");
        printf("\n\n\t3. Main Menu");
        printf("\n\n\tEnter number: ");

        New_game_key = input();

        while(1){
            system("cls");
            if (New_game_key == 1 || New_game_key == 2){
                if (New_game_key == 1){
                    grid = 2;
                } else {
                    grid = 5;
                }
                printf("\n\t1. One Player");
                printf("\n\n\t2. Two Player");
                printf("\n\n\t3. Main Menu");
                printf("\n\n\tEnter number: ");
                Player_key = input();
                if (Player_key == 1){
                    return One_player(grid);
                } else if (Player_key == 2){
                    return Two_player(grid);
                } else if (Player_key == 3){
                    return 0;
                } else {
                    continue;
                }
            } else if (New_game_key == 3) {
                return 0;
            }
            break;
        }
    }
}


int Load_game(){
    int fileno = 0;
    FILE *lfile;
    system("cls");
    printf("\n\t\033[0;33mEnter file number (from 1 to 5): ");
    fileno = input();
    while (fileno < 1 || fileno > 5){
        system("cls");
        printf("\n\tPlease enter a number from 1 to 5");
        printf("\n\n\tEnter file number (from 1 to 5): ");
        fileno = input();
    }
    char name[11] = {'D','o','t','s','_',' ','.','b','i','n'};
	name[5] = fileno + 48;
    if ((lfile = fopen(name, "rb")) == NULL){
       printf("\n\tError! opening the file");
       sleep(1.5);
       return 0;
    }
    printf("\033[0;37m");
    fread(&gametype, sizeof(int), 1, lfile);
    fread(&P1Name, sizeof(char), 30, lfile);
    fread(&P2Name, sizeof(char), 30, lfile);
    fread(&grid, sizeof(int), 1, lfile);
    fclose(lfile);
    return Game(gametype, P1Name, P2Name, grid, name);
}

int Ranking(){
    while(1){
        int HvsHno, PlayerScore;
        char PlayerName[30];

        FILE *rfile;
        system("cls");
        if ((rfile = fopen("Ranking.bin", "rb")) == NULL){
           printf("\n\tError! opening the file");
           sleep(1.5);
           return 0;
        }
        system("cls");
        fread(&HvsHno, sizeof(int), 1, rfile);
        printf("\n\t\t\t\t\t\t   Ranking (Top 10):");

        for (int i = 1; i < HvsHno + 1; i++){
            fread(&PlayerScore, sizeof(int), 1, rfile);
            fread(&PlayerName, sizeof(char), 30, rfile);
            printf("\n\n\t%d. %s    (score: %d)", i, PlayerName, PlayerScore);
        }

        printf("\n\n\tPress enter to return to Main Menu: ");
        if (input() == 0){
            fclose(rfile);
            return 0;
        }
    }
}

int main_menu(){
    int random_shape;
    while(1){
        srand(time(0));
        random_shape = rand()%3;
        system("cls");
        printf("\033[0;35m\n");

        if (random_shape == 0){
            printf(
                   "\t\t\t     _____                      ___      ____                             \n"
                   "\t\t\t    (___  \\       _            / _ \\    |  _ \\                         \n"
                   "\t\t\t     _   \\ \\ ___ | |_   ___   ( (_) )   | | ) ) ___ _   _ ____  ___     \n"
                   "\t\t\t    | |   | / _ \\|  _) /___)   ) _ (    | || | / _ ( \\ / ) _  )/___)    \n"
                   "\t\t\t    | |__/ / |_| | |__|___ |  ( (/  \\   | |_) ) |_| ) X ( (/ /|___ |     \n"
                   "\t\t\t    |_____/ \\___/ \\___|___/    \\__/\\_)  |____/ \\___(_/ \\_)___\\|___/\n");

        } else if (random_shape == 1){
            printf("\t\t\t        ______      _                 ______                             \n"
                   "\t\t\t        |  _  \\    | |         ___    | ___ \\                          \n"
                   "\t\t\t        | | | |___ | |_ ___   ( _ )   | |_/ / _____  _____  ___          \n"
                   "\t\t\t        | | | / _ \\| __/ __|  / _ \\/\\ | ___ \\/ _ \\ \\/ / _ \\/ __|  \n"
                   "\t\t\t        | |/ / (_) | |_\\__ \\ | (_>  < | |_/ / (_) >  <  __/\\__\\     \n"
                   "\t\t\t        |___/ \\___/ \\__|___/  \\___/\\/ \\____/ \\___/_/\\_\\___||___/\n");

        } else {
            printf("\t\t\t       ____        __          ___        ____                           \n"
                   "\t\t\t      / __ \\____  / /______   ( _ )      / __ )____  _  _____  _____    \n"
                   "\t\t\t     / / / / __ \\/ __/ ___/  / __ \\/|   / __  / __ \\| |/_/ _ \\/ ___/ \n"
                   "\t\t\t    / /_/ / /_/ / /_(__  )  / /_/  <   / /_/ / /_/ />  </  __(__  )      \n"
                   "\t\t\t   /_____/\\____/\\__/____/   \\____/\\/  /_____/\\____/_/|_|\\___/____/ \n");
        }

        printf("\033[0;33m");
        printf("\n\t\t\t\t\tMade by Mostafa Galal and Mahmoud Gouda\n");
        printf("\n\n\t1. New game");
        printf("\n\n\t2. Load game");
        printf("\n\n\t3. Ranking");
        printf("\n\n\t4. Exit");
        printf("\n\n\tEnter number: ");

        switch(input()){
            case 1:
                return New_game();
                break;
            case 2:
                return Load_game();
                break;
            case 3:
                return Ranking();
                break;
            case 4:
                return 1;
                break;
            default:
                return 0;
                break;
        }
    }
}

int main()
{
    SetConsoleTitle("Dots & Boxes");
    while (main_menu() == 0){}
    return 0;
}
