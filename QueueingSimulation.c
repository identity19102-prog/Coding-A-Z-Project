#include <stdio.h>
#include <windows.h>

#define MAX 12

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

typedef struct Node {
	int data;
	struct Node *next;
} Node;

typedef struct Queue {
	Node *front;
	Node *rear;
	int size;
} Queue;

//init queue
void initQ(Queue *ptr){
	ptr->front = ptr->rear = NULL; //NULL -> rear -> front 
	ptr->size = 0;
}

void showQ(Queue *ptr){
	Node *curr = ptr->front;
	int count = 0;
	
	printf("\nCurrent Queue: [");
	while(count < MAX){
		if(curr){
			if(curr == ptr->front) {
				textcolor(12);
				printf("%d", curr->data);
				textcolor(7);
			}
			else if(curr == ptr->rear) {
				textcolor(10);
				printf("%d", curr->data);
				textcolor(7);
				}
			else {
				textcolor(11);
				printf("%d", curr->data);
				textcolor(7);
			}
			curr = curr -> next;
		} else {
			printf(" ");
		}
		if(count != MAX-1) printf("|");
		count++;
	}
	printf("]\n\n");
}

void enq(Queue *ptr, int val){
	system("cls");
	if(ptr->size >= MAX){
		textcolor(12);
		printf("Queue is full! :(\n");
		textcolor(7);
		Sleep(1000);
		system("cls");
		showQ(ptr);
		return;
	}
	
	Node *pptr = (Node*)malloc(sizeof(Node)); //pptr = new node
	pptr->data = val;
	pptr->next = NULL;
	
	if(!ptr->rear){// queue is not full
		ptr->front = ptr->rear = pptr;
	}
	else {
		ptr->rear->next = pptr;
		ptr->rear = pptr;
	}
	ptr->size++;
	showQ(ptr);
}

void deq(Queue *ptr){
	system("cls");
	if(!ptr->front){
		textcolor(12);
		printf("Queue is empty! :(\n");
		textcolor(7);
		Sleep(1000);
		system("cls");
		showQ(ptr);
		return;
	}
	
	Node *temp = ptr->front;
	printf("Dequeued: %d\n", temp->data);
	ptr->front = ptr->front->next;
	
	if(!ptr->front){
		ptr->rear = NULL;
	}
	
	free(temp);
	ptr->size--;
	showQ(ptr);
}

void formatQ(Queue *ptr){
	while(ptr->front){
		deq(ptr);
	}
	printf("Queue cleared.\n");
	Sleep(1000);
	system("cls");
}

int main(){
	int num;
	char menu;
	Queue ptr;
	initQ(&ptr);
	SetConsoleOutputCP(65001); // UTF-8
    SetConsoleCP(65001);

    printf("\n\n============================================\n");
    printf("======== Queueing Simulation Program =======\n");
    printf("============================================\n");
    printf("Current Time: "); CurrentTime();

    printf("\nPress any key to start...");
    _getch();
    system("cls");
    
    while(32767){
    	printf("#################### Menu ###################\n");
    	printf("#                                           #\n");
    	printf("# [E]Enqueue  [D]Dequeue  [F]Format [Q]Exit #\n");
    	printf("#                                           #\n");
    	printf("#############################################\n");
        printf("Select: ");
        scanf(" %c", &menu);
        
        if(menu>=97 && menu<=122) menu-=32;
        
        switch(menu){
        	case 'E':{
        		printf("Enter value: ");
                scanf(" %d", &num);
                enq(&ptr,num);
				break;
			}
			case 'D':{
				deq(&ptr);
				break;
			}
			case 'F':{
				printf("Execute Format queue? (0/1)");
				scanf(" %d", &num);
				if(num==1) formatQ(&ptr);
				system("cls");
				showQ(&ptr);
				break;
			}
			case 'Q':{
				return 0;
			}
		}
	}
}
