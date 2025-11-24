#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //-std=gnu99
#include <time.h>
#include <math.h>
#include <ctype.h>

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

char randomChar() {
    int type = rand() % 2;
    if (type == 0)
        return '0' + rand() % 10;
    else
        return 'A' + rand() % 26;
}

void heart(int size, double delay) {
    printf("\n========= Heart Diagram Output =========\n\n");
    for (int i = size / 2; i <= size; i += 2) {
        for (int j = 1; j < size - i; j += 2)
            printf(" ");
        for (int j = 1; j <= i; j++){
        	textcolor(rand()%16);printf("%c", randomChar());
		}
            
        for (int j = 1; j <= size - i; j++)
            printf(" ");
        for (int j = 1; j <= i; j++){
        	textcolor(rand()%16);printf("%c", randomChar());
		}
            
        printf("\n");
        Beep(1000+rand()%(int)delay, (int)delay);
        fflush(stdout);
    }
    for (int i = size; i >= 1; i--) {
        for (int j = i; j < size; j++)
            printf(" ");
        for (int j = 1; j <= (i * 2) - 1; j++){
        	int r = 1 + rand() % 15;
        	textcolor(rand()%16);printf("%c", randomChar());
		}   
        printf("\n");
        Beep(1000+rand()%(int)delay, (int)delay);
        fflush(stdout);
    }
}

void diamond(int size, double delay) {
    printf("\n========= Diamond Diagram Output =========\n\n");
    for (int i = 1; i <= size; i++) {
        for (int j = i; j < size; j++)
            printf(" ");
        for (int j = 1; j <= (2 * i - 1); j++){
            textcolor(rand()%16);printf("%c", randomChar());
		}	
        printf("\n");
        Beep(800+rand()%(int)delay, (int)delay);
        fflush(stdout);
    }
    for (int i = size - 1; i >= 1; i--) {
        for (int j = size; j > i; j--)
            printf(" ");
        for (int j = 1; j <= (2 * i - 1); j++){
            textcolor(rand()%16);printf("%c", randomChar());
		}
        printf("\n");
        Beep(800+rand()%(int)delay, (int)delay);
        fflush(stdout);
    }
}

void pyramid(int size, double delay) {
    printf("\n========= Pyramid Diagram Output =========\n\n");
    for (int i = 1; i <= size; i++) {
        for (int j = i; j < size; j++)
            printf(" ");
        for (int j = 1; j <= (2 * i - 1); j++){
            textcolor(rand()%16);printf("%c", randomChar());
		}
        printf("\n");
        Beep(900+rand()%(int)delay, (int)delay);
        fflush(stdout);
    }
}

void triangle(int size, double delay) {
    printf("\n========= Triangle Diagram Output =========\n\n");
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= i; j++){
            textcolor(rand()%16);printf("%c", randomChar());
		}
        printf("\n");
        Beep(600+rand()%(int)delay, (int)delay);
        fflush(stdout);
    }
}

void circle(int size, double delay) {
    printf("\n========= Circle Diagram Output =========\n\n");
    int r = size;
    for (int y = -r; y <= r; y++) {
        for (int x = -r; x <= r; x++) {
            if (x * x + y * y <= r * r + r){
            	textcolor(1+rand()%15);printf("%c", randomChar());
			}
            else
                printf(" ");
        }
        printf("\n");
        Beep(700+rand()%(int)delay, (int)delay);
        fflush(stdout);
    }
}

void square(int size, double delay) {
    printf("\n========= Square Diagram Output =========\n\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++){
        	int r = 1 + rand() % 15;
            textcolor(1+rand()%15);printf("%c", randomChar());
		}
		printf("\n");
        Beep(500+rand()%(int)delay, (int)delay);
        fflush(stdout);    
    }
}

void Yggdrasil(int size, int delay) {
	printf("\n========= Yggdrasil Diagram Output =========\n\n");
    int width = size * 2 - 1;
    int max = 494, min = 262;

    int radius = size;
    int total_height = size + (size / 2);
    
 	for (int y = 0; y < total_height; y++) {
 		int z = min + (rand() % (max - min + 1));
        int width;
        
        if (y < radius) {//Half-Circle
            double theta = (double)y / radius * (3.1419 / 2);
            width = (int)(sin(theta) * radius);
        } 
        else {
            width = radius - (total_height - y) / 3;
            if (width < radius / 2) width = radius / 2;
        }

        int spaces = radius - width;
        for (int s = 0; s < spaces; s++) printf(" ");
        for (int x = 0; x < width * 2 - 1; x++) {
            textcolor(rand()%16);printf("%c", randomChar());
        }
        Beep(z,delay);
        printf("\n");
    }

    for (int k = 0; k < size / 3; k++) {
    	int z = min + (rand() % (max - min + 1));
        for (int s = 0; s < size - 1 - 3; s++) {
        	printf(" ");
		}
	    //int color = 1 + rand() % 15;
		textcolor(4);printf("||||||\n");
	    Beep(z,delay);
    }
}

int main(){
	srand((unsigned)time(NULL));
	int BPM, size, r; double delay;
	char menu;
	
	printf("\n============================================\n");
	printf("======== Generate Diagram Algorism  ========\n");
	printf("============================================\n");
	printf("Current Time: ");CurrentTime();
	
	while(1){
		textcolor(7);
		printf("\n>>> Input Level: ");
		scanf("%d", &size);
		
        printf("\n>>> Output Diagram <<<\n");
        printf("Section A: Heart\n");
        printf("Section B: Diamond\n");
        printf("Section C: Pyramid\n");
        printf("Section D: Triangle\n");
        printf("Section E: Circle\n");
        printf("Section F: Square\n");
        printf("Section G: Yggdrasil\n");

        printf(">>> Select: ");
        scanf(" %c", &menu);
		printf(">>> Input BPM: ");
		scanf(" %d", &BPM);
		
		delay = 60000 / BPM; 
		if(menu>=97 && menu<=122) menu-=32;
		
		switch (menu) {
        case 'A': heart(size, delay); break;
        case 'B': diamond(size, delay); break;
        case 'C': pyramid(size, delay); break;
        case 'D': triangle(size, delay); break;
        case 'E': circle(size, delay); break;
        case 'F': square(size, delay); break;
        case 'G': Yggdrasil(size, delay); break;
        default:
            printf("Invalid Section.\n");
            continue;
        }
        textcolor(7);pressAnyKey();
	}
}
