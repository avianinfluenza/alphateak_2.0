#include<bits/stdc++.h>
#include<windows.h> 
#include<conio.h>

// 키보드 값 
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
long long int score[1742621], im = -10000000000, AI[6] = {0, 1, 100, 10000, 1000000, 100000000};

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

// 평가 함수 고려해야할 것 : 돌 개수, 최근에 둔 돌 근처에 있는 돌 수 
int sc(int index){		//평가함수 플레이어(1) 에게 유리할때는 음수, AI(2)에게 유리할때는 양수 
	int i, j, s = 0,temp, tf; 
	for(i = 1; i <= 15; i++){	//AI기준 가로 세로 연결된 돌 고려 
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
	for(i = 1; i <= 15; i++){	//플레이어기준 가로 세로 연결된 돌 고려, 플레이어는 인공지능보다 가중치 2 배  
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
	for(i = 1; i <= 15; i++){	//AI기준 대각선 고려(조선 아님) 
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
	for(i = 1; i <= 15; i++){	//AI기준 대각선 고려(조선 아님) 
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
	
	for(i = 1; i <= 15; i++){	//player기준 대각선 고려(조선 아님) 
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
			s -= AI[temp]*4;
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
			s -= AI[temp]*4;
			temp = 0;
			tf = 0;
		}		
	}
		
	for(i = 1; i <= 15; i++){	//player기준 대각선 고려(조선 아님) 
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
			s -= AI[temp]*4;
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

int sc2(int index){		//board[index][x][y]
	int temp, tf, s = 0, i, j;
	int x = board[index][0][0];		//가장 최근 착수 돌의 x좌표 
	int y = board[index][0][1];		//가장 최근 착수 돌의 y좌표 
	//현재 board가 플레이어가 가장 최근에 둔 board(플레이어 기준으로 점수 부여) 
	temp = 0; tf = 0;
	for(i = 1; i <= 5; i++){		//y++
		if(y+i > 15){
			break;
		}
		if(board[index][x][y+i] == 1){
			temp++;
			tf = 1;
		}
		else{
			if(tf == 1){
				s -= AI[temp]*2;
				if(temp >= 3){
					if(board[index][x][y+i] == 2){
						s += AI[temp]*3;
					}
					if(y+i-temp-1 > 0){
						if(board[index][x][y+i-temp-1] == 2){
							s += AI[temp]*3;
						}
					}
				}
				temp = 0; tf = 0;
			}
		}
	}
	if(tf == 1){
		s -= 2*AI[temp];
		temp = 0; tf = 0;
	}
	
	for(i = 1; i <= 5; i++){		//x++
		if(x+i > 15){
			break;
		}
		if(board[index][x+i][y] == 1){
			temp++;
			tf = 1;
		}
		else{
			if(tf == 1){
				s -= AI[temp]*2;
				if(temp >= 3){
					if(board[index][x+i][y] == 2){
						s += AI[temp]*3;
					}
					if(x+i-temp-1 > 0){
						if(board[index][x+i-temp-1][y] == 2){
							s += AI[temp]*3;
						}
					}
				}
				temp = 0; tf = 0;
			}
		}
	}
	if(tf == 1){
		s -= 2*AI[temp];
		temp = 0; tf = 0;
	}
	
	for(i = 1; i <= 5; i++){		//y--
		if(y-i < 1){
			break;
		}
		if(board[index][x][y-i] == 1){
			temp++;
			tf = 1;
		}
		else{
			if(tf == 1){
				s -= AI[temp]*2;
				if(temp >= 3){
					if(board[index][x][y-i] == 2){
						s += AI[temp]*3;
					}
					if(y-i+temp+1 <= 15){
						if(board[index][x][y-i+temp+1] == 2){
							s += AI[temp]*3;
						}
					}
				}
				temp = 0; tf = 0;
			}
		}
	}
	if(tf == 1){
		s -= 2*AI[temp];
		temp = 0; tf = 0;
	}
	
	for(i = 1; i <= 5; i++){		//x--
		if(x-i < 1){
			break;
		}
		if(board[index][x-i][y] == 1){
			temp++;
			tf = 1;
		}
		else{
			if(tf == 1){
				s -= AI[temp]*2;
				if(temp >= 3){
					if(board[index][x-i][y] == 2){
						s += AI[temp]*3;
					}
					if(x-i+temp+1 <= 15){
						if(board[index][x-i+temp+1][y] == 2){
							s += AI[temp]*3;
						}
					}
				}
				temp = 0; tf = 0;
			}
		}
	}
	if(tf == 1){
		s -= 2*AI[temp];
		temp = 0; tf = 0;
	}
	
	for(i = 1; i <= 5; i++){		//x++ y++
		if(x+i > 15 || y+i > 15){
			break;
		}
		if(board[index][x+i][y+i] == 1){
			temp++;
			tf = 1;
		}
		else{
			if(tf == 1){
				s -= AI[temp]*4;
				if(temp >= 3){
					if(board[index][x+i][y+i] == 2){
						s += AI[temp]*3;
					}
					if(x+i-temp-1 > 0 && y+i-temp-1 > 0){
						if(board[index][x+i-temp-1][y+i-temp-1] == 2){
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
		temp = 0; tf = 0;
	}
	
	for(i = 1; i <= 5; i++){		//x-- y--
		if(x-i < 1 || y-i < 1){
			break;
		}
		if(board[index][x-i][y-i] == 1){
			temp++;
			tf = 1;
		}
		else{
			if(tf == 1){
				s -= AI[temp]*4;
				if(temp >= 3){
					if(board[index][x-i][y-i] == 2){
						s += AI[temp]*3;
					}
					if(x-i+temp+1 <= 15 && y-i+temp+1 <= 15){
						if(board[index][x-i+temp+1][y-i+temp+1] == 2){
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
		temp = 0; tf = 0;
	}		
	
	for(i = 1; i <= 5; i++){		//x++ y--
		if(x+i > 15 || y-i < 1){
			break;
		}
		if(board[index][x+i][y-i] == 1){
			temp++;
			tf = 1;
		}
		else{
			if(tf == 1){
				s -= AI[temp]*4;
				if(temp >= 3){
					if(board[index][x+i][y-i] == 2){
						s += AI[temp]*3;
					}
					if(x+i-temp-1 > 0 && y-i+temp+1 <= 15){
						if(board[index][x+i-temp-1][y-i+temp+1] == 2){
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
		temp = 0; tf = 0;
	}
	
	for(i = 1; i <= 5; i++){		//x-- y++
		if(x-i < 1 || y+i > 15){
			break;
		}
		if(board[index][x-i][y+i] == 1){
			temp++;
			tf = 1;
		}
		else{
			if(tf == 1){
				s -= AI[temp]*4;
				if(temp >= 3){
					if(board[index][x-i][y+i] == 2){
						s += AI[temp]*3;
					}
					if(x-i+temp+1 <= 15 && y+i-temp-1 >= 1){
						if(board[index][x-i+temp+1][y+i-temp-1] == 2){
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
		temp = 0; tf = 0;
	}		
		/////////////////////////////////////AI기준 
	tf = 0; temp = 0;
	for(i = 1; i <= 5; i++){		//y++
		if(y+i > 15){
			break;
		}
		if(board[index][x][y+i] == 2){
			temp++;
			tf = 1;
		}
		else{
			if(tf == 1){
				s += AI[temp];
				temp = 0; tf = 0;
			}
		}
	}
	if(tf == 1){
		s += AI[temp];
		temp = 0; tf = 0;
	}
	
	for(i = 1; i <= 5; i++){		//x++
		if(x+i > 15){
			break;
		}
		if(board[index][x+i][y] == 2){
			temp++;
			tf = 1;
		}
		else{
			if(tf == 1){
				s += AI[temp];
				temp = 0; tf = 0;
			}
		}
	}
	if(tf == 1){
		s += AI[temp];
		temp = 0; tf = 0;
	}
	
	for(i = 1; i <= 5; i++){		//y--
		if(y-i < 1){
			break;
		}
		if(board[index][x][y-i] == 2){
			temp++;
			tf = 1;
		}
		else{
			if(tf == 1){
				s += AI[temp];
				temp = 0; tf = 0;
			}
		}
	}
	if(tf == 1){
		s += AI[temp];
		temp = 0; tf = 0;
	}
	
	for(i = 1; i <= 5; i++){		//x--
		if(x-i < 1){
			break;
		}
		if(board[index][x-i][y] == 2){
			temp++;
			tf = 1;
		}
		else{
			if(tf == 1){
				s -= AI[temp];
				temp = 0; tf = 0;
			}
		}
	}
	if(tf == 1){
		s += AI[temp];
		temp = 0; tf = 0;
	}
	
	for(i = 1; i <= 5; i++){		//x++ y++
		if(x+i > 15 || y+i > 15){
			break;
		}
		if(board[index][x+i][y+i] == 2){
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
		temp = 0; tf = 0;
	}
	
	for(i = 1; i <= 5; i++){		//x-- y--
		if(x-i < 1 || y-i < 1){
			break;
		}
		if(board[index][x-i][y-i] == 2){
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
		temp = 0; tf = 0;
	}		
	
	for(i = 1; i <= 5; i++){		//x++ y--
		if(x+i > 15 || y-i < 1){
			break;
		}
		if(board[index][x+i][y-i] == 2){
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
		temp = 0; tf = 0;
	}
	
	for(i = 1; i <= 5; i++){		//x-- y++
		if(x-i < 1 || y+i > 15){
			break;
		}
		if(board[index][x-i][y+i] == 2){
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
		temp = 0; tf = 0;
	}		
	return s;
}


void copy(int a, int b){	//b 보드에 a보드를 복사함  
	int i, j;
	for(i = 1; i <= 15; i++){
		for(j = 1; j<= 15;j++){
			board[b][i][j] = board[a][i][j]; 
		}
	}
}

int key(){	//키 입력 함수 
	int key;
	key=getch();
	if(key==72) return UP; // 방향키 위 
	else if(key==80) return DOWN; // 방향키 아래 
	else if(key==13) return ENTER; // 엔터키 
} 
void xy(int x, int y){	// x,y 좌표설정 
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}
void init(){  //크기및 커서 숨기는 설정 
	system("title OMOK BOT");
	system("mode con cols=53 lines=15"); 
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle,&ConsoleCursor);
}
void titleDraw(){ //타이틀
	puts("           #####   #     #   #####   #    # ");
 	puts("          #     #  ##   ##  #     #  #   #  ");
	puts("          #     #  # # # #  #     #  #  #   ");
	puts("          #     #  #  #  #  #     #  ###    ");
	puts("          #     #  #     #  #     #  #  #   ");
	puts("          #     #  #     #  #     #  #   #  ");
	puts("           #####   #     #   #####   #    # ");

}
int menuDraw(){	// 선택 
	int x=23;
	int y=10;
	xy(x-2,y);
	printf("> 게임시작");
	xy(x,y+2);
	printf("  종료 ");
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

void re(){ //다시하기 입력받는 함수
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
	else cout << "잘못된 입력입니다. 다시 입력해주세요: ";
	}
}

void input(){	// 플레이
	system("mode con cols=45 lines=17"); // 크기 조절 
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
		if(cnt%2!=0) cout << "Player 1의 착수위치를 입력해주세요: ";
		while(1){
			cin >> x >> y;
			if(x<0||x>15||y<0||y>15||board[0][x][y]!=0) cout << "잘못된 입력입니다. 다시 입력해주세요: ";
			else break;
		}
		if(cnt%2!=0){
			temp = -1;
			board[0][x][y]=1; //player1 착수, board[0]은 루트노드
			board[0][0][0] = x;
			board[0][0][1] = y;
			score[0] = sc(0);
			if(score[0] < -50000000){
				for(int i=0;i<16;i++){
					for(int j=0;j<16;j++){
						if(i==0){           //가로줄 번호 출력
							printf("%X ", k);
							k++;
							continue;
						}
						if(j==0){           //세로줄 번호 출력
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
				printf("player의 승리입니다!");
				re(); 
			}
			for(int i = 1; i <= 120; i++){		//경우의 수 트리에 저장 
				copy(0, i);
				score[i] = score[0];
				if(x+dx[i] < 0 || x+dx[i] > 15 || y+dy[i] < 0 || y+dy[i] > 15){
					score[i] = im;	//나중에 점수 계산(미니맥스 알고리즘)을 사용할때 논외로 빼놓기 위함
					for(int j = 1; j <= 120; j++){
						score[i*120+j] = im;
						for(int k = 1; k <= 120; k++){
							score[(i*120+j)*120+k] = im;
						}
					}
				}
				else if(board[i][x + dx[i]][y + dy[i]] != 0){		//이미 돌이 있는 경우 
					score[i] = im;	//나중에 점수 계산(미니맥스 알고리즘)을 사용할때 논외로 빼놓기 위함
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
					score[i] += sc2(i);
					for(int j = 1; j <= 120; j++){
						copy(i,120*i+j);
						score[120*i+j] = score[i];
						if(x+dx[i]+dx[j] < 0 || x+dx[i]+dx[j] > 15 || y+dy[i]+dy[j] < 0 || y+dy[i]+dy[j] > 15){		//board 범위 초과  
							score[i*120+j] = im;	//나중에 점수 계산(미니맥스 알고리즘)을 사용할때 논외로 빼놓기 위함
							for(int k = 1; k <= 120; k++){
								score[(i*120+j)*120+k] = im;
							}
						}
						else if(board[i*120+j][x+dx[i]+dx[j]][y+dy[i]+dy[j]] != 0){		//이미 돌이 있는 경우 
							score[i*120+j] = im;	//나중에 점수 계산(미니맥스 알고리즘)을 사용할때 논외로 빼놓기 위함
							for(int k = 1; k <= 120; k++){
								score[(i*120+j)*120+k] = im;
							}
						}
						else{
							board[i*120+j][x+dx[i]+dx[j]][y+dy[i]+dy[j]] = 1;
							board[i*120+j][0][0] = x+dx[i]+dx[j];
							board[i*120+j][0][1] = y+dy[i]+dy[j];
							score[i*120+j] += sc2(i*120+j);
							for(int k = 1; k <= 120; k++){
								copy(i*120+j, (i*120+j)*120+k);
								score[(i*120+j)*120+k] = score[i*120+j]; 
								if(x+dx[i]+dx[j]+dx[k] > 15 || x+dx[i]+dx[j]+dx[k] < 0 || y+dy[i]+dy[j]+dy[k] > 15 || y+dy[i]+dy[j]+dy[k] < 0){
									score[(i*120+j)*120+k] = im;	//나중에 점수 계산(미니맥스 알고리즘)을 사용할때 논외로 빼놓기 위함
								}
								else if(board[(i*120+j)*120+k][x+dx[i]+dx[j]+dx[k]][y+dy[i]+dy[j]+dy[k]] != 0){		//이미 돌이 있는 경우 
									score[(i*120+j)*120+k] = im;	//나중에 점수 계산(미니맥스 알고리즘)을 사용할때 논외로 빼놓기 위함
								}
								else{
									board[(i*120+j)*120+k][x+dx[i]+dx[j]+dx[k]][y+dy[i]+dy[j]+dy[k]] = 2;
									board[(i*120+j)*120+k][0][0] =  x+dx[i]+dx[j]+dx[k];
									board[(i*120+j)*120+k][0][1] =  y+dy[i]+dy[j]+dy[k];
									score[(i*120+j)*120+k] += sc2((i*120+j)*120+k);
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
				if(i==0){           //가로줄 번호 출력
					printf("%X ", k);
					k++;
					continue;
				}
				if(j==0){           //세로줄 번호 출력
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
				printf("AI의 승리입니다!");
				cout << "다시 하시겠습니까? (Y/N) : ";
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
