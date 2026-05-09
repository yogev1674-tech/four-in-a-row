#ifndef GAME_H//הגדרת מקרו למניעת הכללה כפולה של קבצים
#define GAME_H
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include <string.h>
#include<time.h>//קריאה לסיפרייה לצורך מימוש פונקציות השהייה
#define ROW 6
#define COL 7
#define p1 1
#define p2 2
#define p1_disc 'O'//הגדרת דיסקית שחקן 1
#define p2_disc 'O'//הגדרת דיסקית שחקן 2
#define empty ' '//הגדרת מיקום ריק בלוח
#define RED "\033[31m"//הגדרת קוד הצבע לאדום
#define YELLOW "\033[33m"//הגדרת קוד צבע לצהוב
#define BLUE "\033[36m"//הגדרת קוד צבע לכחול
#define PURPLE "\033[35m"//הגדרת קוד צבע לסגול
#define RESET "\033[0m"// הגדרת קוד לאיפוס הצבע
typedef int matrix[ROW][COL];
void PvP(int* games_played, int* draws, int* p2_wins, int* p1_wins);
int check_winner(matrix Board, int row, int column, int current_player,int highlight_mode);
int make_move(matrix Board, int column, int current_player);
void same_player_name(char* player1, char* player2);
void fix_string(char *player);
void PvC(int* games_played, int* draws, int* p2_wins, int* p1_wins);
int PC_move_easy(matrix Board);
int PC_move_medium(matrix Board);
int sim_and_check_win(matrix Board, int column, int current_player);
int is_column_available(matrix Board, int column);
void print_statistics(int games_played, int draws, int p2_wins, int p1_wins);
void draw_board(matrix Board);
void animate_fall(matrix Board, int column, int row, int current_player);
void tiny_sleep(int ms);
#endif

