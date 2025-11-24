#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h> // _getch

void CurrentTime() {
    SYSTEMTIME st;
    GetLocalTime(&st);

    printf("%04d-%02d-%02d %02d:%02d:%02d.%03d\n",
           st.wYear,st.wMonth,st.wDay,st.wHour,
		   st.wMinute,st.wSecond,st.wMilliseconds);
}

void Hidecursor(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = 0;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

void pressAnyKey() {
    printf("\nPress any key to continue (ESC: quit)... ");
    int ch = getch();
    if (ch == 27) { // ESC Ű
        printf("\nExiting program.\n");
        exit(0);
    }
    printf("\nContinuing...\n");
}

int main(){
	int bpm, count, r, min, max, bar;
	double time;
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	
	printf("\n============================================\n");
	printf("======== Metronome Simulation Program ========\n");
	printf("============================================\n");
	printf("Current Time: ");CurrentTime();
	
	printf("\nPress any key to start...\n");
    _getch();
    
    Hidecursor();
	
	while(1){
		system("cls");
		printf("\n>>> Enter Metronome BPM: ");
		scanf(" %d", &bpm);
		
		printf(">>> Enter Metronome Count: ");
		scanf(" %d", &count);
		
    	bar = 0;
		time = 60000 / bpm; //ms
		printf("\nReady(%.0fms) ",time);
		for(int j=3; j>0; j--){
			printf("%d ", j);
			Sleep(time);
		}
		printf("GO! \n");
		Sleep(time);
		
		for(int i=0; i<count; i++){
			
			if(GetAsyncKeyState(VK_UP) & 0x8000){
                bpm++;
                time = 60000.0 / bpm;
            }
            if(GetAsyncKeyState(VK_DOWN) & 0x8000){
                bpm--;
                if(bpm < 60) bpm = 60;
                time = 60000.0 / bpm;
            }
            
			if(i%4==0){
				system("cls");
				max = 355; min = 350;
				printf("========= Metronome Block (Bar:\033[91m%d\033[0m) =========\n",++bar);
				printf("BPM: <\033[91m%d.00\033[0m> ~ (> _ <) ~ Count: %d/4 %d/%d\n",bpm,(i%4)+1, i+1,count);
				r = min + (rand() % (max - min + 1));
				Beep(r,(DWORD)(time-rand()%2));
			}
			if(i%4==1){
				max = 415; min = 410;
				r = min + (rand() % (max - min + 1));
				printf("BPM: <\033[91m%d.00\033[0m> / (+ _ +) / Count: %d/4 %d/%d\n",bpm,(i%4)+1, i+1,count);
				Beep(r,(DWORD)(time-rand()%2));
			}
			if(i%4==2){
				max = 392; min = 390;
				r = min + (rand() % (max - min + 1));
				printf("BPM: <\033[91m%d.00\033[0m> \\ (^ o ^) \\ Count: %d/4 %d/%d\n",bpm,(i%4)+1, i+1,count);
				Beep(r,(DWORD)(time-rand()%2));
			}
			if(i%4==3){
				max = 312; min = 310;
				r = min + (rand() % (max - min + 1));
				printf("BPM: <\033[91m%d.00\033[0m> \\ (+ v +) / Count: %d/4 %d/%d\n",bpm,(i%4)+1, i+1,count);
				Beep(r,(DWORD)(time-rand()%2));
			}
		}
		pressAnyKey();
	}
}
