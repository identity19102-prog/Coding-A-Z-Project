#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define W 33
#define H 24
#define TIME_LIMIT 999

char m[H][W];
int px=1, py=1, score=0, stageScore=0, maxScore=0, level=0, rem=0;
int bl = 15;
int bc = 0;

void CurrentTime() {
    SYSTEMTIME st;
    GetLocalTime(&st);

    printf("%04d-%02d-%02d %02d:%02d:%02d.%03d\n",
           st.wYear, st.wMonth, st.wDay,
           st.wHour, st.wMinute, st.wSecond,
           st.wMilliseconds);
}
void Hidecursor(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = 0;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

void textcolor(int color) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color);
    /* 0: black 1: blue 2: green 3: aqua 4: red 5: magenta 6: yellow 7: white
	8: gray 9: light blue 10: light green 11: light aqua
	12: light red 13: pink 14: light yellow 15: bright white*/
}

void goTop(){
    COORD topLeft = {0,0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), topLeft);
}

int countMaxScore(){
    int cnt=0;
    for(int i=0;i<H;i++)
        for(int j=0;j<W;j++)
            if(m[i][j]=='@') cnt++;
    return cnt;
}

void draw(int timeLeft){
    goTop();
    textcolor(7);
    printf(" %06d     \u263B <", score);
	textcolor(11);printf(" %d ", level);textcolor(7);
	printf("> \u263B   Time:%03d \n", timeLeft);
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            char ch = m[i][j];

            if(i == py && j == px){
                textcolor(10);
                printf("\u263B");
                textcolor(7);
            }
            else if(ch == '#'){
                textcolor(8);
                printf("#");
                textcolor(7);
            }
            else if(ch == '@'){
                textcolor(rand()%16);
                printf("@");
                textcolor(7); 
            }
            else if(ch == 'X'){
                textcolor(240);
                printf("E");
                textcolor(7);
            }
            else{
                printf("%c", ch);
            }
        }
        printf("\n");
    }

    textcolor(7);
    printf(" %02d,%02d ", px, py);
    if(maxScore - stageScore != 0){
    	textcolor(9);printf("         %X", bl-bc);
		textcolor(7);
    	textcolor(12);printf("            %03d\n", maxScore - stageScore);
		textcolor(7);
	} else {
		textcolor(9);printf("         %X", bl-bc);
		textcolor(7);
		textcolor(4);printf("            %03d\n", maxScore - stageScore);
		textcolor(7);
	}
    
}

void generateMaze() {
    bc = 0;

    // Wall init
    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++)
            m[y][x] = '#';

    // DFS
    int visited[H][W] = {0};
    int stackX[H*W], stackY[H*W];
    int sp = 0;

    int sx = 1 + (rand() % ((W-2)/2)) * 2;
    int sy = 1 + (rand() % ((H-2)/2)) * 2;

    stackX[sp] = sx;
    stackY[sp] = sy;
    sp++;
    visited[sy][sx] = 1;
    m[sy][sx] = ' ';

    int dx[4] = {0, 0, -2, 2};
    int dy[4] = {-2, 2, 0, 0};

    // DFS Backtracking ===
    while (sp > 0) {
        int x = stackX[sp-1];
        int y = stackY[sp-1];

        int dirs[4] = {0,1,2,3};

        for (int i = 0; i < 4; i++) {
            int r = rand()%4;
            int t = dirs[i];
            dirs[i] = dirs[r];
            dirs[r] = t;
        }

        int moved = 0;

        for (int k = 0; k < 4; k++) {
            int d = dirs[k];
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx <= 0 || ny <= 0 || nx >= W-1 || ny >= H-1)
                continue;

            if (!visited[ny][nx]) {
                visited[ny][nx] = 1;

                m[y + dy[d]/2][x + dx[d]/2] = ' ';
                m[ny][nx] = ' ';

                stackX[sp] = nx;
                stackY[sp] = ny;
                sp++;

                moved = 1;
                break;
            }
        }

        if (!moved) sp--; // back tracking
    }

    // === Item
    int itemCount = level*5 + rand()%10;
    for (int i=0; i<itemCount; i++) {
        int x, y;
        do {
            x = rand()%W;
            y = rand()%H;
        } while (m[y][x] != ' ');
        m[y][x] = '@';
    }

    // ===  Exit
    int ex, ey;
    do {
        ex = rand()%W;
        ey = rand()%H;
    } while (m[ey][ex] != ' ');
    m[ey][ex] = 'X';

    // === Player
    int distance(int x1, int y1, int x2, int y2) {
        return abs(x1-x2) + abs(y1-y2);
    }

    do {
        px = 1 + rand() % (W-2);
        py = 1 + rand() % (H-2);
    } while (m[py][px] != ' ' || distance(px,py,ex,ey) < 8);

    m[py][px] = 'P';

    bc = 0;
    if (level == 0) score = 0;
    stageScore = 0;
    maxScore = countMaxScore();
}

void victory() {
    Beep(523, 200); // C5
    Beep(659, 200); // E5
    Beep(783, 400); // G5
    Beep(1046, 600); // C6
    Beep(783, 400);  // G5
    Beep(659, 400);  // E5
    Beep(523, 800);  // C5
}

int main(){
	char c;
	SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    srand((unsigned)time(NULL));
    Hidecursor();
	printf("\n============================================\n");
    printf("============= Xenomaze Adventure ===========\n");
    printf("============================================\n");
    printf("Press any key to start...\n");
    _getch();
    clock_t start = clock();
    system("cls");
    generateMaze();
    while(1){
        
        int elapsed = (clock() - start) / CLOCKS_PER_SEC;
		int timeLeft = TIME_LIMIT - elapsed;
        draw(timeLeft);       
        
	    if(timeLeft <= 0){
	        draw(0);
	        printf("Time Out!!\n");
	        printf("Game Over! Final Level: %d\n", level);
	        return 0;
    	}
		
        if(_kbhit()){ //WASD & Arrow Key
            c = _getch();
            int nx = px, ny = py;
            
            if (c == -32 || c == 224) {
		        c = _getch();
		        switch (c) {
		            case 72: ny--; break; // ก่ 
		            case 80: ny++; break; // ก้
		            case 75: nx--; break; // ก็
		            case 77: nx++; break; // กๆ
	       		}
		    } else {
		        if (c == 'W'||c == 'w') ny--;
		        if (c == 'S'||c == 's') ny++;
		        if (c == 'A'||c == 'a') nx--;
		        if (c == 'D'||c == 'd') nx++;
		    }
		    
            if(nx<0 || nx>=W || ny<0 || ny>=H) continue;
            if(m[ny][nx]=='#'){
            	if(bc < bl){
            		m[ny][nx] = ' ';
            		bc++;
            		Beep(200,50);
				} else {
					continue;
				}
			}
            if(m[ny][nx]=='@'){	
            	score++;
            	stageScore++;
            	Beep(400,50);
			}
            if(m[ny][nx]=='X'){
                if(maxScore - stageScore == 0){
                    draw(timeLeft);
                    printf("\nYou Escaped!!! Level %d Cleared!\n", level); 
                    level++;
                    if(level>9){
                    	system("cls");
						textcolor(10);
                    	printf("====================================\n");
			            printf("========= CONGRATULATIONS! =========\n");
			            printf("======  YOU CLEARED THE GAME  ======\n");
			            printf("====================================\n");
			            victory();
						textcolor(7);
			            return 0; 
					}
					srand((unsigned int)time(NULL) + level);
                    generateMaze();
                    start = clock();
                    Sleep(1000);
                    system("cls");
                } else {
                    textcolor(12);printf("Clean all items first!!\n");textcolor(7);
                    Sleep(1000);
                    system("cls");
                    continue;
                }
            }
            m[py][px]=' ';
            px=nx; 
			py=ny;
            m[py][px]='P';   
        }
    }
    return 0;
}
