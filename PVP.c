#include"game.h"
void PvP(int* games_played, int* draws, int* p2_wins, int* p1_wins){
	//משתני סטטיסטיקות
	matrix Board = { 0 };
	char *player1 = (char*)malloc(21 * sizeof(char));
	assert(player1);
	char *player2 = (char*)malloc(21 * sizeof(char));
	assert(player2);
	getchar();//for the '\n'
	printf("Plese enter player 1 name:");
	fgets(player1, 21, stdin);//stdin=לקלוט ממקלדת
	printf("\n");
	printf("Plese enter player 2 name:");
	fgets(player2, 21, stdin);
	printf("\n");
	same_player_name(player1,player2);//בודק שהשמות שונים במידה ולא מוסיף להם סימני זיהוי
	fix_string(player1);//מוחק אנטר
	fix_string(player2);//מוחק אנטר
	printf("Wellcome %s and %s to Four in a row game!\n", player1, player2);
	printf("\n");
	int current_player = p1;
	char *current_player_name = player1;//מחרוזת שתגיד כל הזמן תור מי
	draw_board(Board);
	for (int move = 0; move < 42;) {//פה רצתי בפור למרות שבשני שנגד המחשב רצתי בוויל ללא סיבה מיוחדת
			int column, row;
			printf("%s, Plese choose a column (1-7):",current_player_name);//מעדכן את שם הדחקן ומכריז על תורו
			scanf_s("%d" ,&column);
			column--;//לנרמל
			//בחירת השורה בעמודה שנבחרה
			row = make_move(Board, column, current_player);//בוחר שורה ובודק חוקיות שלה בהתאם לעמודה שנבחרה
			if (row == -1) {
				printf("Invalid move,the column you chose is full %s plese try agin\n", current_player_name);
				continue;
			}
			else if (row == -2) {
				printf("Invalid move, please choose a column between 1 to 7 %s plese try agin\n", current_player_name);
				continue;
			}
			animate_fall(Board, column, row, current_player);//אנימציית נפילה וציור הלוח לאחר כל מהלך חוקי שלא כולל ניצחון
			int result = check_winner(Board, row, column, current_player,1);
			//בדיקת ניצחון
			if (result) {
				(*games_played)++;//מעדכן סטטיסטיקות
				if (current_player == p1) {
					(*p1_wins)++;//מעדכן סטטיסטיקות
				}
				else {
					(*p2_wins)++;//מעדכן סטטיסטיקות
				}
				draw_board(Board);//ציור הלוח בעת ניצחון כולל הדגשת שורה מנצחת
				printf("Congratulation %s, you are the winner!!!\n", current_player_name);
				printf("Press ENTER to return to menu...");
				getchar();//קליטה של אנטר
			    getchar();//מנקה את הבאפר
				free(player1);
				free(player2);
				return;
			}
			//החלפת תורות
			if (current_player == p1) {
				current_player = p2;
				current_player_name = player2;
			}
			else {
				current_player = p1;
				current_player_name = player1;
			}
			//מהלך הבא
			move++;
	}
	(*games_played)++;//סטטיסטיקות בשוויון
	(*draws)++;//סטטיסטיקות בשוויון
	free(player1);
	free(player2);
	draw_board(Board);// ציור הלוח במקרה של שוויון
	printf("The game ended in a draw!\n");
	return;
}   
int check_winner(matrix Board,int row,int column,int current_player,int highlight_mode){
	int count;
	//בדיקה אופקית
	count = 1;
	//שמאל
	for (int c = column - 1; c>=0 && Board[row][c] == current_player; c--) {//בודק לצד שמאל מתחיל מקום אחד לפני או אחרי כי אני בודק מהפעולה האחרונה
		count++;
	}
	//ימין
	for (int c = column + 1; c < COL && Board[row][c] == current_player; c++) {//בודק לצד ימין 
		count++;
	}
  if (count >= 4){//אם בריצה ימין ושמאל התגלה רצף
    if (highlight_mode == 1) {//בודק שזה מהלך חוקי ולא סימולציה ובמידה וכן צובע 4 דיסקיות מנצחות
        int h = current_player + 2;//אנידיקציה להשלים לכחול
        Board[row][column] = h;
        int c;
        for (c = column - 1; c >= 0 && Board[row][c] == current_player; c--) {//עושה את אותה ריצה של הניצחון ופשוט מחליף אדום או צהוב בכחול
            Board[row][c] = h;
		}	
        for (c = column + 1; c < COL && Board[row][c] == current_player; c++) {
            Board[row][c] = h;
		}
    }
    return 1;
  }
	//בדיכה אנכית
	count = 1;
	//למטה
	for (int r = row + 1; r < ROW && Board[r][column] == current_player; r++) {
		count++;
	}
	//למעלה
	for (int r = row - 1; r >= 0 && Board[r][column] == current_player; r--) {
		count++;
	}
  if(count>=4){//במקרה של ניצחון מעדכן דגל לשחקן 1 או 2 בהתאם על מנת לצבוע דיסקיות מנצחות
   	 if(highlight_mode==1){//בודק שזאת לא סימולציית מחשב אלא מהלך חוקי
     int h=current_player+2;//משנה על מנת לבחור קוד צבע מנצח
     Board[row][column]=h;//מציב מספר חדש בדיסקית 
     int r;
        for(r=row+1; r<ROW && Board[r][column]==current_player; r++){//עובר שוב על הדיסקיות המנצחות לצד ימין ומציב גם להן את הערך החדש
            Board[r][column]=h;
		}
        for(r=row-1; r>=0 && Board[r][column]==current_player; r--){//מבצע את אותה פעולה לצד שמאל
            Board[r][column]=h;
		}
	 }
	 return 1;//מחזיר ניצחון
    } 

	//אלכסון ראשי
	count = 1;
	//למטה ימינה
	for (int r = row + 1, c = column + 1; r < ROW && c < COL && Board[r][c] == current_player; r++, c++) {
		count++;
	}
	//למעלה שמאלה
	for (int r = row - 1, c = column - 1; r >= 0 && c >= 0 && Board[r][c] == current_player; r--, c--) {
		count++;
	}
 if(count>=4){
    if(highlight_mode==1){
        int h=current_player+2;
        Board[row][column]=h;
        int r,c;
        for(r=row+1,c=column+1; r<ROW && c<COL && Board[r][c]==current_player; r++,c++){
            Board[r][c]=h;
		}	
        for(r=row-1,c=column-1; r>=0 && c>=0 && Board[r][c]==current_player; r--,c--){
            Board[r][c]=h;
		}	
    }
    return 1;
 }
	//אלכסון משני 
	count = 1;
	//למטה שמאלה
	for (int r = row + 1, c = column - 1; r < ROW && c >= 0 && Board[r][c] == current_player; r++, c--) {
		count++;
	}
	//למעלה ימינה
	for (int r = row - 1, c = column + 1; r>=0 && c<COL && Board[r][c] == current_player; r--,c++) {
		count++;
	}
 if(count>=4){
    if(highlight_mode==1){
        int h=current_player+2;
        Board[row][column]=h;
        int r,c;
        for(r=row-1,c=column+1; r>=0 && c<COL && Board[r][c]==current_player; r--,c++){
            Board[r][c]=h;
		}	
        for(r=row+1,c=column-1; r<ROW && c>=0 && Board[r][c]==current_player; r++,c--){
            Board[r][c]=h;
		}	
    }
    return 1;
 }
	//לא נמצאו נצחונות
	return 0;
}
//בחירת השורה הריקה בעמודה שנבחרה
int make_move(matrix Board, int column, int current_player) {
	if (column<0 || column>COL - 1) {//בדיקת עמודה חוקית
		return -2;
	}
	//מציאת השורה הריקה בעמודה
	for (int row = ROW - 1; row >= 0; row--) {//בודק מהסוף להתחלה בהתאם לחוקי המשחק
		if (Board[row][column] == 0) {
			Board[row][column] = current_player;
			return row;
		}
	}
	//העמודה מלאה
	return -1;
}
//סידור המחרוזות שנקלטו ובדיקת מקרה קיצון
void same_player_name(char *player1, char *player2) {//בדיקה שהשמות שונים במידה ולא מוסיף להם 1 או 2
	int n1 = strlen(player1);
	int n2 = strlen(player2);
	if (strcmp(player1, player2) == 0) {
		for (int i = 0; i < n1; i++) {
			if (player1[i] == '\n') {
				player1[i] = '1';
			}
		}
		for (int i = 0; i < n2; i++) {
			if (player2[i] == '\n') {
				player2[i] = '2';
			}
		}
	}
}	
void fix_string(char *player){//מוחק אנטר מהמחרוזת
	int n=strlen(player);
   for (int i = 0; i < n; i++) {
	   if (player[i] == '\n') {
	       player[i] = '\0';
	    }
    }	
}

