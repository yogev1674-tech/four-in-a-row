#include"game.h"
void PvC(int *games_played,int *draws,int *p2_wins, int *p1_wins) {
	matrix Board = { 0 };
	int current_player = p1, moves = 0;
	//משתני סטטיסטיקות
	char *player1 = (char*)malloc(21 * sizeof(char));
	assert(player1);
	int level;
	printf("Enter level of difficulty:\npress 1 for easy or 2 for medium:");
	scanf_s("%d", &level);
	getchar();//\nשהבאפר לא יקלוט את ה 
	printf("Plese enter player name:");
	fgets( player1,21,stdin);
	printf("\n");
	
	fix_string(player1);//נפתר מהאנטר
	printf("Wellcome to Four in a row game %s!\n", player1);
	printf("\n");
	draw_board(Board);
	while (moves < ROW * COL) {//רץ ככמות המהלכים האפשריים
		int column, row;
		if (current_player == p1) {
			printf("%s, plese choose column:", player1);
			scanf_s("%d", &column);
			column--;//לנרמל
			row = make_move(Board, column, current_player);// בוחר שורה פנויה בעמודה שנבחרה
			if (row ==-1) {
				printf("Invalid move,the column you chose is full %s plese try agin\n", player1);
				continue;
			}
			else if(row== -2) {
				printf("Invalid move, please choose a column between 1 to 7 %s plese try agin\n", player1);
				continue;
			}
		}
		  //לפי בחירת הרמה מחשב מהלך מחשב
		else {
			if (level == 1) {
				column = PC_move_easy(Board);
				//אין עמודות פנויות
				if (column == -1) {
					break;
				}
				row = make_move(Board, column, current_player);//מבצע את ההצבה בשורה
			}
			else if (level == 2){		
				column = PC_move_medium(Board);
				//אין עמודות פנויות
				if (column == -1) {
					break;
				}
				row = make_move(Board, column, current_player);//מבצע הצבה בשורה רמה קשה יותר
			}
			animate_fall(Board, column, row, current_player);//קריאה לאנימצית נפילה לאחר כל מהלך חוקי שהוא לא ניצחון וציור הלוח
		    printf("The computer chose column %d\n", column+1);
		}
		moves++;//קידום מונה מהלכים
		if (check_winner(Board, row, column, current_player,1)) {//אם זוהה ניצחון
			(*games_played)++;//מעדכן ערך פויינטר עבור סטטיסטיקה
			if (current_player == p1) {
				(*p1_wins)++;//מעדכן ערך פויינטר עבור סטטיסטיקה
				draw_board(Board);//ציור הלוח בעת ניצחון כולל הדגשת שורה מנצחת
				printf("Congratulation %s , you are the winner!!!\n", player1);
			}
			else {
				(*p2_wins)++;//מעדכן ערך פויינטר עבור סטטיסטיקה
				draw_board(Board);//ציור הלוח בעת ניצחון כולל הדגשת שורה מנצחת
				printf("The computer won! Better luck next time %s.\n", player1);
			}
			printf("Press ENTER to return to menu...");
			getchar();
			getchar();
			return;
		}
			current_player = (current_player == 1)  ? p2 : p1;
	}
	(*games_played)++;// מעדכן ערך פויינטר עבור סטטיסטיקה במקרה שיוויון
	(*draws)++;// מעדכן ערך פויינטר עבור סטטיסטיקה במקרה שוויון
	free(player1);
	draw_board(Board);//ציור הלוח במקרה שוויון
	printf("The game ended in a draw!\n");
	return;
}
//easy mode
//בחירת העמודה הראשונה הפנויה תור מחשב
int PC_move_easy(matrix Board) {
	for (int c = 0; c < COL; c++) {
		if (Board[0][c] == 0) {
			return c;
		}
	}
	return -1;
}
//medium mode
//האם אפשר להכניס פה מהלך
int is_column_available(matrix Board, int column) {
	return Board[0][column] == 0;
}
//סימולציה ובדיקת ניצחון
int sim_and_check_win(matrix Board, int column, int current_player) {
	int row = make_move(Board, column, current_player);//בוחר שורה רנדומלית
	if (row < 0) {//רואה שהיא חוקית
		return 0;
	}
	int win = check_winner(Board, row, column, current_player,0);//אם החזיר עמודה חוקית וגם שורה מנצחת שומר אותה
	Board[row][column] = 0;//כאן החלק של הסימולציה מתבצע החזיר את הערכים אחורה כאילו לא התבצע מהלך
	return win;//מחזיר שורה מנצחת
}
//בחירת עמודה לפי אסטרטגיה
int PC_move_medium(matrix Board) {
	int c;
	for (c = 0; c < COL; c++) {
		if (is_column_available(Board, c)) {//בודק עבור כל עמודה האם היא פנויה
			if (sim_and_check_win(Board, c, p2)) {//אם השורה פנויה מריץ סימולציה של בדיקת ניצחון אם קיבל ניצחון יחזיר אותה
				return c;
			}
		}
	}
	for (c = 0; c < COL; c++) {
		if (is_column_available(Board, c)) {//בודק את אותו תנאי עבור היריב
			if (sim_and_check_win(Board, c, p1)) {//בודק אם יש לו עמודה שתיתן לו ניצחון ואם כן חוסם אותה
				return c;
			}
		}
	}
	return PC_move_easy(Board);//אם אף אחד מהתנאים לא מתקיים בוחר בעמודה הראשונה שפנויה
}
