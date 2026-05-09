#include"game.h"
void draw_board(matrix Board) {
    #ifdef _WIN32//הוספת פקודת מקרו לקמפל על ווינדוז
	system("cls");//הוספת ניקוי מסך כל פעם לפני ציור הלוח
    #endif
    printf("\n");
    for (int r = 0; r < ROW; r++) {//לולאה שעוברת על כל השורות ומדפיסה את החוצץ השמאלי של העמודה
        printf("|");
        for (int c = 0; c < COL; c++) {//לולאה פנימית שעוברת על כל העמודות 
            char ch;
            if (Board[r][c] == 1) {//תנאי לבדוק אם זה שחקן מספר 1
                printf(" %s%c%s |", RED, p1_disc, RESET);//אם המשבצת של שחקן מספר 1 מדפיסה את הדיסקית שלו באדום ואת החוצץ הימני של העמודה
            }
            else if (Board[r][c] == 2) {//תנאי לבדוק אם זה שחקן 2
                printf(" %s%c%s |", YELLOW, p2_disc, RESET);// מדפיסה את הדיסקית שלו בצהוב ואת החוצץ הימני של העמודה
            }
            else if(Board[r][c]==3){//כשזוהה ניצחון של שחקן 1
                printf(" %s%c%s |", BLUE, p1_disc, RESET);//מדפיס ארבע דסקיות מנצחות בכחול
            }
            else if(Board[r][c]==4){//כשזוהה ניצחון של שחקן 2 
                printf(" %s%c%s |", PURPLE, p2_disc, RESET);//מדפיס ארבע דיסקיות מנצחות בסגול
			}
            else {
                printf(" %c |", empty);//אחרת כלומר ריק מדפיס רווח ואת החוצץ הימני של העמודה 
            }
        }
        printf("\n");
    }
    // קו תחתון של הלוח
    printf(" ");
    for (int c = 0; c < COL; c++) {
        printf("----");
    }
    printf("\n ");
    //מדפיס מספרי עמודות מ1-7 מתחת ללוח
    for (int c = 1; c <= COL; c++) {
        printf(" %d  ", c);
    }
    printf("\n\n");
}
void tiny_sleep(int ms) {//פונקציית השהייה במילי שניות
  clock_t start = clock();//שומר את הזמן שחלף מאז תחילת ריצת התוכנית ושומר אותו ביחידות של TICKS
  while ((clock() - start) * 1000 / CLOCKS_PER_SEC < ms);//מחשב כמה זמן עבר מאז שהתחלתי למדוד כלומר בקריאה של הפונקציה ממיר למילי שניות ואז מקבל ערך ומבצע השהייה עד הערך הזה 
}
void animate_fall(matrix Board, int column, int row, int current_player) {//אנימציית נפילה לדיסקית
    Board[row][column] = 0;//מאפסים את המיקום שהתקבל מפונקציית ביצוע המהלך
    for(int r=0; r <= row; r++) {//רצים על השורות עד לשורה שהתקבלה
        Board[r][column] = current_player;//ממקמים זמנית את הדיסקית בכל שורה עד לשורה שהתקבלה
        draw_board(Board);//מציירים את הלוח עם המיקום הזמני של הדיסקית
        tiny_sleep(100);//עוצר כל פעם ל100 מילי שניות כדי לדמות נפילה
        Board[r][column] = 0;//מאפס את המיקום הזמני של הדיסקית לפני המעבר לשורה הבאה
	}
	Board[row][column] = current_player;//מציב בסוף הלולאה את הדיסקית במיקום הסופי שהתקבל
	draw_board(Board);//מצייר את הלוח עם המיקום הסופי של הדיסקית
}