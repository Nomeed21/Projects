// Money Manager
/*Pseudocode:
    Input current allowance
    (Permanent) Input percentages you want to allot 
        e.g. Daily money, savings\emergency funds, Wants, Growth
    Daily journal on what you spend today
    Input spent today
    Remaining = currentallowance - spenttoday
    Update remaining
    Update alloted money for each category.
 */

#include <stdio.h>
#include <unistd.h>

#define DATA_PATH "/home/xonicskt21/tools/files/allowance.bin" 
void menu();
void showCurrent();
void showPercentages();
void getAllowance();
void calculateCurrent();
void getSpentToday();
void save();


//initialize
typedef struct {
    float allowance;
    char day[20];
} Current;

typedef struct {
    float needs;
    float savings;
    float growth;
    float wants;
} Percent;

Current readget = {0.00, "No_Date"};
Percent percent = {0.00, 0.00, 0.00, 0.00};

void loadFile() {
    FILE *fptr = fopen(DATA_PATH, "rb");
     if (fptr == NULL ) {
        printf("File not found!\n");
        printf("Creating new file...\n");
        sleep(1);
        fptr = fopen(DATA_PATH, "wb");       
    }
    if (fptr == NULL) {
        printf("Error handling file\n");
        return;
    }
    fread(&readget, sizeof(Current), 1, fptr); 
    fclose(fptr);

    FILE *fpr = fopen(DATA_PATH, "rb");
     if (fptr == NULL ) {
        printf("File not found!\n");
        printf("Creating new file...\n");
        sleep(1);
        fpr = fopen(DATA_PATH, "wb");       
    }
    if (fpr == NULL) {
        printf("Error handling file\n");
        return;
    }
    fread(&percent, sizeof(Percent), 1, fpr); 
    fclose(fpr);

}



//start of the program
int main() {
   menu();
    return 0;
}
//


void  menu() {
    
    int choice;
    system("reset");
    system("nano financial_record.txt");
    showCurrent();
    do {
    printf("[1] Spendings Today\n[2] Stipend Release\n[3] Reset Allowance\n[4] Refresh Allowance\n[5]Exit\n");
    scanf("%d", &choice);
    getchar();
    switch (choice) {
	case 1:
      	getSpentToday();
  	break;
	
 	case 2:
 	getAllowance();
	break;
	
	case 3:
	readget.allowance = 0;
   	calculateCurrent();
	save();
	break;
	
	case 4:
	loadFile();
	readget.allowance = percent.needs + percent.wants + percent.savings + percent.growth;
    	save();
 	break;

 	case 5:
	break;

	default:
	printf("Invalid option!\n");

    }
    system("reset");
    showCurrent();
    } while (choice != 5);
}



void showCurrent() {
    
    loadFile();
    for (int i = 0; i < 10; i++) {
	printf("**");	
    }
    printf("\nCurrent allowance:  %.2f\n", readget.allowance);
    printf("Last date updated = %s\n\n", readget.day);
    
    for (int i = 0; i < 10; i++) {
        printf("**");   
    }    
    showPercentages();
    sleep(1);
    printf("\nPress any key to continue...\n");
    getchar(); 

}

void getAllowance() {
    float stip;
    printf("Enter your stipend received: ");
    scanf("%f", &stip);
    getchar();
    readget.allowance += stip;
    calculateCurrent();
    save();
}


void getSpentToday() {
    float today;
    int ded;
    char date[50];
    printf("How much did you spent today???:   ");
    scanf("%f", &today);
    printf("Where do you want to deduct it?\n");
    printf("  [1] Needs\n  [2] Growth\n  [3] Wants\n");
    scanf("%d", &ded);
    getchar();
    switch (ded) {
	case 1:
	percent.needs -= today;
	break;
	
	case 2:
	percent.growth -= today;
	break;

	case 3:
	percent.wants -= today;
	break;
	
	case 4:
	percent.savings -= today;
	break;
	
	default:
	printf("Invalid option\n");

    }
    readget.allowance -= today;
    save();
}
void calculateCurrent() {
    percent.needs = readget.allowance * 0.5;
    percent.savings =  readget.allowance * 0.3;
    percent.growth =  readget.allowance * 0.1;
    percent.wants =  readget.allowance * 0.1;
    save();
}

void save() {
FILE *fptr = fopen(DATA_PATH, "wb");
        if (fptr == NULL) {
            printf("Error accessing file");     

        }
    fwrite(&readget, sizeof(Current), 1, fptr);
    fclose(fptr);

FILE *fpr = fopen(DATA_PATH, "wb");
        if (fpr == NULL) {
            printf("Error accessing file");     

        }
    fwrite(&percent, sizeof(Percent), 1, fpr);
    fclose(fpr);
}

void showPercentages() {
    printf("\nAlloted allowance:\n");
    sleep(1);
    printf(" NEEDS (50%%): %.2f\n", percent.needs);
    printf("    %.f Days left (if P200/day) \n", percent.needs/ 200);
    sleep(2);
    printf(" SAVINGS (30%%): %.2f\n", percent.savings);
    sleep(1);
    printf(" GROWTH (10%%): %.2f\n", percent.growth);
    sleep(1);
    printf(" WANTS (10%%): %.2f\n", percent.wants);
    sleep(1);

}
