#include <stdio.h>
#include <windows.h>
#include <conio.h>
#define MAX 16

void bubbleSort(int arr[], int n) {
    int i, j, tmp, r;
    int max = 900, min = 200;
    
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-1-i; j++){
            if(arr[j] > arr[j+1]){
            	//swap
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
		}
		textcolor(7);printf("BubbleSort Rotation %d: ", i+1);
        for(int j=0; j<n; j++) {
        	textcolor(12);printf("%d ", arr[j]);
		}
		r = min + rand() % (max - min + 1);
		Beep(r, 300);
        printf("\n");
	}
	textcolor(7);printf("\n");
}

void insertionSort(int arr[], int n) {
    int key, r, j;
    int max = 600, min = 300;
    
    for(int i=1; i<n; i++){
        key = arr[i];
        j = i-1;
        //swap
        while(j>=0 && arr[j]>key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1]=key;
        
        textcolor(7);printf("InsertionSort Rotation %d: ", i);
        for(int j=0; j<n; j++){
        	textcolor(10);printf("%d ", arr[j]);
		}
		r = min + rand() % (max - min + 1);
		Beep(r, 300);
        printf("\n");
    }
    textcolor(7);printf("\n");
}

void selectionSort(int arr[], int n) {
    int min_idx, tmp, r;
    int max = 750, min = 250;
    
    for(int i=0; i<n-1; i++){
        min_idx = i;
        for(int j=i+1; j<n; j++){
        	if(arr[j] < arr[min_idx]) {
			min_idx = j;
			}
		}
		//swap
	    tmp = arr[i];
	    arr[i] = arr[min_idx];
	    arr[min_idx] = tmp;
        
        textcolor(7);printf("SelectionSort Rotataion %d: ", i+1);
        for(int j=0; j<n; j++){
			textcolor(9);printf("%d ", arr[j]);		
		}
		r = min + rand() % (max - min + 1);
		Beep(r, 300);
        printf("\n");
    }
    textcolor(7);printf("\n");
}

void reverseArray(int *arr, int size){
	int *ptr = arr; //start
	int *pptr = arr + size - 1; //end
	int temp, step = 1;
	
	printf("\n======== Reverse Array Process ========\n\n");
	while(ptr < pptr){
		temp = *ptr;
		*ptr = *pptr;
		*pptr = temp;
		
		printf("Reverse Step %d: ", step++);
		for(int *p=arr; p<arr+size; p++){
			textcolor(rand()%16);
			printf("%d ", *p);
		}
		Beep(250+rand()%500,300);
		textcolor(7);
		printf("\n");
		ptr++;
		pptr--;
	}
	printf("\n=======================================\n\n");
	
}

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

void clear(){
    system("cls");
}

int main(){
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	
	int size, count, num; char menu;
	int arr[MAX], bub[MAX], ins[MAX], sel[MAX];
	
	printf("\n============================================\n");
	printf("=========== Array Control System ===========\n");
	printf("============================================\n");
	printf("Current Time: ");CurrentTime();
	printf("Press any key to start...\n");
    _getch();
    
    printf("\n>>> Enter Array Size: ");
    scanf(" %d", &size);
    printf(">>> Enter Array Elements: ");
	for(int i=0; i<size; i++) {
		scanf(" %d",&arr[i]);
	}
    count = size;
    clear();
    while(1){
		printf("================ \n");
		printf("      Menu \n");
		printf("================ \n");
		printf("Current Array: ");
		
		printf("| ");
		textcolor(12);
		for(int i=0; i<count; i++) printf("%d ", arr[i]);
		textcolor(7);
		printf("|\n");
		
		printf("\nI: Insert Elements\n");
		printf("D: Delete Elements\n");
		printf("F: Format Array\n");
		printf("S: Sorting Current Array\n");
		printf("R: Reverse Array\n");
		printf("Q: Quit");
		printf("\n\n>>> Select: ");
		scanf(" %c", &menu);
		
		if(menu>=97&&menu<=122) menu-=32; //toupper
		
		switch(menu) {
			case 'I': {
				if(count>=MAX){
					printf("This array is full! :(\n");
					Sleep(1000);
					break;
				}
				printf("\nInsert Number: ");
				scanf(" %d", &num);
				
				int d=0; //Duplication Cheak
				for(int k=0;k<count;k++){
					if(arr[k] == num){
						d=1;
						break;
					}
				}
				if(d){
					printf("Duplicate value! Cannot insert :(\n");
					Sleep(1000);
					clear();
					break;
				}
				
				int i;
				for(i=0; i<count; i++){
					if(arr[i] > num) break;
				}
				
				for(int j=count; j>i; j--){
					arr[j] = arr[j-1];
				}
				arr[i] = num;
				count++;
				Sleep(500);
				clear();
				break;	
			}			
			case 'D':{
				printf("\nDelete Number: ");
				scanf(" %d", &num);
				int i;
				for(i=0; i<count; i++){
					if(arr[i] == num) break;
				}
				
				if(i==count){
					printf("No Such Number. :(\n");
					Sleep(1000);
					clear();
					break;
				}
				
				for(int j=i; j<count-1; j++){
					arr[j] = arr[j+1];
				}
				count--;
				Sleep(500);
				clear();
				break;
			}
			case 'F':{
				char confirm;
				printf("\nWarning! All data will be deletd. Are you sure? (Y/N): ");
				scanf(" %c", &confirm);
				if(confirm == 'Y' || confirm == 'y'){
					for(int i=0; i<count; i++) arr[i] = 0;
					count=0;size=0;
					printf("\nArray formatted successfully! (All data cleared)\n");
					Sleep(1000);
	        		clear();
				} else {
					printf("\nFormat canceled.\n");
        			Sleep(800);
        			clear();
				}
				break;
			}
			case 'S':{
				size = count;
				for(int i=0;i<size;i++){
					bub[i]=arr[i];
					ins[i]=arr[i];
					sel[i]=arr[i];
				}
				printf("\n======== Array Sorting Result ========\n");
				bubbleSort(bub, size);
				insertionSort(ins, size);
				selectionSort(sel, size);
				
				for(int i=0;i<size;i++){
					arr[i]=bub[i];
					arr[i]=ins[i];
					arr[i]=sel[i];
				}
				
				printf("\nPress any key to continue... ");
				int ch = getch();
				
    			Sleep(1000);
				clear();
				break;
			}
			case 'R':{
				size = count;
				reverseArray(arr, size);
				printf("\nPress any key to continue... ");
				int ch = getch();
				Sleep(1000);
				clear();
				break;
			}
			case 'Q':{
				printf("\nGood Bye~ ");
				return 0;
			}
			default: {
				printf("Invalid Option.!");
				Sleep(1000);
				clear();
				break;
			}				
		}
	}
}
