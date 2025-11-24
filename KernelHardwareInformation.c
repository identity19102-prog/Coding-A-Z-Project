#include <stdio.h>
#include <windows.h>

void CurrentTime() {
    SYSTEMTIME st;
    GetLocalTime(&st);
    printf("%04d-%02d-%02d %02d:%02d:%02d.%03d\n",
		   st.wYear,st.wMonth,st.wDay,st.wHour,
		   st.wMinute,st.wSecond,st.wMilliseconds);
}
void textcolor(int color) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color);
    /* 0: black 1: blue 2: green 3: aqua 4: red 5: magenta 6: yellow 7: white
	8: gray 9: light blue 10: light green 11: light aqua
	12: light red 13: pink 14: light yellow 15: bright white
	font use PxPlus Rainbow100 re.66 */
}
char randomChar() {
    int type = rand() % 2;
    if (type == 0)
        return '0' + rand() % 10;
    else
        return 'A' + rand() % 26;
}

void loadingBar(const char *msg){ //*msg is pointer, "const" means do not change data.
	textcolor(11);
	printf("%s ", msg);
	textcolor(7);
	
	for(int i=0; i<25; i++){
		textcolor(rand()%16);
		printf("%c",randomChar());
		textcolor(7);
		Sleep(40 + rand() % 40);
	}
	printf("  Done! \u263B\n");
	Sleep(150);
}

void pressAnyKey() {
    printf("\nPress any key to continue (ESC: quit)... ");
    int ch = getch();
    if (ch == 27) { // ESC
        printf("\nExiting program.\n");
        exit(0);
    }
    printf("\nContinuing...\n");
}

void Hardware(){
	SYSTEM_INFO sysInfo;
    MEMORYSTATUSEX memStat;

     // UTF-8
    GetSystemInfo(&sysInfo);
    memStat.dwLength = sizeof(memStat);
    GlobalMemoryStatusEx(&memStat);
	
    printf("=======================================\n");
    textcolor(11);
	printf("      Kernel Hardware Information      \n");
	textcolor(7);
    printf("=======================================\n");
    printf("\n");
	textcolor(7);Beep(800,300+rand()%16);
	
    // CPU
    //loadingBar("Reading CPU info...");
    textcolor(12);printf("[CPU]\n");textcolor(7);
    system("wmic cpu get name /value | find \"=\"");
    printf("Cores : %u\n\n", sysInfo.dwNumberOfProcessors);
    textcolor(7);Beep(800,300+rand()%16);

    // RAM
    //loadingBar("Reading RAM info...");
    textcolor(12);printf("[Memory]\n");textcolor(7);
    printf("Total : %llu MB\n", memStat.ullTotalPhys / (1024 * 1024));
    printf("Available : %llu MB\n", memStat.ullAvailPhys / (1024 * 1024));
    printf("\n");textcolor(7);Beep(800,300+rand()%16);
	
	//Motherboard
	//loadingBar("Reading Motherboard info...");
	textcolor(12);printf("[Mainboard]\n");textcolor(7);
	system("for /f \"tokens=2 delims==\" %a in ('wmic baseboard get manufacturer /value') do @echo Manufacturer: %a");
	system("for /f \"tokens=2 delims==\" %a in ('wmic baseboard get product /value') do @echo Product: %a");
	system("for /f \"tokens=2 delims==\" %a in ('wmic baseboard get version /value') do @echo Version: %a");
	printf("\n");textcolor(7);Beep(800,300+rand()%16);
	
    // Graphics Card
    //loadingBar("Reading VGA info...");
    textcolor(12);printf("[Graphics]\n");textcolor(7);
    system("wmic path win32_videocontroller get name /value | find \"=\"");
    printf("\n");textcolor(7);Beep(800,300+rand()%16);
	
    // Stroage
    //loadingBar("Reading Stroage info...");
    textcolor(12);printf("[Storage]\n");textcolor(7);
    system("wmic diskdrive get model /value | find \"=\"");
    printf("\n");textcolor(7);Beep(800,300+rand()%16);
    
    // Opration System 
    //loadingBar("Reading Opration System info...");
    textcolor(12);printf("[OS]\n");textcolor(7);
    system("wmic os get caption,version /value | find \"=\"");
    printf("\n");Beep(800,300+rand()%16);
    
    //loadingBar("Reading Device info...");
    textcolor(12); printf("\n[Device Name]\n"); textcolor(7);
	system("wmic computersystem get name /value | find \"=\"");
	printf("\n");Beep(800, 300 + rand() % 16);
    
	textcolor(7);
    printf("=======================================\n");
    textcolor(11);printf("          END OF INFORMATION\n");textcolor(7);
    printf("=======================================\n");
    printf("\n");Beep(800,300+rand()%16);
}

int main(){
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	srand((unsigned)time(NULL));
	printf("\n============================================\n");
	printf("======  Kernel Hardware Information  =======\n");
	printf("============================================\n");
	printf("Current Time: ");CurrentTime();
	printf("Press any key to start...\n");
    _getch();
	system("cls");
	while(32767){
		Hardware();
		pressAnyKey();
	}
}


