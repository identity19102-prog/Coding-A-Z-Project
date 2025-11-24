#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

clock_t start, end;
double et = 0.0;
int run = 0;
char key;
char c;

void CurrentTime() {
    SYSTEMTIME st;
    GetLocalTime(&st);
    printf("%04d-%02d-%02d %02d:%02d:%02d.%03d\n",
           st.wYear, st.wMonth, st.wDay,
           st.wHour, st.wMinute, st.wSecond,
           st.wMilliseconds);
}

void printTime(double et) {
    int hr = (int)(et / 3600);
    int min = ((int)(et) % 3600) / 60;
    int sec = (int)et % 60;
    int mil = (int)((et - (int)et) * 1000);
    printf("\rElapsed Time: \033[91m%02d:%02d:%02d.%03d\033[0m (%.2f Tick)", 
	hr, min, sec, mil, et*20);
    fflush(stdout);
}

void funcA(){
	system("cls");
	printf("\n[\033[91mS\033[0m] Start | [\033[91mR\033[0m] Reset |[\033[91mQ\033[0m] Quit\n");
	while(1){
		if (_kbhit()) {
            key = _getch();
            
            if(key >=97 && key<=122) key-=32;
            
            if (key == 'S') {
                if (!run) {
                	Beep(750,100);
                    start = clock() - (et * CLOCKS_PER_SEC);
                    run = 1;
                } else {
                    end = clock();
                    et = (double)(end - start) / CLOCKS_PER_SEC;
                    run= 0;
                }
            } else if (key == 'R') {
                et = 0.0;
                run = 0;
            } else if (key == 'Q') {
                break;
            }
        }
        if (run) {
            end = clock();
            et = (double)(end - start) / CLOCKS_PER_SEC;
        }
        printTime(et);
        fflush(stdout);
	}
}

void funcB(){
	system("cls");
	double limit = 0.0, et = 0.0;
    clock_t start, end;
    int run = 0;
    char key;
    
    printf("\nEnter time limit in seconds: ");
    scanf("%lf", &limit);
    if(limit <= 0){
        printf("Invalid time limit!\n");
        return;
    }
	printf("\n[\033[91mS\033[0m] Start | [\033[91mR\033[0m] Reset | [\033[91mQ\033[0m] Quit\n");
    start = clock();
    while(1){
    	if (_kbhit()) {
            key = _getch();
            if(key >=97 && key<=122) key-=32;

            if(key == 'S'){
                if(!run){
                    Beep(750,100);
                    start = clock() - (et * CLOCKS_PER_SEC);
                    run = 1;
                } else {
                    end = clock();
                    et = (double)(end - start)/CLOCKS_PER_SEC;
                    run = 0;
                }
            } else if(key == 'R'){
                et = 0.0;
                run = 0;
            } else if(key == 'Q'){
                break;
            }
        }

        if(run){
            end = clock();
            et = (double)(end - start)/CLOCKS_PER_SEC;
        }

        double remain = limit - et;
        if(remain <= 0){
            printf("\r\033[91m          !!!Time's up!!!          \033[0m\n");
            Beep(1000,1000);
            break;
        }

        int hr = (int)(remain / 3600);
        int min = ((int)(remain) % 3600) / 60;
        int sec = (int)remain % 60;
        int mil = (int)((remain - (int)remain)*1000);
        printf("\rRemaining Time: \033[91m%02d:%02d:%02d.%03d\033[0m", hr,min,sec,mil);
        fflush(stdout);
    }
}

int main(){	
	SetConsoleOutputCP(65001); // UTF-8
	SetConsoleCP(65001);
	printf("\n============================================\n");
	printf("===========   Stopwatch Module   ===========\n");
	printf("============================================\n");
	printf("Current Time: ");CurrentTime();
	
	printf("\nPress any key to start...\n");
    _getch();
	
	while(1){
		system("cls");
		printf("\n>>>>>>>>>>>>> \033[92mSelection\033[0m <<<<<<<<<<<<<\n");
		printf(
		"[\033[91mA\033[0m] Stopwatch\n"
		"[\033[91mB\033[0m] Timelimit\n"
		"[\033[91mQ\033[0m] Quit\n"
		);
		printf(">>> Select Simulation Mode: ");
		scanf(" %c", &c);
		
		if(c >= 97 && c <= 122) c -= 32;
		
		switch(c){
		case 'A': funcA();break;
		case 'B': funcB();break;
		case 'Q': return 0;
		default :
			Beep(300,100);
			printf("\nInvalid Option.!\n");
			break;
		}
	}
	
}
