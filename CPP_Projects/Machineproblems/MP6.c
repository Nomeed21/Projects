#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 5

char nameA[MAX][50];
int quiz1A[MAX], quiz2A[MAX], quiz3A[MAX];
int last = -1;

void addRecord(char name[], int quiz1, int quiz2, int quiz3);
void delRecord(char name[]);
void updateRecord(char name[]);
void display();
int locate(char name[]);
int locatePos(float ave);
int isEmpty();
int isFull();
int menu();
void save();
void retrieve();


int main(){
    int quiz1, quiz2, quiz3;
    char name[50];
    retrieve();
    
    while(1){
        switch(menu()){
            case 1:
            printf("Input name: ");
            scanf(" %[^\n]", name);
            if(locate(name) > -1){
                printf("Duplicate Found!");
                system("pause");
            }
            else{
                printf("Input Quiz 1: ");
                scanf("%d", &quiz1);
                printf("Input Quiz 2: ");
                scanf("%d", &quiz2);
                printf("Input Quiz 3: ");
                scanf("%d", &quiz3);
                addRecord(name, quiz1, quiz2, quiz3);
                system("pause");
            }
            break;
            
            case 2:
            printf("Input name: ");
            scanf(" %[^\n]", name);
            delRecord(name);
            system("pause");
            break;
            
            case 3:
            printf("Input name: ");
            scanf(" %[^\n]", name);
            delRecord(name);
            system("pause");
            break;
            
            case 4:
            display();
            system("pause");
            break;
            
            case 5:
            save();
            exit(0);
            break;
            
            default:
            printf("Invalid choice!!\n 1-5 only\n");
            while(getchar() != '\n');   
            system("pause");
            
            
        }
    }
    
    
    
    return 0;
}

void save(){
    FILE *fp;
    fp = fopen("Records.csv", "w");
    
    if (fp == NULL){
        printf("Error File Handling\n");
    }
    else{
        for(int i = 0; i <= last; i++){
            fprintf(fp, "%s,%d,%d,%d\n", nameA[i], quiz1A[i], quiz2A[i], quiz3A[i]);
        }
    }
    
    fclose(fp);
    
}

void retrieve(){
    FILE *fp;
    fp = fopen("Records.csv", "r");
    int quiz1, quiz2, quiz3;
    char name[50], line[80];
    
    if(fp == NULL){
        printf("Error File handling\n");
    }
    else{
        while(fgets(line, sizeof(line), fp)){
            sscanf(line, "%[^,],%d,%d,%d", name, quiz1, quiz2, quiz3);
            addRecord(name, quiz1, quiz2, quiz3);
        }
    }
    fclose(fp);
}

void addRecord(char name[], int quiz1, int quiz2, int quiz3){
    int index;
    float ave;
    if(isFull()){
        printf("Array Full!!");
        system("pause");
    }
    else{
        
        last++;
        ave = (float) (quiz1 + quiz2 + quiz3) / 3.0;
        index = locatePos(ave);
        
        for(int i = last; i >= index; i--){
            strcpy(nameA[i + 1], nameA[i]);
            quiz1A[i+1] = quiz1A[i];
            quiz2A[i+1] = quiz2A[i];
            quiz3A[i+1] = quiz3A[i];
        }
            strcpy(nameA[index], name);
            quiz1A[index] = quiz1;
            quiz2A[index] = quiz2;
            quiz3A[index] = quiz3;
            
        printf("Successfully Recorded!\n Name: %s\n Quiz1: %d\n Quiz2: %d\n Quiz 3: %d\n", nameA[last], quiz1A[last], quiz2A[last], quiz3A[last]);
    }
}
void delRecord(char name[]){
    int index;
    if(isEmpty()){
        printf("Nothing to delete!...\n");
        system("pause");
    }
    else {
        index = locate(name);
        for(int i = index; i<=last; i++){
            strcpy(nameA[i + 1], nameA[i]);
            quiz1A[i] = quiz1A[i+1];
            quiz2A[i] = quiz2A[i+1];
            quiz3A[i] = quiz3A[i+1];
        }
        last--;
    }
}
int locatePos(float ave){
    int i;
    for (i = 0; i<last; i++){
        float average = (quiz1A[i] + quiz2A[i] + quiz3A[i]) / 3;
        if (average > ave) return i;
    }
    return i;
}

void updateRecord(char name[]){
    int index, choice, num;
    float ave;
    if(isEmpty()){
        printf("Nothing to update!...\n");
        system("pause");
    }
    else {
        index = locate(name);
        num = 0;
        while(1){
            ave = (float)(quiz1A[index] + quiz2A[index] +quiz3A[index]) / 3;
            printf("Current Record: %s\n", nameA[index]);
            printf("Quiz 1: %d\n", quiz1A[index]);
            printf("Quiz 2: %d\n", quiz2A[index]);
            printf("Quiz 3: %d\n", quiz3A[index]);
            printf("Average: %d\n", ave);
            printf("Update Menu: \n");
            printf("[1]Quiz 1\n[2]Quiz 2\n[3]Quiz 3\n[4]Exit\n");
            printf("Select your choice: ");
            scanf("%d", &choice);
            switch(choice){
                case 1:
                printf("Input new score: ");
                scanf("%d", &num);
                quiz1A[index] = num;
                break;
                case 2:
                printf("Input new score: ");
                scanf("%d", &num);
                quiz2A[index] = num;
                break;
                case 3:
                printf("Input new score: ");
                scanf("%d", &num);
                quiz3A[index] = num;
                break;
                case 4:
                return;
                break;
                default:
                printf("1-4 choices only!\n");
            }
        }
        
    }
}
void display(){
    float ave;
    
    if (isEmpty()){
        printf("Nothing to Display...\n");
        system("pause");
    }
    else{
        printf("%10s %-10s %6s %6s %6s %6s %6s\n", "No.", "Name", "Quiz 1", "Quiz2", "Quiz3", "Average", "Remarks");
        for(int i = 0; i<= last; i++){
            ave = (float)(quiz1A[i] + quiz2A[i] +quiz3A[i]) / 3;
            printf("%10d %-10s %6d %6d %6d %6.2f %6s\n", i+1, nameA[i], quiz1A[i], quiz2A[i], quiz3A[i], ave, ave >= 75? "Passed": "Failed");
        }
    }
}
int locate(char name[]){
    int i;
    for( i = 0; i<= last; i++){
        if(strcmp(nameA[i], name) == 0) return i;
    }
    return -1;
}
int isEmpty(){
    return last == -1;
}
int isFull(){
    return last == MAX -1;
}
int menu(){
    int ch;
    printf("MAIN MENU:\n");
    printf("1.Add Record\n");
    printf("2.Delete Record\n");
    printf("3.Update Record\n");
    printf("4.Display Record\n");
    printf("5. Exit\n");
    printf("Select your choice: ");
    scanf("%d", &ch);
    return ch;
}