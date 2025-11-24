#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

void CurrentTime() {
    SYSTEMTIME st;
    GetLocalTime(&st);

    printf("%04d-%02d-%02d %02d:%02d:%02d.%03d\n",
           st.wYear, st.wMonth, st.wDay,
           st.wHour, st.wMinute, st.wSecond,
           st.wMilliseconds);
}

void textcolor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Hidecursor(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = 0;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}


char randomChar() {
    int type = rand() % 2;
    if (type == 0)
        return '0' + rand() % 10;
    else
        return 'A' + rand() % 26;
}

int main(){
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	
	srand((unsigned)time(NULL));
	Hidecursor();
	printf("\n============================================\n");
	printf("=========== Yonderly Screensaver ===========\n");
	printf("============================================\n");
	printf("Current Time: ");CurrentTime();
	
	char key = 0;
	
	printf("\n>>> Press any key to start...(Quit: ESC): ");
    _getch();
    system("cls");
    
	while(1){
		int x = rand() % 64;
        int y = 1 + rand() % 32;
        int color = rand() % 15;
        char c = randomChar(); 
		
		if (_kbhit()) {
            key = _getch();
            if (key == 27) {textcolor(7);break;}
		} // ESC
		
		COORD pos = { x, y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        textcolor(color);
        printf("%c", c);   	
        
        if (rand() % 25 == 0) {
            textcolor(7);
            system("cls");
        }
		Sleep(5 + rand()%10);
   	}
   	
   	system("cls");
   	printf("<< Yonderly ScreenSaver Off >>\n");
   	return 0;	
}
