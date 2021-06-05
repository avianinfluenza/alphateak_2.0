#include<bits/stdc++.h>
#include<windows.h> 
#include<conio.h>

// Ű���� �� 
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define ENTER 4
using namespace std;
int dx[121] = {0, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -3, -3, -3, -3, -3, -3, -3, -3,
-3, -3, -3, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4,
 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
int dy[121] = {0, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, -5, -4
, -3, -2, -1, 0, 1, 2, 3, 4, 5, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, -5, -4, -3, -2, -1, 1, 2, 3, 4, 5, -5, -4, -3,
-2, -1, 0, 1, 2, 3, 4, 5, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, -5, -4, -3, -2, -1
, 0, 1, 2, 3, 4, 5, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
int board[1742621][16][16]={},cnt=1;
long long int score[1742621], im = -10000000000, AI[10] = {0, 1, 100, 10000, 1000000, 100000000, 100000000, 100000000, 100000000, 100000000};

void input();

int tree(void){
	int i, temp = -1, s;
	for(i = 120+14401; i <= 1728000+120+14400; i++){
		if(score[i/120] == im){
			i+=119;
			continue;
		}
		score[i/120] = max(score[i/120], score[i]);
	}
	for(i = 121; i <= 120+14400; i++){
		if(score[i] == im){
			continue;
		}
		score[i/120] = min(score[i/120], score[i]);
	}
	s = im -1;
	for(i = 1; i <= 120; i++){
		if(score[i] >= s){
			temp = i;
			s = score[i];
		}
	}
	return temp;
}

// �� �Լ� ����ؾ��� �� : �� ����, �ֱٿ� �� �� ��ó�� �ִ� �� �� 
int sc(int index){		//���Լ� �÷��̾�(1) ���� �����Ҷ��� ����, AI(2)���� �����Ҷ��� ��� 
	int i, j, s = 0,temp, tf; 
	for(i = 1; i <= 15; i++){	//AI���� ���� ���� ����� �� ��� 
		temp = 0; tf = 0;
		for(j = 1; j <= 15; j++){
			if(board[index][i][j] == 2){
				temp++;
				tf = 1;
			}
			else{
				if(tf == 1){
					s += AI[temp];
					temp = 0;
					tf = 0;
				}
			}
		}
		if(tf == 1){
			s += AI[temp];
			temp = 0;
			tf = 0;
		}
		temp = 0; tf = 0;
		for(j = 1; j <= 15; j++){
			if(board[index][j][i] == 2){
				temp++;
				tf = 1;
			}
			else{
				if(tf == 1){
					s += AI[temp];
					temp = 0;
					tf = 0;
				}
			}
		}
		if(tf == 1){
			s += AI[temp];
			temp = 0;
			tf = 0;
		}
	}
	for(i = 1; i <= 15; i++){	//�÷��̾���� ���� ���� ����� �� ���, �÷��̾�� �ΰ����ɺ��� ����ġ 2 ��  
		temp = 0; tf = 0;
		for(j = 1; j <= 15; j++){
			if(board[index][i][j] == 1){
				temp++;
				tf = 1;
			}
			else{
				if(tf == 1){
					s -= AI[temp]*4;
					if(temp >= 3){
						if(board[index][i][j] == 2){
							s += AI[temp]*3;
						}
						if(j-temp-1 > 0){
							if(board[index][i][j-temp-1] == 2){
								s += AI[temp]*3;
							}
						}
					}
					temp = 0;
					tf = 0;
				}
			}
		}
		if(tf == 1){
			s -= 4*AI[temp];
			temp = 0;
			tf = 0;
		}
		temp = 0; tf = 0;
		for(j = 1; j <= 15; j++){
			if(board[index][j][i] == 1){
				temp++;
				tf = 1;
			}
			else{
				if(tf == 1){
					s -= AI[temp]*4;
					if(temp >= 3){
						if(board[index][j][i] == 2){
							s += AI[temp]*3;
						}
						if(j-temp-1 > 0){
							if(board[index][j-temp-1][i] == 2){
								s += AI[temp]*3;
							}
						}
					}					
					temp = 0;
					tf = 0;
				}
			}
		}
		if(tf == 1){
			s -= 2*AI[temp];
			temp = 0;
			tf = 0;
		}
	}
	for(i = 1; i <= 15; i++){	//AI���� �밢�� ���(���� �ƴ�) 
		temp = 0; tf = 0;
		for(j = 1; j <= i; j++){
			if(board[index][16-j][i+1-j] == 2){
				temp++;
				tf = 1;
			}
			else{
				if(tf == 1){
					s += AI[temp];
					temp = 0;
					tf = 0;
				}
			}
		}
		temp = 0; tf = 0;
		for(j = 1; j <= i; j++){
			if(board[index][j][15-i+j] == 2){
				temp++;
				tf = 1;
			}
			else{
				if(tf == 1){
					s += AI[temp];
					temp = 0;
					tf = 0;
				}
			}
		}		
	}	
	for(i = 1; i <= 15; i++){	//AI���� �밢�� ���(���� �ƴ�) 
		temp = 0; tf = 0;
		for(j = 1; j <= i; j++){
			if(board[index][16-j][15-i+j] == 2){
				temp++;
				tf = 1;
			}
			else{
				if(tf == 1){
					s += AI[temp];
					temp = 0;
					tf = 0;
				}
			}
		}
		if(tf == 1){
			s += AI[temp];
			temp = 0;
			tf = 0;
		}
		temp = 0; tf = 0;
		for(j = 1; j <= i; j++){
			if(board[index][j][i-j+1] == 2){
				temp++;
				tf = 1;
			}
			else{
				if(tf == 1){
					s += AI[temp];
					temp = 0;
					tf = 0;
				}
			}
		}
		if(tf == 1){
			s += AI[temp];
			temp = 0;
			tf = 0;
		}		
	}
	for(i = 1; i <= 15; i++){	//player���� �밢�� ���(���� �ƴ�) 
		temp = 0; tf = 0;
		for(j = 1; j <= i; j++){
			if(board[index][16-j][i+1-j] == 1){
				temp++;
				tf = 1;
			}
			else{
				if(tf == 1){
					s -= AI[temp]*4;
					if(temp >= 3){
						if(board[index][16-j][i+1-j] == 2){
							s += AI[temp]*3;
						}
						if(i+1-j+temp+1 < 15 && 16-j+temp+1 < 15){
							if(board[index][16-j+temp+1][i+1-j+temp+1] == 2){
								s += AI[temp]*3;
							}
						}
					}
					temp = 0;
					tf = 0;
				}
			}
		}
		if(tf == 1){
			s -= AI[temp]*2;
			temp = 0;
			tf = 0;
		}
		temp = 0; tf = 0;
		for(j = 1; j <= i; j++){
			if(board[index][j][15-i+j] == 1){
				temp++;
				tf = 1;
			}
			else{
				if(tf == 1){
					s -= AI[temp]*4;
					if(temp >= 3){
						if(board[index][j][15-i+j] == 2){
							s += AI[temp]*3;
						}
						if(15-i+j-temp-1 > 0 && j-temp-1 > 0){
							if(board[index][j-temp-1][15-i+j-temp-1] == 2){
								s += AI[temp]*3;
							}
						}
					}
					temp = 0;
					tf = 0;
				}
			}
		}
		if(tf == 1){
			s -= AI[temp]*2;
			temp = 0;
			tf = 0;
		}		
	}	
	for(i = 1; i <= 15; i++){	//player���� �밢�� ���(���� �ƴ�)
		temp = 0; tf = 0;
		for(j = 1; j <= i; j++){
			if(board[index][16-j][15-i+j] == 1){
				temp++;
				tf = 1;
			}
			else{
				if(tf == 1){
					s -= AI[temp]*4;
					if(temp >= 3){
						if(board[index][16-j][15-i+j] == 2){
							s += AI[temp]*3;
						}
						if(15-i+j-temp-1 > 0 && 16-j+temp+1 < 15){
							if(board[index][16-j+temp+1][15-i+j-temp-1] == 2){
								s += AI[temp]*3;
							}
						}
					}
					temp = 0;
					tf = 0;
				}
			}
		}
		if(tf == 1){
			s -= AI[temp]*2;
			temp = 0;
			tf = 0;
		}
		temp = 0; tf = 0;
		for(j = 1; j <= i; j++){
			if(board[index][j][i-j+1] == 1){
				temp++;
				tf = 1;
			}
			else{
				if(tf == 1){
					s -= AI[temp]*4;
					if(temp >= 3){
						if(board[index][j][i+1-j] == 2){
							s += AI[temp]*3;
						}
						if(i+1-j+temp+1 < 15 && j-temp-1 > 0){
							if(board[index][j-temp-1][i+1-j+temp+1] == 2){
								s += AI[temp]*3;
							}
						}
					}
					temp = 0;
					tf = 0;
				}
			}
		}
		if(tf == 1){
			s -= AI[temp]*4;
			temp = 0;
			tf = 0;
		}		
	}
	return s;
}

int scme(int index){
	int i, j, s = 0,temp, tf;
	int x = board[index][0][0];
	int y = board[index][0][1];
	//���Լ� �÷��̾�(1) ���� �����Ҷ��� ����, AI(2)���� �����Ҷ��� ���
	////////////////////////////////////////�÷��̾� ����////////////////////////////////////////
	temp = 0; tf = 0;			
	for(i = -4; i < 5; i++){	//�÷��̾�(1) x+- 
		if(x+i < 1 || x+i > 15){
			continue;	
		}
		if(board[index][x+i][y] == 1){
			tf = 1;
			temp++;
		}
		else{
			tf = 0;
			temp = 0;
			s -= AI[temp]*2;
			if(x+i-temp-1 >= 1 && board[index][x+i-temp-1][y] == 2){
				s += AI[temp]*3;
			}
			if(board[index][x+i][y] == 2){
				s += AI[temp]*3;
			}
		}
	}
	if(tf == 1){
		tf = 0;
		temp = 0;
		s -= AI[temp]*2;
		if(x+i-temp-1 >= 1 && board[index][x+i-temp-1][y] == 2){
			s += AI[temp]*3;
		}
		if(x+i <= 15 && board[index][x+i][y] == 2){
			s += AI[temp]*3;
		}
	}
	
	temp = 0; tf = 0;
	for(i = -4; i < 5; i++){	//�÷��̾�(1) y+- 
		if(y+i < 1 || y+i > 15){
			continue;	
		}
		if(board[index][x][y+i] == 1){
			tf = 1;
			temp++;
		}
		else{
			tf = 0;
			temp = 0;
			s -= AI[temp]*2;
			if(y+i-temp-1 >= 1 && board[index][x][y+i-temp-1] == 2){
				s += AI[temp]*3;
			}
			if(board[index][x][y+i] == 2){
				s += AI[temp]*3;
			}
		}
	}
	if(tf == 1){
		tf = 0;
		temp = 0;
		s -= AI[temp]*2;
		if(y+i-temp-1 >= 1 && board[index][x][y+i-temp-1] == 2){
			s += AI[temp]*3;
		}
		if(y+i <= 15 && board[index][x][y+i] == 2){
			s += AI[temp]*3;
		}
	}
	
	temp = 0; tf = 0;
	for(i = -4; i < 5; i++){	//�÷��̾�(1) x+- y+- 
		if(y+i < 1 || y+i > 15 || x+i < 1 || x+i > 15){
			continue;	
		}
		if(board[index][x+i][y+i] == 1){
			tf = 1;
			temp++;
		}
		else{
			tf = 0;
			temp = 0;
			s -= AI[temp]*3;
			if(y+i-temp-1 >= 1 && x+i-temp-1 >= 1 && board[index][x+i-temp-1][y+i-temp-1] == 2){
				s += AI[temp]*4;
			}
			if(board[index][x+i][y+i] == 2){
				s += AI[temp]*4;
			}
		}
	}
	if(tf == 1){
		tf = 0;
		temp = 0;
		s -= AI[temp]*3;
		if(y+i-temp-1 >= 1 && x+i-temp-1 >= 1 && board[index][x+i-temp-1][y+i-temp-1] == 2){
			s += AI[temp]*4;
		}
		if(y+i <= 15 && x+i <= 15 && board[index][x+i][y+i] == 2){
			s += AI[temp]*4;
		}
	}
	
	temp = 0; tf = 0;
	for(i = -4; i < 5; i++){	//�÷��̾�(1) x+- y+- 
		if(y+i < 1 || y+i > 15 || x-i < 1 || x-i > 15){
			continue;	
		}
		if(board[index][x-i][y+i] == 1){
			tf = 1;
			temp++;
		}
		else{
			tf = 0;
			temp = 0;
			s -= AI[temp]*3;
			if(y+i-temp-1 >= 1 && x-i+temp+1 >= 1 && board[index][x-i+temp+1][y+i-temp-1] == 2){
				s += AI[temp]*4;
			}
			if(board[index][x-i][y+i] == 2){
				s += AI[temp]*4;
			}
		}
	}
	if(tf == 1){
		tf = 0;
		temp = 0;
		s -= AI[temp]*3;
		if(y+i-temp-1 >= 1 && x-i+temp+1 >= 1 && board[index][x-i+temp+1][y+i-temp-1] == 2){
			s += AI[temp]*4;
		}
		if(y+i <= 15 && x-i >= 1 && board[index][x-i][y+i] == 2){
			s += AI[temp]*4;
		}
	}
	////////////////////////////////////////�÷��̾� ����////////////////////////////////////////
	
	////////////////////////////////////////AI ����////////////////////////////////////////
	/*
	temp = 0; tf = 0;			
	for(i = -4; i < 5; i++){	//�÷��̾�(1) x+- 
		if(x+i < 1 || x+i > 15){
			continue;	
		}
		if(board[index][x+i][y] == 2){
			tf = 1;
			temp++;
		}
		else{
			tf = 0;
			temp = 0;
			s += AI[temp];
			if(x+i-temp-1 >= 1 && board[index][x+i-temp-1][y] == 1){
				s -= AI[temp]*2;
			}
			if(board[index][x+i][y] == 1){
				s -= AI[temp]*2;
			}
		}
	}
	if(tf == 1){
		tf = 0;
		temp = 0;
		s += AI[temp];
		if(x+i-temp-1 >= 1 && board[index][x+i-temp-1][y] == 1){
			s -= AI[temp]*2;
		}
		if(x+i <= 15 && board[index][x+i][y] == 1){
			s -= AI[temp]*2;
		}
	}
	
	temp = 0; tf = 0;
	for(i = -4; i < 5; i++){	//�÷��̾�(1) y+- 
		if(y+i < 1 || y+i > 15){
			continue;	
		}
		if(board[index][x][y+i] == 1){
			tf = 1;
			temp++;
		}
		else{
			tf = 0;
			temp = 0;
			s += AI[temp];
			if(y+i-temp-1 >= 1 && board[index][x][y+i-temp-1] == 1){
				s -= AI[temp]*2;
			}
			if(board[index][x][y+i] == 2){
				s -= AI[temp]*2;
			}
		}
	}
	if(tf == 1){
		tf = 0;
		temp = 0;
		s += AI[temp];
		if(y+i-temp-1 >= 1 && board[index][x][y+i-temp-1] == 1){
			s -= AI[temp]*2;
		}
		if(y+i <= 15 && board[index][x][y+i] == 1){
			s -= AI[temp]*2;
		}
	}
	
	temp = 0; tf = 0;
	for(i = -4; i < 5; i++){	//�÷��̾�(1) x+- y+- 
		if(y+i < 1 || y+i > 15 || x+i < 1 || x+i > 15){
			continue;	
		}
		if(board[index][x+i][y+i] == 2){
			tf = 1;
			temp++;
		}
		else{
			tf = 0;
			temp = 0;
			s += AI[temp]*2;
			if(y+i-temp-1 >= 1 && x+i-temp-1 >= 1 && board[index][x+i-temp-1][y+i-temp-1] == 1){
				s -= AI[temp]*3;
			}
			if(board[index][x+i][y+i] == 1){
				s -= AI[temp]*3;
			}
		}
	}
	if(tf == 1){
		tf = 0;
		temp = 0;
		s += AI[temp]*2;
		if(y+i-temp-1 >= 1 && x+i-temp-1 >= 1 && board[index][x+i-temp-1][y+i-temp-1] == 1){
			s -= AI[temp]*3;
		}
		if(y+i <= 15 && x+i <= 15 && board[index][x+i][y+i] == 1){
			s -= AI[temp]*3;
		}
	}
	
	temp = 0; tf = 0;
	for(i = -4; i < 5; i++){	//�÷��̾�(1) x+- y+- 
		if(y+i < 1 || y+i > 15 || x-i < 1 || x-i > 15){
			continue;	
		}
		if(board[index][x-i][y+i] == 1){
			tf = 1;
			temp++;
		}
		else{
			tf = 0;
			temp = 0;
			s += AI[temp]*2;
			if(y+i-temp-1 >= 1 && x-i+temp+1 >= 1 && board[index][x-i+temp+1][y+i-temp-1] == 2){
				s -= AI[temp]*3;
			}
			if(board[index][x-i][y+i] == 2){
				s -= AI[temp]*3;
			}
		}
	}
	if(tf == 1){
		tf = 0;
		temp = 0;
		s += AI[temp]*2;
		if(y+i-temp-1 >= 1 && x-i+temp+1 >= 1 && board[index][x-i+temp+1][y+i-temp-1] == 2){
			s -= AI[temp]*3;
		}
		if(y+i <= 15 && x-i >= 1 && board[index][x-i][y+i] == 2){
			s -= AI[temp]*3;
		}
	}
	*/
	////////////////////////////////////////AI ����////////////////////////////////////////
	
	return s;
}


void copy(int a, int b){	//b ���忡 a���带 ������  
	int i, j;
	for(i = 1; i <= 15; i++){
		for(j = 1; j<= 15;j++){
			board[b][i][j] = board[a][i][j]; 
		}
	}
}

int key(){	//Ű �Է� �Լ� 
	int key;
	key=getch();
	if(key==72) return UP; // ����Ű �� 
	else if(key==80) return DOWN; // ����Ű �Ʒ� 
	else if(key==13) return ENTER; // ����Ű 
} 
void xy(int x, int y){	// x,y ��ǥ���� 
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}
void init(){  //ũ��� Ŀ�� ����� ���� 
	system("title OMOK BOT");
	system("mode con cols=53 lines=15"); 
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle,&ConsoleCursor);
}
void titleDraw(){ //Ÿ��Ʋ
	puts("           #####   #     #   #####   #    # ");
 	puts("          #     #  ##   ##  #     #  #   #  ");
	puts("          #     #  # # # #  #     #  #  #   ");
	puts("          #     #  #  #  #  #     #  ###    ");
	puts("          #     #  #     #  #     #  #  #   ");
	puts("          #     #  #     #  #     #  #   #  ");
	puts("           #####   #     #   #####   #    # ");

}
int menuDraw(){	// ���� 
	int x=23;
	int y=10;
	xy(x-2,y);
	printf("> ���ӽ���");
	xy(x,y+2);
	printf("  ���� ");
	while(1){
		int n=key();
		switch(n){
			case UP: {
				if(y> 10){
					xy(x-2,y);
					printf(" ");
					xy(x-2,y-=2);
					printf(">");
				}
				break;
			}
			
			case DOWN: {
				if(y<12){
					xy(x-2,y);
					printf(" ");
					xy(x-2,y+=2);
					printf(">");
				}
				break;
			}
			
			case ENTER: {
				return y-10;
			}
		}
		
	}
}

void re(){ //�ٽ��ϱ� �Է¹޴� �Լ�
	char a;
	while(1){
	cin >> a;
	if(a=='Y'||a=='y'){
		system("cls");
		for(int i=0;i<16;i++){
			for(int j=0;j<16;j++){
				board[0][i][j]=0;
			}
		}
		cnt=1;
		puts("0 1 2 3 4 5 6 7 8 9 A B C D E F");
		puts("1 - - - - - - - - - - - - - - -");
		puts("2 - - - - - - - - - - - - - - -");
		puts("3 - - - - - - - - - - - - - - -");
		puts("4 - - - - - - - - - - - - - - -");
		puts("5 - - - - - - - - - - - - - - -");
		puts("6 - - - - - - - - - - - - - - -");
		puts("7 - - - - - - - - - - - - - - -");
		puts("8 - - - - - - - - - - - - - - -");
		puts("9 - - - - - - - - - - - - - - -");
		puts("A - - - - - - - - - - - - - - -");
		puts("B - - - - - - - - - - - - - - -");
		puts("C - - - - - - - - - - - - - - -");
		puts("D - - - - - - - - - - - - - - -");
		puts("E - - - - - - - - - - - - - - -");
		puts("F - - - - - - - - - - - - - - -");
		return ;
	}
	else if(a=='N'||a=='n'){
		exit(0);
	}
	else cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���: ";
	}
}

void input(){	// �÷���
	system("mode con cols=45 lines=17"); // ũ�� ���� 
    system("cls");
	int k=0,t=1,cnt1=0,x,y, temp;
	puts("0 1 2 3 4 5 6 7 8 9 A B C D E F");
	puts("1 - - - - - - - - - - - - - - -");
	puts("2 - - - - - - - - - - - - - - -");
	puts("3 - - - - - - - - - - - - - - -");
	puts("4 - - - - - - - - - - - - - - -");
	puts("5 - - - - - - - - - - - - - - -");
	puts("6 - - - - - - - - - - - - - - -");
	puts("7 - - - - - - - - - - - - - - -");
	puts("8 - - - - - - - - - - - - - - -");
	puts("9 - - - - - - - - - - - - - - -");
	puts("A - - - - - - - - - - - - - - -");
	puts("B - - - - - - - - - - - - - - -");
	puts("C - - - - - - - - - - - - - - -");
	puts("D - - - - - - - - - - - - - - -");
	puts("E - - - - - - - - - - - - - - -");
	puts("F - - - - - - - - - - - - - - -");
	while(1){
		if(cnt%2!=0) cout << "Player 1�� ������ġ�� �Է����ּ���: ";
		while(1){
			cin >> x >> y;
			if(x<0||x>15||y<0||y>15||board[0][x][y]!=0) cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���: ";
			else break;
		}
		if(cnt%2!=0){
			temp = -1;
			board[0][x][y]=1; //player1 ����, board[0]�� ��Ʈ���
			board[0][0][0] = x;
			board[0][0][1] = y;
			score[0] = sc(0);
			if(score[0] < -50000000){
				for(int i=0;i<16;i++){
					for(int j=0;j<16;j++){
						if(i==0){           //������ ��ȣ ���
							printf("%X ", k);
							k++;
							continue;
						}
						if(j==0){           //������ ��ȣ ���
							printf("%X ", t);
							t++;
							continue;
						}
						if(board[0][i][j]==0) cout << "- ";
						else if(board[0][i][j]==1) cout << "O ";
						else if(board[0][i][j]==2) cout << "X ";
					}
					puts("");
				}				
				printf("player�� �¸��Դϴ�!");
				re(); 
			}
			for(int i = 1; i <= 120; i++){		//����� �� Ʈ���� ���� 
				copy(0, i);
				if(x+dx[i] < 0 || x+dx[i] > 15 || y+dy[i] < 0 || y+dy[i] > 15){
					score[i] = im;	//���߿� ���� ���(�̴ϸƽ� �˰���)�� ����Ҷ� ��ܷ� ������ ����
					for(int j = 1; j <= 120; j++){
						score[i*120+j] = im;
						for(int k = 1; k <= 120; k++){
							score[(i*120+j)*120+k] = im;
						}
					}
				}
				else if(board[i][x + dx[i]][y + dy[i]] != 0){		//�̹� ���� �ִ� ��� 
					score[i] = im;	//���߿� ���� ���(�̴ϸƽ� �˰���)�� ����Ҷ� ��ܷ� ������ ����
					for(int j = 1; j <= 120; j++){
						score[i*120+j] = im;
						for(int k = 1; k <= 120; k++){
							score[(i*120+j)*120+k] = im;
						}
					}
				}
				else{
					board[i][x+dx[i]][y+dy[i]] = 2;
					board[i][0][0] = x+dx[i];
					board[i][0][1] = y+dy[i];
					score[i] = score[0] + scme(i);
					for(int j = 1; j <= 120; j++){
						copy(i,120*i+j);
						if(x+dx[i]+dx[j] < 0 || x+dx[i]+dx[j] > 15 || y+dy[i]+dy[j] < 0 || y+dy[i]+dy[j] > 15){
							score[i*120+j] = im;	//���߿� ���� ���(�̴ϸƽ� �˰���)�� ����Ҷ� ��ܷ� ������ ����
							for(int k = 1; k <= 120; k++){
								score[(i*120+j)*120+k] = im;
							}
						}
						else if(board[i*120+j][x+dx[i]+dx[j]][y+dy[i]+dy[j]] != 0){		//�̹� ���� �ִ� ��� 
							score[i*120+j] = im;	//���߿� ���� ���(�̴ϸƽ� �˰���)�� ����Ҷ� ��ܷ� ������ ����
							for(int k = 1; k <= 120; k++){
								score[(i*120+j)*120+k] = im;
							}
						}
						else{
							board[i*120+j][x+dx[i]+dx[j]][y+dy[i]+dy[j]] = 1;
							board[i*120+j][0][0] = x+dx[i]+dx[j];
							board[i*120+j][0][1] = y+dy[i]+dy[j];
							score[i*120+j] = score[i] + scme(i*120+j);
							for(int k = 1; k <= 120; k++){
								copy(i*120+j, (i*120+j)*120+k);
								if(x+dx[i]+dx[j]+dx[k] > 15 || x+dx[i]+dx[j]+dx[k] < 0 || y+dy[i]+dy[j]+dy[k] > 15 || y+dy[i]+dy[j]+dy[k] < 0){
									score[(i*120+j)*120+k] = im;	//���߿� ���� ���(�̴ϸƽ� �˰���)�� ����Ҷ� ��ܷ� ������ ����
								}
								else if(board[(i*120+j)*120+k][x+dx[i]+dx[j]+dx[k]][y+dy[i]+dy[j]+dy[k]] != 0){		//�̹� ���� �ִ� ��� 
									score[(i*120+j)*120+k] = im;	//���߿� ���� ���(�̴ϸƽ� �˰���)�� ����Ҷ� ��ܷ� ������ ����
								}
								else{
									board[(i*120+j)*120+k][x+dx[i]+dx[j]+dx[k]][y+dy[i]+dy[j]+dy[k]] = 2;
									board[(i*120+j)*120+k][0][0] =  x+dx[i]+dx[j]+dx[k];
									board[(i*120+j)*120+k][0][1] =  y+dy[i]+dy[j]+dy[k];
									score[(i*120+j)*120+k] = score[i*120+j] + sc((i*120+j)*120+k);
								}
							}
						}
					}
				}
			}
		}
		for(int i = 1; i <= 120; i++){
			if(score[i] > 50000000){
				temp = i;
			}
		}
		if(temp == -1){
			temp = tree();			
		}
		board[0][x+dx[temp]][y+dy[temp]] = 2;
		score[0] = sc(0);
		cnt++;
		for(int i=0;i<16;i++){
			for(int j=0;j<16;j++){
				if(i==0){           //������ ��ȣ ���
					printf("%X ", k);
					k++;
					continue;
				}
				if(j==0){           //������ ��ȣ ���
					printf("%X ", t);
					t++;
					continue;
				}
				if(board[0][i][j]==0) cout << "- ";
				else if(board[0][i][j]==1) cout << "O ";
				else if(board[0][i][j]==2) cout << "X ";
			}
			puts("");
		}
		t=1,k=0;
		cnt ++;
		if(score[0] > 50000000){
				printf("AI�� �¸��Դϴ�!");
				cout << "�ٽ� �Ͻðڽ��ϱ�? (Y/N) : ";
				re(); 
		}
	}
}
int main(){
	init();
	while(1){
		titleDraw();
		int code= menuDraw();
		if(code==0) input();
		else if(code==1) return 0;
		system("cls");
		
	}
}

