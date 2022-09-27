#include "AI.h"
#include "Save.h"
#include "Rank.h"
#include "Scan.h"

int Game(int gametype, char P1Name[30], char P2Name[30], int grid, char name[11])
{
    struct {
        char name[30];
        int moves;
        int score;
        int color;
    } P1 = {" ", 0 ,0 ,0}, P2 = {" ", 0, 0, 1};

    for (int i = 0; i < 30; i++){
        P1.name[i] = P1Name[i];
        P2.name[i] = P2Name[i];
    }

    int redo_counter = 0, sec = 0, fileno = 0, choose = 0, aloop = 1;
    int x = grid, y = grid, history_len = x*(x+1)*2, gamet = gametype;
    int counter = 0, found = 0, invalid = 0, player = 0, seconds = 0;
    char lines[x+x+1][y+y+1], emptystr[30];
    int available_moves = x * (x+1) * 2;
    int rowno, columnno, x_coor, y_coor, emptyint, moves_history[history_len][3];
    int boxes[x*x], ind = 0 , inloop = 0, moves_redo[history_len][3];
    clock_t dif, before = clock();

    for (int i = 1; i < 2*x; i+=2){
        for (int j = 1; j < 2*y; j+=2){
            boxes[ind] = i*10+j;
            ind++;
        }
    }

    for (int i = 0; i < x+x+1; i++){
        for (int j = 0; j < y+y+1; j++){
            lines[i][j] = ' ';
        }
    }

    for (int i = 0; i < history_len; i++){
        moves_history[i][0] = 0;
        moves_history[i][1] = 0;
        moves_history[i][2] = 0;
    }

    printf("\n");

    for (int i = 0; i < history_len; i++){
        moves_redo[i][0] = 0;
        moves_redo[i][1] = 0;
        moves_redo[i][2] = 0;
    }

    for (int i = 0; i < x+x+1; i+=2){
        for (int j = 0; j < y+y+1; j+=2){
            lines[i][j] = 254;
        }
    }

    if (gamet > 2){
        FILE *sfile;
        if ((sfile = fopen(name,"rb")) == NULL){
           printf("Error! opening file");
           exit(1);
        }
        fread(&emptyint, sizeof(int), 1, sfile);
        fread(&emptystr, sizeof(char), 30, sfile);
        fread(&emptystr, sizeof(char), 30, sfile);
        fread(&x, sizeof(int), 1, sfile);
        fread(&counter, sizeof(int), 1, sfile);
        fread(&P1.score, sizeof(int), 1, sfile);
        fread(&P2.score, sizeof(int), 1, sfile);
        fread(&P1.moves, sizeof(int), 1, sfile);
        fread(&P2.moves, sizeof(int), 1, sfile);
        fread(&available_moves, sizeof(int), 1, sfile);
        fread(&seconds, sizeof(int), 1, sfile);
        fread(&lines, sizeof(char), (x+x+1) * (x+x+1), sfile);
        fread(&player, sizeof(int), 1, sfile);
        fread(&boxes, sizeof(int), x*x, sfile);
        fread(&history_len, sizeof(int), 1, sfile);
        fread(&moves_history, sizeof(int), history_len * 3, sfile);
        fclose(sfile);
    }

    gamet %= 10;

    FILE *GLog;

    GLog = fopen("GLog.txt", "w");

    while(1){


        system("cls");

        GLog = fopen("GLog.txt", "a+");
        if(GLog != NULL){
            if (counter == 0){
                fprintf(GLog, "Gametype: %d\n", gametype);
                fprintf(GLog, "P1Name: %s\n", P1.name);
                fprintf(GLog, "P2Name: %s\n", P2.name);
                fprintf(GLog, "Grid: %d\n\n", x);
            }
            fprintf(GLog, "counter: %d\n", counter);
            fprintf(GLog, "P1.score: %d\n", P1.score);
            fprintf(GLog, "P2.score: %d\n", P2.score);
            fprintf(GLog, "P1.moves: %d\n", P1.moves);
            fprintf(GLog, "P2.moves: %d\n", P2.moves);
            fprintf(GLog, "available_moves: %d\n", available_moves);
            fprintf(GLog, "seconds: %d\n", seconds);
            fprintf(GLog, "player: %d\n\n", player);
            fclose(GLog);
        }

        for (int i = 1; i < x+x+1; i+=2){
            for (int j = 1; j < y+y+1; j+=2){
                for (int k = 0; k < x*x; k++){
                   if (i*10 + j == boxes[k]){
                        if (lines[i][j-1] == -70 && lines[i][j+1] == -70 && lines[i-1][j] == -51 && lines[i+1][j] == -51){
                            if (inloop == 0){
                                player ^= 1;
                            }
                            lines[i][j] = 219;
                            boxes[k] = boxes[k] * 10 + player;
                            if (player){
                                P2.score++;
                            } else {
                                P1.score++;
                            }
                            inloop = 1;
                        }
                        break;
                    }
                }
            }
        }

        inloop = 0;
        if (x < 5){
            printf("\n\t\t\t\t\t\t       ");
        } else {
            printf("\n\t\t\t\t\t\t");
        }
        for (int i = 0; i < x+x+1; i++){
            printf("\033[0;37m");
            if (i%2 == 0){
                printf("%d", i + 1);
            } else {
                printf(" %d ", i + 1);
            }
        }

        for (int i = 0; i < x+x+1; i++){
            if (x < 5){
                printf("\n\t\t\t\t\t\t     %d ", i + 1);
            } else {
                if (i < 9){
                    printf("\n\t\t\t\t\t     %d  ", i + 1);
                } else {
                    printf("\n\t\t\t\t\t     %d ", i + 1);
                }
            }
            for (int j = 0; j < y+y+1; j++){
                for (int k = 0; k < history_len; k++){
                    if(((i+1) == moves_history[k][0]) && ((j+1) == moves_history[k][1])){
                        if (moves_history[k][2]){
                            printf("\033[0;31m");
                        } else {
                            printf("\033[0;34m");
                        }
                        break;
                    }
                }
                if (i%2 && j%2){
                    for (int k = 0; k < x*x; k++){
                        if (i*10 + j == boxes[k]/10){
                            if (boxes[k]%10){
                                printf("\033[0;31m");
                            } else {
                                printf("\033[0;34m");
                            }
                        break;
                        }
                    }
                    printf("%c%c%c", lines[i][j], lines[i][j], lines[i][j]);
                } else if (i%2 == 0 && j%2) {
                    printf("%c%c%c", lines[i][j], lines[i][j], lines[i][j]);
                } else if (i%2 && j%2 == 0) {
                    printf("%c", lines[i][j]);
                } else {
                    printf("\033[0;37m");
                    printf("%c", lines[i][j]);
                }
                printf("\033[0;37m");
            }
        }
        printf("\n\n\t\033[0;34mPlayer one name: ");
        for (int i = 0; i < 30; i++){
            if (P1.name[i] != '\0'){
                printf("%c", P1.name[i]);
            } else {
                printf("\033[0;30m");
                printf(" ");
            }
        }
        printf("\t\t\t\033[0;31mPlayer two name: %s", P2.name);
        printf("\n\n\t\033[0;34mPlayer one score: %d", P1.score);
        printf("\t\t\t\t\t\t\033[0;31mPlayer two score: %d", P2.score);
        printf("\n\n\t\033[0;34mPlayer one number of moves: %d", P1.moves);
        printf("\t\t\t\t\t\033[0;31mPlayer two number of moves: %d", P2.moves);
        printf("\033[0;37m");
        printf("\n\n\tAvailable moves: %d", available_moves);
        dif = clock() - before;
        sec = seconds + dif / CLOCKS_PER_SEC;
        printf("\t\t\t\t\t\tTime passed: %d secs", sec);
        printf("\n\n\t- Enter (U/u) for Undo || (R/r) for Redo || (S/s) for Save || (M/m) for Main Menu || (E/e) for Exit");
        printf("\n\n\t- Enter number of row and column to draw the line");
        if (!available_moves){
            if (P1.score == P2.score){
                printf("\n\n\t\t\t\t\t\t\tTie!!!");
            } else if (P1.score > P2.score){
                printf("\n\n\t\t\t\t\t\t  \033[0;34mPlayer one Wins!!!");
                if (gamet == 0 && aloop == 1){
                    Rank(P1.name, P1.score);
                }
            } else {
                if (gamet == 0){
                    printf("\n\n\t\t\t\t\t\t  \033[0;31mPlayer two Wins!!!");
                } else {
                    printf("\n\n\t\t\t\t\t\t  \033[0;31mComputer Wins!!!");
                }
                if (gamet == 0 && aloop == 1){
                    Rank(P2.name, P2.score);
                }
            }
            aloop = 0;
            printf("\033[0;37m");
            printf("\n\n\t1. Main Menu");
            printf("\n\n\t2. Exit");
            printf("\n\n\tEnter number: ");
            choose = input();
            if (choose == 1){
                return 0;
            } else if (choose == 2){
                return 1;
            } else {
                continue;
            }
        }

        while(1){
            found = 0;
            if (invalid){
                printf("\n\n\tPlease enter a valid move");
                invalid = 0;
            }
            if (gamet != 0 && player == 1){
                if (!((rowno =='r'  ||rowno =='R'  || columnno == 'r'|| columnno == 'R') || (rowno =='u'  ||rowno =='U'  || columnno == 'u'|| columnno == 'U'))){
                    AI(x, y, lines, moves_history, counter, &rowno, &columnno, gamet);
                }
            } else {
                if (player == 0){
                    printf("\033[0;34m");
                    printf("\n\n\tPlayer's One turn");
                } else if (player == 1){
                    printf("\033[0;31m");
                    printf("\n\n\tPlayer's Two turn");
                }
                printf("\n\n\tEnter row number: ");
                rowno = input();
                printf("\n\tEnter column number: ");
                columnno = input();
                printf("\033[0;37m");
            }if(rowno==-1||columnno==-1){
                    invalid=1;
                }
            if (rowno =='e'  ||rowno =='E'  || columnno == 'e'|| columnno == 'E'){
                printf("\n\tPress enter to Exit: ");
                if (input() == 0){
                    return 1;
                } else {
                    break;
                }
            }
            if (rowno =='m'  ||rowno =='M'  || columnno == 'm'|| columnno == 'M'){
                printf("\n\tPress enter to return to Main Menu: ");
                if (input() == 0){
                    return 0;
                } else {
                    break;
                }
            }
            if (rowno =='s'  ||rowno =='S'  || columnno == 's'|| columnno == 'S'){
                system("cls");
                printf("\n\t\033[0;33mEnter file number (from 1 to 5): ");
                fileno = input();
                while (fileno < 1 || fileno > 5){
                    system("cls");
                    printf("\n\tPlease enter a number from 1 to 5");
                    printf("\n\n\tEnter file number (from 1 to 5): ");
                    fileno = input();
                }
                Save((10 + gamet), P1.name, P2.name, x, counter, P1.score, P2.score, P1.moves, P2.moves, available_moves, sec, lines, player, boxes, history_len, moves_history, fileno);
                break;
            }
            if ((rowno =='r'  ||rowno =='R'  || columnno == 'r'|| columnno == 'R')&& redo_counter > 0){
                available_moves--;
                redo_counter--;
                x_coor = moves_redo[redo_counter][0];
                y_coor = moves_redo[redo_counter][1];
                moves_history[counter][0] = x_coor;
                moves_history[counter][1] = y_coor;
                moves_history[counter][2] = moves_redo[redo_counter][2];
                counter++;
                x_coor--;
                y_coor--;
                if (x_coor % 2 == 0 && y_coor % 2 == 1){
                    lines[x_coor][y_coor] = 205;
                } else if(x_coor % 2 == 1 && y_coor % 2 == 0){
                    lines[x_coor][y_coor] = 186;
                }
                moves_redo[redo_counter][0] = 0;
                moves_redo[redo_counter][1] = 0;
                moves_redo[redo_counter][2] = 0;
                player ^= 1;
                P1.moves = 0;
                P2.moves = 0;
                for (int i = 0; i < counter; i++){
                    if(moves_history[i][2]){
                        P2.moves++;
                    } else {
                        P1.moves++;
                    }
                }
                inloop = 0;
                for (int i = 1; i < x+x+1; i+=2){
                    for (int j = 1; j < y+y+1; j+=2){
                        for (int k = 0; k < x*x; k++){
                           if (i*10 + j == boxes[k]){
                                if (lines[i][j-1] == -70 && lines[i][j+1] == -70 && lines[i-1][j] == -51 && lines[i+1][j] == -51){
                                    if (inloop == 0){
                                        player ^= 1;
                                    }
                                    lines[i][j] = 219;
                                    boxes[k] = boxes[k] * 10 + player;
                                    if (player){
                                        P2.score++;
                                    } else {
                                        P1.score++;
                                    }
                                    inloop = 1;
                                }
                                break;
                            }
                        }
                    }
                }
                if (gamet == 1 && player == 1){
                    rowno = 'r';
                    columnno = 'r';
                }
                break;
            }
            //undo function
            if ((rowno =='u'  ||rowno =='U'  || columnno == 'u'|| columnno == 'U') && counter > 0){
                available_moves++;
                counter--;
                x_coor = moves_history[counter][0];
                y_coor = moves_history[counter][1];
                moves_redo[redo_counter][0] = x_coor;
                moves_redo[redo_counter][1] = y_coor;
                moves_redo[redo_counter][2] = moves_history[counter][2];
                redo_counter++;
                lines[x_coor-1][y_coor-1] = ' ';
                moves_history[counter][0] = 0;
                moves_history[counter][1] = 0;
                moves_history[counter][2] = 0;
                player ^= 1;
                P1.moves = 0;
                P2.moves = 0;
                for (int i = 0; i < counter; i++){
                    if(moves_history[i][2]){
                        P2.moves++;
                    } else {
                        P1.moves++;
                    }
                }
                inloop = 0;
                for (int i = 1; i < x+x+1; i+=2){
                    for (int j = 1; j < y+y+1; j+=2){
                        for (int k = 0; k < x*x; k++){
                           if (i*10 + j == boxes[k]/10){
                                if (!(lines[i][j-1] == -70 && lines[i][j+1] == -70 && lines[i-1][j] == -51 && lines[i+1][j] == -51)){
                                    if (inloop == 0){
                                        player ^= 1;
                                    }
                                    lines[i][j] = ' ';
                                    boxes[k] /= 10;
                                    if (player){
                                        P2.score--;
                                    } else {
                                        P1.score--;
                                    }
                                    inloop = 1;
                                }
                                break;
                            }
                        }
                    }
                }
                if (gamet == 1 && player == 1){
                    rowno = 'u';
                    columnno = 'u';
                }
                break;
            }
            if((rowno < 1 || columnno > (x+x+1)) || (columnno  < 1 || rowno > (x+x+1))){
                invalid = 1;
                break;
            } else if ((rowno % 2 == 0 && columnno % 2 == 1) || (columnno % 2 == 0 && rowno % 2 == 1)){
                for (int i = 0; i < history_len; i++){
                    if((rowno == moves_history[i][0]) && (columnno == moves_history[i][1])){
                        found = 1;
                        break;
                    }
                }
                if (found){
                    invalid = 1;
                    break;
                } else {
                    for (int i = 0; i < redo_counter; i++){
                        moves_redo[i][0] = 0;
                        moves_redo[i][1] = 0;
                        moves_redo[i][2] = 0;
                    }
                    redo_counter = 0;
                    moves_history[counter][0] = rowno;
                    moves_history[counter][1] = columnno;
                    moves_history[counter][2] = player;
                    x_coor = rowno;
                    y_coor = columnno;
                    x_coor -= 1;
                    y_coor -= 1;
                    if (x_coor % 2 == 0 && y_coor % 2 == 1){
                        lines[x_coor][y_coor] = 205;
                    } else if(x_coor % 2 == 1 && y_coor % 2 == 0){
                        lines[x_coor][y_coor] = 186;
                    }
                    if (player){
                        P2.moves++;
                    } else {
                        P1.moves++;
                    }
                    player ^= 1;
                    available_moves--;
                    counter++;
                    break;
                }
            } else {
                invalid = 1;
                break;
            }
        }
    }
    return 0;
}
