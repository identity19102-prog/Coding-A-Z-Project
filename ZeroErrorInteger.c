#include <stdio.h>
#include <windows.h>
#define SIZE 1000

void CurrentTime() {
    SYSTEMTIME st;
    GetLocalTime(&st);
    printf("%04d-%02d-%02d %02d:%02d:%02d.%03d\n",
           st.wYear, st.wMonth, st.wDay,
           st.wHour, st.wMinute, st.wSecond,
           st.wMilliseconds);
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
void funcA(){
	int b,e,t;
	printf("\n>>> Enter Base: ");
	scanf("%d", &b);
	printf(">>> Enter Exponent: ");
	scanf("%d", &e);
	printf(">>> Enter BPM: ");
	scanf("%d", &t);
	
	t = 60000/t;
	if(t < 50) t = 50;
    if(t > 2000) t = 2000;
	
	int res[SIZE]; res[0] = 1; int sz = 1;
	
	for(int i=0;i<e;i++){
        int carry = 0;
        for(int j=0;j<sz;j++){
            int t = res[j]*b + carry;
            res[j] = t % 10;
            carry = t / 10;
        }
        while(carry){
            res[sz++] = carry % 10;
            carry /= 10;
        }
    }
	printf("%d^%d = ", b, e);
    for(int i=sz-1;i>=0;i--){
    	textcolor(12);printf("%d", res[i]);
    	Beep(750,t);
	}
    textcolor(7);printf("\n");
}
void funcB(){
	int n,t;
	printf("\n>>> Enter Factrial Number: ");
	scanf("%d", &n);
	printf(">>> Enter BPM: ");
	scanf("%d", &t);
	
	t = 60000/t;
	if(t < 50) t = 50;
    if(t > 2000) t = 2000;
	
	int res[SIZE]; res[0]=1; int sz=1;
	
	for(int i=2;i<=n;i++){
        int carry = 0;
        for(int j=0;j<sz;j++){
            int t = res[j]*i + carry;
            res[j] = t % 10;
            carry = t / 10;
        }
        while(carry){
            res[sz++] = carry % 10;
            carry /= 10;
        }
    }
    printf("%d! = ", n);
    for(int i=sz-1;i>=0;i--) {
    	textcolor(12);printf("%d", res[i]);
    	Beep(750,t);
	}
    textcolor(7);printf("\n");	
}
void funcC(){
    int n, t;
    printf("\n>>> Enter Fibonacci Number: ");
    scanf("%d", &n);
    printf(">>> Enter BPM: ");
    scanf("%d", &t);

    t = 60000 / t;
    if(t < 50) t = 50;
    if(t > 2000) t = 2000;

    int **f = (int**)malloc(sizeof(int*) * (n+1));
    int *sz = (int*)malloc(sizeof(int) * (n+1));
    for(int i = 0; i <= n; i++){
        f[i] = (int*)calloc(SIZE, sizeof(int));
        sz[i] = 0;
    }

    f[0][0] = 0; sz[0] = 1;
    f[1][0] = 1; sz[1] = 1;

    for(int i = 2; i <= n; i++){
        int carry = 0;
        int maxsz = sz[i-1] > sz[i-2] ? sz[i-1] : sz[i-2];
        for(int j = 0; j < maxsz; j++){
            int tmp = f[i-1][j] + f[i-2][j] + carry;
            f[i][j] = tmp % 10;
            carry = tmp / 10;
        }
        sz[i] = maxsz;
        while(carry){
            f[i][sz[i]++] = carry % 10;
            carry /= 10;
        }
    }

    for(int i = 0; i <= n; i++){
    	textcolor(7);printf("Fibonacci %d: ", i);
    	Beep(750, t);
        for(int j = sz[i]-1; j >= 0; j--){
            textcolor(12);printf("%d", f[i][j]);
        }
        printf("\n");
    }
	textcolor(7);
    for(int i = 0; i <= n; i++) free(f[i]);
    free(f);
    free(sz);
}
void funcD(){
	int n, t;
    printf("\n>>> Enter Lucas Number Steps: ");
    scanf("%d", &n);
    printf(">>> Enter BPM: ");
    scanf("%d", &t);

    t = 60000 / t;
    if(t < 50) t = 50;
    if(t > 2000) t = 2000;

    int **f = (int**)malloc(sizeof(int*) * (n+1));
    int *sz = (int*)malloc(sizeof(int) * (n+1));
    for(int i = 0; i <= n; i++){
        f[i] = (int*)calloc(SIZE, sizeof(int));
        sz[i] = 0;
    }

    f[0][0] = 2; sz[0] = 1;  // L0 = 2
    f[1][0] = 1; sz[1] = 1;  // L1 = 1

    // Lucas
    for(int i = 2; i <= n; i++){
        int carry = 0;
        int maxsz = sz[i-1] > sz[i-2] ? sz[i-1] : sz[i-2];
        for(int j = 0; j < maxsz; j++){
            int tmp = f[i-1][j] + f[i-2][j] + carry;
            f[i][j] = tmp % 10;
            carry = tmp / 10;
        }
        sz[i] = maxsz;
        while(carry){
            f[i][sz[i]++] = carry % 10;
            carry /= 10;
        }
    }

    for(int i = 0; i <= n; i++){
    	textcolor(7);printf("Lucas %d: ", i);
    	Beep(750, t);
        for(int j = sz[i]-1; j >= 0; j--){
            textcolor(12);printf("%d", f[i][j]);
            
        }
        textcolor(7);printf("\n");
    }
	textcolor(7);
    for(int i = 0; i <= n; i++) free(f[i]);
    free(f);
    free(sz);
}

int main(){
	char c;
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	printf("\n============================================\n");
	printf("==========   Zeroerror Integer    ==========\n");
	printf("============================================\n");
	printf("Current Time: ");CurrentTime();
	
	textcolor(12);printf("\nHigh Accuracy Zero-Error Module!\n");textcolor(7);
	
	printf("Press any key to start...\n");
    _getch();
    
    while(2147483647){
    	printf("\n>>>Mode: [A]Power [B]Factorial [C]Fibonacci [D]Lucas\n");
    	printf(">>>Select: ");
    	scanf(" %c", &c);
    	
    	if(c>=97 && c<=122) c-=32;
    	
    	switch(c){
    		case 'A': funcA();break;
    		case 'B': funcB();break;
    		case 'C': funcC();break;
    		case 'D': funcD();break;
    		default: return 1;
		}
		pressAnyKey();
	}
}
