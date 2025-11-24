#include <stdio.h>
#include <windows.h>
#include <conio.h>

volatile double loadPercent = 0.0;
volatile int running = 1;  

void CurrentTime() {
    SYSTEMTIME st;
    GetLocalTime(&st);

    printf("%04d-%02d-%02d %02d:%02d:%02d.%03d\n",
           st.wYear, st.wMonth, st.wDay,
           st.wHour, st.wMinute, st.wSecond,
           st.wMilliseconds);
}

DWORD WINAPI LoadThread(LPVOID arg) {
    while (running) {
        DWORD busyTime = (DWORD)(loadPercent * 10);
        DWORD idleTime = 1100 - busyTime;
        
        if (idleTime < 0) idleTime = 0;
        DWORD start = GetTickCount();
        
        while (GetTickCount() - start < busyTime) {
            double x = 0, y = 0, z = 0; 
            
            for (int i = 0; i < 500; i++){
            	for (int j = 0; j < 500; j++){
            		for (int k = 0; k < 500; k++){
            			x += i * 0.001;y += j * 0.002;z += k * 0.003;
					}
				}
			}
        }
        Sleep(idleTime);
    }
    return 0;
}

int main(){
	SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    int cores = sysInfo.dwNumberOfProcessors;
    SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
    
	printf("\n============================================\n");
	printf("========  Hyper Reinforcement Test  ========\n");
	printf("============================================\n");
	printf("Current Time: ");CurrentTime();
	
	int run = 1;
	
	while(1){
		printf("\nCPU Core Count : %d\n", cores);
		printf(">>> CPU Load Rate (0~100%%): ");
	    scanf(" %lf", &loadPercent);
	    
	    if (loadPercent < 0) loadPercent = 0;
    	if (loadPercent > 100) loadPercent = 100;
    	
    	for (int i = 0; i < cores; i++) {
        	CreateThread(NULL, 0, LoadThread, NULL, 0, NULL);
    	}
    	
    	printf("\nEntered Loading Rate: %.2lf%%\n", loadPercent);
    	printf("[Working] Press Key to Reset and Quit (R|Q)\n");
    	
    	while(run){
			if (_kbhit()) {
	            char c = _getch();
	            if (c == 'q' || c == 'Q' || c == 27) { // Quit This Program.
	                run = 0;
	                printf("\nThread Terminating..\n");	
					Sleep(1000); 
					printf("All Thread Terminated.\n");
					return 0;
	            } else if (c == 'r' || c == 'R') { // 'Press r Reset CPU Loading Rate
	                printf("\n>>> New CPU Core Loading (0~100%%): ");
	                scanf("%lf", &loadPercent);
	                if (loadPercent < 0) loadPercent = 0;
	                if (loadPercent > 100) loadPercent = 100;
	                printf("[Working] Current Loading Rate: %.2lf%%\n", loadPercent);
	            }
    		}
    		Sleep(100);
		}	
	}
    return 0;
}
