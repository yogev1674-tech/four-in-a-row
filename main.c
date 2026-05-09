#include"game.h"
int main() {
	//כאן מתבצע הגדרת תפריט בחירה של מצבי משחק שונים בעצם הפונקציה הראשית מתפקדת כבורר מצבי משחק
	printf("\n");
	printf("=====================================\n");
	printf("      %sFOUR IN A ROW%s\n", YELLOW, RESET);
	printf("=====================================\n");
	printf("Created by: %sYogev Ohayon & Liav Dimri%s\n", RED, RESET);
	printf("HIT 2025-2026\n");
	printf("Computer Science Department\n");
	printf("=====================================\n\n");
	int num,games_played=0,draws=0,p2_wins=0, p1_wins = 0;
	while(1){
		printf("=====================================\n");
		printf("               GAME MENU                \n");
		printf("=====================================\n\n");
		printf("  1) Player vs Player\n");
		printf("  2) Player vs Computer\n");
		printf("  3) Statistics\n");
		printf("  4) Exit\n\n");
		printf(" Choose an option (1-4): ");
		scanf_s("%d", &num);
	
		if (num == 1) {
			PvP(&games_played, &draws, &p2_wins, &p1_wins);
		}
		else if (num == 2) {
			PvC(&games_played, &draws, &p2_wins, &p1_wins);
		}
		else if (num == 3) {
			print_statistics(games_played, draws, p2_wins, p1_wins);
		}
		else if (num == 4) {
			break;
		}
		else {
			printf("Invalid input!\n");
		}
	}
	return 0;
}
void print_statistics(int games_played, int draws, int p2_wins, int p1_wins) {
	//הדפסת נתוני סטטיסטיקות
	printf("\n");
	printf("+-----------------------------+\n");
	printf("|       STATISTICS BOARD      |\n");
	printf("+-----------------------------+\n");
	printf("| Games played : %2d          |\n", games_played);
	printf("| Player 1 wins: %2d          |\n", p1_wins);
	printf("| Player 2 wins: %2d          |\n", p2_wins);
	printf("| Draws        : %2d          |\n", draws);
	printf("+-----------------------------+\n");
}

