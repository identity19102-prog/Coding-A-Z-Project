#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void CurrentTime() {
    SYSTEMTIME st;
    GetLocalTime(&st);

    printf("%04d-%02d-%02d %02d:%02d:%02d.%03d\n",
           st.wYear,st.wMonth,st.wDay,
           st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
}

void pressAnyKey() {
    printf("\nPress any key to continue (ESC: quit)... ");
    int ch = getch();
    if (ch == 27) { // ESC Ű
        printf("\nExiting program.\n");
        exit(0);
    }
    printf("\nContinuing...\n");
    Sleep(1000);system("cls");
}

void textcolor(int color) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color);
    /* 0: black 1: blue 2: green 3: aqua 4: red 5: magenta 6: yellow 7: white
	8: gray 9: light blue 10: light green 11: light aqua
	12: light red 13: pink 14: light yellow 15: bright white*/
}

int isPrime(int number){
	if(number<2) return 0;
	for (int i = 2; i < number; i++){
		if (number % i == 0) return 0; // Filtering	Composite number.
	}
	return 1;
}

int checkPerfectNumber(int number) {
    int sum = 0;
    //Greatest Common Divisor(GCD) : num / 2
	    for (int i = 1; i <= number / 2; i++) {
	        if (number % i == 0) 
	            sum += i;
	    }
    if (sum == number) return 1;
    else return 0;
}

int main(void){
	srand((unsigned)time(NULL));
	int num, count, r, res, bpm;
	SetConsoleOutputCP(65001); // UTF-8
	SetConsoleCP(65001);
	printf("\n============================================\n");
	printf("==========  Organic Prime Numbers  =========\n");
	printf("============================================\n");
	printf("Current Time: ");CurrentTime();
	printf("\nPress any key to start...");
    _getch();
	while(1){
		printf("\n>>> Enter Max Output Number: ");
		scanf(" %d", &num);
		printf(">>> Enter Output BPM: ");
		scanf(" %d", &bpm);
		int time = 60000 / bpm;
		
		printf("\n>>>>>>>>>>>>> Finding Result <<<<<<<<<<<<<\n");
		count = 1;
		int arr[num];
		//num--;
		for (int i = 0, j = 0; i <= num; i++) {
			int max = 750, min = 250;
	        if (isPrime(i)){
	        	textcolor(12);
				printf("%3d ", i);
	        	arr[j] = i;
	        	j++;
				res = j;
			}
			else if(i > 0 && checkPerfectNumber(i)){
				textcolor(3);
				printf("%3d ", i);
			}
	        else{
	        	textcolor(7);
				printf("%3d ", i);
			} 
	        if (count % 10 == 0){
	        	r = min + (rand() % (max - min + 1));
	        	Beep(r, time);
        		printf("\n");
			}
			textcolor(7);
			count++;
    	}
    	printf("\nCurrent Prime List: \n");
    	for(int i = 0; i < res; i++){
    		int max = 750, min = 250;
    		r = min + (rand() % (max - min + 1));
    		textcolor(rand()%16);
			printf("%3d ",arr[i]);
    		if((i + 1) % 10 == 0) {
    			printf("\n");
    			Beep(r, time);
			}
		}
		textcolor(7);
		printf("\nCurrent Prime Array Length: %d\n", res);
		pressAnyKey();	
	}
}
