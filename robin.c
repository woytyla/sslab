#include <stdio.h>
#include <stdlib.h>

struct node{
    int id, at, bt, tempbt, ct, tat, wt, isCompleted;
    struct node* next;
};

int front = -1, rear = -1;

struct node* Sort(struct node* head){
    struct node* temp = head;
    while(temp != NULL){
        struct node* temp2 = temp -> next;
        while(temp2 != NULL){
            if(temp2 -> at < temp -> at){
                int id = temp -> id;
                int at = temp -> at;
                int bt = temp -> bt;
                int tempbt = temp -> tempbt;
                temp -> id = temp2 -> id;
                temp -> at = temp2 -> at;
                temp -> bt = temp2 -> bt;
                temp -> tempbt = temp2 -> tempbt;
                temp2 -> id = id;
                temp2 -> at = at;
                temp2 -> bt = bt;
                temp2 -> tempbt = tempbt;
            }
            temp2 = temp2 -> next;
        }
        temp = temp -> next;
    }
    return head;
}

struct node* Create(int n){
    struct node* head = NULL;
    struct node* temp = NULL;
    for(int i = 0; i < n; i++){
        printf("\nPROCESS %d\n\n", i+1);
        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        newNode -> id = i+1;
        printf("Arrival Time: ");
        scanf("%d", &newNode -> at);
        printf("Burst Time: ");
        scanf("%d", &newNode -> bt);
        newNode -> tempbt = newNode -> bt;
        newNode -> isCompleted = 0;

        if(head == NULL){
            head  = temp = newNode;
        }
        else{
            temp -> next = newNode;
            temp = newNode;
        }
        newNode -> next = NULL;
    }
    return Sort(head);
}

void EnQueue(struct node* queue[], struct node* newNode){
    if(front == -1 && rear == -1){
        front = rear = 0;
        queue[rear] = newNode;
    }
    else{
        rear++;
        queue[rear] = newNode;
    }
}

struct node* DeQueue(struct node* queue[]){
    struct node* toReturn = NULL;
    if(front == rear){
        toReturn = queue[front];
        front = rear = -1;
    }
    else{
        toReturn = queue[front];
        front++;
    }
    return toReturn;
}

int isEmpty(struct node* queue[]){
    if(front == -1 && rear == -1) return 1;
    else return 0;
}

int isInQueue(struct node* queue[], struct node* newNode){
    int temp = front, flag = 0;
    while(temp != rear){
        if(queue[temp] == newNode){
            flag = 1;
            break;
        }
        temp++;
    }
    if(flag == 0){
        if(queue[temp] == newNode){
            flag = 1;
        }
    }
    return flag;
}

void Display(struct node* head){
    printf("\nPROCESS\tAT\tBT\tCT\tTAT\tWT\n\n");
    struct node* temp = head;
    while(temp != NULL){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", temp -> id, temp -> at, temp -> bt, temp -> ct, temp -> tat, temp -> wt);
        temp = temp -> next;
    }
}

void CalculateWTandTAT(struct node* head){
    struct node* temp = head;
    while(temp != NULL){
        temp -> tat = (temp -> ct) - (temp -> at);
        temp -> wt = (temp -> tat) - (temp -> bt);
        temp = temp -> next;
    }
}

void ExecuteRoundRobin(struct node* head, int TQ){
    struct node* queue[20];
    int currentCT = 0;
    EnQueue(queue, head);
    while(isEmpty(queue) == 0){
        struct node* currentProcess = DeQueue(queue);
        if(currentProcess -> tempbt <= TQ){
            currentCT += currentProcess -> tempbt;
            currentProcess -> tempbt = 0;
            currentProcess -> ct = currentCT;
            currentProcess -> isCompleted = 1;
        }
        else{
            currentProcess -> tempbt = (currentProcess -> tempbt) - TQ;
            currentCT += TQ;
            struct node* temp = currentProcess -> next;
            while(temp != NULL && (temp -> at <= currentCT) && (temp -> isCompleted == 0)){
                if(isInQueue(queue, temp) == 0) EnQueue(queue, temp);
                temp = temp -> next;
            }
            EnQueue(queue, currentProcess);
        }
    }
    CalculateWTandTAT(head);
    Display(head);
}

void main(){
    printf("Enter total number of processes: ");
    int n;
    scanf("%d", &n);
    struct node* head = Create(n);
    printf("\nEnter time quantum: ");
    int TQ;
    scanf("%d", &TQ);
    ExecuteRoundRobin(head, TQ);
}