#include <stdio.h>
#include <ctype.h>
#include <windows.h>

char str[32767], rev[32767], result[32767];
int s = 0, bpm = 0;

void textcolor(int color) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color);
    /* 0: black 1: blue 2: green 3: aqua 4: red 5: magenta 6: yellow 7: white
	8: gray 9: light blue 10: light green 11: light aqua
	12: light red 13: pink 14: light yellow 15: bright white*/
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

void CurrentTime() {
    SYSTEMTIME st;
    GetLocalTime(&st);

    printf("%04d-%02d-%02d %02d:%02d:%02d.%03d\n",
           st.wYear, st.wMonth, st.wDay,
           st.wHour, st.wMinute, st.wSecond,
           st.wMilliseconds);
}

int main(){
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	
	srand(time(NULL));
	printf("\n============================================\n");
	printf("========== Caesar Cipher Algoriam ==========\n");
	printf("============================================\n");
	printf("Current Time: ");CurrentTime();
	
	while(1){
		printf("\n>>> Enter Convert String: ");
		scanf(" %[^\n]s", str);
		printf(">>> Enter Shift Level: ");
		scanf(" %d", &s);
		printf(">>> Enter BPM: ");
		scanf(" %d", &bpm);
		
		s = (s % 26 + 26) % 26;
		int t = 60000/bpm;
		
	    char *ptr = &str;
	    int len = strlen(str);
	    
	    printf("Reverse Current String: ");
	    for (int i=0; i<len; i++){
	    	rev[i] = str[len - i - 1];
	    	textcolor(12);printf("%c",rev[i]);textcolor(7);
			Beep(200+rand()%500,t);
		}
		
	 	printf("\nConverted Caesar String: ");
	    for(int i = 0; ptr[i]!='\0'; i++){
	        if(isupper(ptr[i]))
	            result[i] = (ptr[i]-'A'+ s) % 26 + 'A';
	        else if(islower(ptr[i]))
	            result[i] = (ptr[i]-'a'+ s) % 26 + 'a';
	        else if(isdigit(ptr[i]))
	            result[i] = (ptr[i]-'0'+ s) % 10 + '0';
	        else if(!(isupper(ptr[i]) || islower(ptr[i]) || isdigit(ptr[i])))    
	            result[i] = ptr[i];
	        
	        textcolor(12);printf("%c",result[i]);textcolor(7);
			Beep(200+rand()%500,t);
	    }
	    printf("\n");
	    pressAnyKey();
	}	
}


