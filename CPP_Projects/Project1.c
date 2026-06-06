#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 10

typedef struct {
	char username[50];
	char password[50];
	int add, sub, times, divide;
} RECORD;

void registerPlayer(RECORD player);
RECORD logIn(RECORD player);
void playGame(int type);
void leaderboards();
void save();
void retrieve();
int mainMenu();
int loginMenu();
int quizMenu();
int locate(char n[]);

RECORD players[MAX];
int last = -1;
int isLoggedIn = 0;
int current = -1;

void clear() {
	printf("\033[H\033[2J");
}

void gotoxy(int x, int y) {
	printf("\033[%d;%dH", y, x);
}

void syspause() {
	printf("\nPress Enter to continue...");
	getchar();
	while(getchar() != '\n' && getchar() != EOF);
}

int main() {
	RECORD player;
	srand(time(NULL));
	retrieve();

	while(1) {
		while(!isLoggedIn) {
			clear();
			switch(loginMenu()) {
			case 1:
				printf("Input username: ");
				scanf(" %[^\n]", player.username);
				printf("Input Password: ");
				scanf(" %[^\n]", player.password);
				player = logIn(player);
				break;

			case 2:
				printf("Input username: ");
				scanf(" %[^\n]", player.username);
				printf("Input Password: ");
				scanf(" %[^\n]", player.password);
				registerPlayer(player);
				break;

			case 3:
				printf("Saving and exiting... Thank you!\n");
				save();
				exit(0);
			default:
				printf("Invalid input!! [1-3 only]\n");
				syspause();
			}
		}

		while(isLoggedIn) {
			clear();
			switch(mainMenu()) {
			case 1:
				while(1) {
					clear();
					int qChoice = quizMenu();
					if(qChoice >= 1 && qChoice <= 4) {
						playGame(qChoice);
					} else if(qChoice == 5) {
						break;
					} else {
						printf("Invalid choice!\n");
						syspause();
					}
				}
				break;
			case 2:
				leaderboards();
				break;
			case 3:
				isLoggedIn = 0;
				current = -1;
				printf("Logged out successfully.\n");
				syspause();
				break;
			case 4:
				save();
				printf("Saving and exiting... Thank you!\n");
				exit(0);
			default:
				printf("Invalid input!!\n");
				syspause();
			}
		}
	}
	return 0;
}

void registerPlayer(RECORD player) {
	if(locate(player.username) > -1) {
		printf("Username already exists!");
		syspause();
	}
	else if (last >= MAX - 1) {
		printf("Database is full!");
		syspause();
	}
	else {
		last++;
		player.add = 0;
		player.sub = 0;
		player.times = 0;
		player.divide = 0;
		players[last] = player;
		printf("Registration successful! You can now log in.\n");
		save();
		syspause();
	}
}

RECORD logIn(RECORD player) {
	int p = locate(player.username);
	if(p == -1) {
		printf("Username not found!");
		syspause();
	}
	else {
		if(strcmp(players[p].password, player.password) != 0) {
			printf("Incorrect password!!");
			syspause();
		}
		else {
			isLoggedIn = 1;
			current= p;
			printf("Login successful!\n");
			syspause();
			return players[p];
		}
	}
	return player;
}

void playGame(int type) {
	int num1, num2, ans, userAns;
	int cont = 1;
	char op;

	while(cont == 1) {
		clear();
		num1 = rand() % 50 + 1;
		num2 = rand() % 50 + 1;

		switch(type) {
		case 1:
			op = '+';
			ans = num1 + num2;
			break;
		case 2:
			op = '-';
			if(num2 > num1) {
				int temp = num1;
				num1 = num2;
				num2 = temp;
			}
			ans = num1 - num2;
			break;
		case 3:
			op = '/';
			ans = rand() % 12 + 1;
			num2 = rand() % 12 + 1;
			num1 = ans * num2;
			break;
		case 4:
			op = '*';
			num1 = rand() % 12 + 1;
			num2 = rand() % 12 + 1;
			ans = num1 * num2;
			break;
		}

		printf("--- QUIZ ---\n");
		printf("What is %d %c %d?\n", num1, op, num2);
		printf("Your Answer: ");
		scanf("%d", &userAns);

		if(userAns == ans) {
			printf("Correct!\n");
			if(type == 1) players[current].add++;
			if(type == 2) players[current].sub++;
			if(type == 3) players[current].divide++;
			if(type == 4) players[current].times++;
		} else {
			printf("Wrong! The correct answer was %d.\n", ans);
		}

		printf("\nDo you want to continue? (1 for Yes, 0 for No): ");
		scanf("%d", &cont);
	}

	save();
	leaderboards();
}
void leaderboards() {
	clear();

	int totals[MAX];
	int order[MAX];
	for(int i = 0; i <= last; i++) {
		totals[i] = players[i].add + players[i].sub + players[i].times + players[i].divide;
		order[i] = i; 
	}

	for(int i = 0; i <= last - 1; i++) {
		for(int j = 0; j <= last - i - 1; j++) {
			if(totals[order[j]] < totals[order[j+1]]) {
				int temp = order[j];
				order[j] = order[j+1];
				order[j+1] = temp;
			}
		}
	}

	gotoxy(15, 2);
	printf("- - - - - LEADERBOARDS - - - - -");

	gotoxy(2, 4);
	printf("Rank");
	gotoxy(10, 4);
	printf("Username");
	gotoxy(25, 4);
	printf("Add");
	gotoxy(32, 4);
	printf("Sub");
	gotoxy(39, 4);
	printf("Mul");
	gotoxy(46, 4);
	printf("Div");
	gotoxy(53, 4);
	printf("Total");

	int y = 6;
	for(int i = 0; i <= last; i++) {
		int index = order[i];
		gotoxy(2, y);
		printf("%d", i + 1);
		gotoxy(10, y);
		printf("%s", players[index].username);
		gotoxy(25, y);
		printf("%d", players[index].add);
		gotoxy(32, y);
		printf("%d", players[index].sub);
		gotoxy(39, y);
		printf("%d", players[index].times);
		gotoxy(46, y);
		printf("%d", players[index].divide);
		gotoxy(53, y);
		printf("%d", totals[index]);
		y++;
	}

	printf("\n\n\n- - - VISUAL STANDINGS - - -\n\n");
	for(int i = 0; i <= last; i++) {
		int index = order[i];

		printf("%s", players[index].username);

		for(int j = 0; j < totals[index]; j++) {
			printf("-");
		}
		
		printf(">%dpoints\n", totals[index]);
	}

	printf("\n");
	syspause();
}
void save() {
	FILE *fp = fopen("game_data.dat", "wb");
	if(fp != NULL) {
		fwrite(&last, sizeof(int), 1, fp);
		if(last >= 0) {
			fwrite(players, sizeof(RECORD), last + 1, fp);
		}
		fclose(fp);
	}
}

void retrieve() {
	FILE *fp = fopen("game_data.dat", "rb");
	if(fp != NULL) {
		fread(&last, sizeof(int), 1, fp);
		if(last >= 0) {
			fread(players, sizeof(RECORD), last + 1, fp);
		}
		fclose(fp);
	}
}

int mainMenu() {
	int ch;
	printf("MAIN MENU (Logged in as: %s)\n", players[current].username);
	printf("[1] Start Quiz\n");
	printf("[2] Show Leaderboards\n");
	printf("[3] Logout\n");
	printf("[4] Exit\n");
	printf("Input your choice: ");
	scanf("%d", &ch);
	return ch;
}

int quizMenu() {
	int ch;
	printf("QUIZ MENU\n");
	printf("[1] Addition Quiz\n");
	printf("[2] Subtraction Quiz\n");
	printf("[3] Division Quiz\n");
	printf("[4] Multiplication Quiz\n");
	printf("[5] Return to Main Menu\n");
	printf("Input your choice: ");
	scanf("%d", &ch);
	return ch;
}

int loginMenu() {
	int ch;
	printf("LOGIN MENU\n");
	printf("[1] Log in\n");
	printf("[2] Register\n");
	printf("[3] Exit\n");
	printf("Input your choice: ");
	scanf("%d", &ch);
	return ch;
}

int locate(char n[]) {
	int i;
	for(i = 0; i<=last; i++) {
		if(strcmp(players[i].username, n) == 0)
			return i;
	}
	return -1;
}
