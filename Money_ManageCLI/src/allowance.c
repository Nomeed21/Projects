/**
 * Project: Personal Money Manager CLI
 * Description: A simple financial tracker that allocates income into specific 
 * buckets (Needs, Savings, Growth, Wants) and tracks expenses.
 * Author: [Your Name]
 * Date: 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Configuration
#define DATA_FILE "finance_data.bin"
#define LOG_FILE "transaction_log.txt"

// Data Structures
typedef struct {
    float totalAllowance;
    float needs;
    float savings;
    float growth;
    float wants;
    char lastUpdated[26]; // To hold ctime string
} FinancialState;

// Function Prototypes
void loadData(FinancialState *state);
void saveData(FinancialState *state);
void updateDate(FinancialState *state);
void displayMenu();
void showStatus(FinancialState *state);
void addIncome(FinancialState *state);
void addExpense(FinancialState *state);
void resetData(FinancialState *state);
void clearScreen();
void pauseConsole();

int main() {
    FinancialState wallet = {0}; // Initialize with zeros
    int choice;

    // Load existing data or initialize new
    loadData(&wallet);

    do {
        clearScreen();
        // Auto-update date on startup
        updateDate(&wallet); 
        
        showStatus(&wallet);
        displayMenu();
        
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            // Handle non-integer input to prevent infinite loops
            while(getchar() != '\n'); 
            choice = 0; 
        }
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                addExpense(&wallet);
                break;
            case 2:
                addIncome(&wallet);
                break;
            case 3:
                resetData(&wallet);
                break;
            case 4:
                printf("\nExiting and saving...\n");
                saveData(&wallet);
                break;
            default:
                printf("\nInvalid option! Please try again.\n");
                pauseConsole();
        }

    } while (choice != 4);

    return 0;
}

// --- core Logic Functions ---

void loadData(FinancialState *state) {
    FILE *file = fopen(DATA_FILE, "rb");
    if (file == NULL) {
        printf("No previous data found. Creating new wallet...\n");
        updateDate(state);
        // Initialize safe defaults
        state->totalAllowance = 0;
        state->needs = 0;
        state->savings = 0;
        state->growth = 0;
        state->wants = 0;
        return;
    }
    fread(state, sizeof(FinancialState), 1, file);
    fclose(file);
}

void saveData(FinancialState *state) {
    FILE *file = fopen(DATA_FILE, "wb");
    if (file == NULL) {
        perror("Error saving data"); // Professional error reporting
        return;
    }
    fwrite(state, sizeof(FinancialState), 1, file);
    fclose(file);
    printf("Data saved successfully.\n");
}

void updateDate(FinancialState *state) {
    time_t t;
    time(&t);
    // ctime returns a string with a newline at the end, we strip it
    char *timeStr = ctime(&t);
    timeStr[strcspn(timeStr, "\n")] = 0; 
    strcpy(state->lastUpdated, timeStr);
}

void addIncome(FinancialState *state) {
    float amount;
    printf("\n--- ADD INCOME ---\n");
    printf("Enter amount received: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount.\n");
        pauseConsole();
        return;
    }

    // Update Total
    state->totalAllowance += amount;

    // Allocation Strategy (50/30/10/10 Rule)
    state->needs   += amount * 0.50;
    state->savings += amount * 0.30;
    state->growth  += amount * 0.10;
    state->wants   += amount * 0.10;

    printf("\nAmount allocated:\n");
    printf("Needs (50%%):   +%.2f\n", amount * 0.50);
    printf("Savings (30%%): +%.2f\n", amount * 0.30);
    printf("Growth (10%%):  +%.2f\n", amount * 0.10);
    printf("Wants (10%%):   +%.2f\n", amount * 0.10);
    
    saveData(state);
    pauseConsole();
}

void addExpense(FinancialState *state) {
    float amount;
    int category;
    
    printf("\n--- ADD EXPENSE ---\n");
    printf("Amount spent: ");
    scanf("%f", &amount);
    
    if (amount <= 0) {
        printf("Invalid amount.\n");
        pauseConsole();
        return;
    }

    printf("Deduct from:\n [1] Needs\n [2] Savings\n [3] Growth\n [4] Wants\nChoice: ");
    scanf("%d", &category);

    int success = 1;
    switch (category) {
        case 1: state->needs   -= amount; break;
        case 2: state->savings -= amount; break;
        case 3: state->growth  -= amount; break;
        case 4: state->wants   -= amount; break;
        default: 
            printf("Invalid Category.\n"); 
            success = 0;
            break;
    }

    if (success) {
        state->totalAllowance -= amount;
        
        // Optional: Log to text file for history
        FILE *log = fopen(LOG_FILE, "a");
        if (log != NULL) {
            fprintf(log, "Spent %.2f from category %d on %s\n", amount, category, state->lastUpdated);
            fclose(log);
        }
        
        printf("Transaction recorded.\n");
        saveData(state);
    }
    pauseConsole();
}

void resetData(FinancialState *state) {
    char confirm;
    printf("\nWARNING: This will wipe all financial data. Continue? (y/n): ");
    getchar(); // Clear buffer
    scanf("%c", &confirm);
    
    if (confirm == 'y' || confirm == 'Y') {
        state->totalAllowance = 0;
        state->needs = 0;
        state->savings = 0;
        state->growth = 0;
        state->wants = 0;
        saveData(state);
        printf("Wallet reset.\n");
    } else {
        printf("Cancelled.\n");
    }
    pauseConsole();
}

// --- UI Functions ---

void showStatus(FinancialState *state) {
    printf("=========================================\n");
    printf("      FINANCIAL DASHBOARD\n");
    printf("      %s\n", state->lastUpdated);
    printf("=========================================\n");
    printf(" TOTAL BALANCE:   PHP %.2f\n", state->totalAllowance);
    printf("-----------------------------------------\n");
    printf(" [Needs]   : %.2f  (%.0f days @ P200/day)\n", state->needs, state->needs/200);
    printf(" [Savings] : %.2f\n", state->savings);
    printf(" [Growth]  : %.2f\n", state->growth);
    printf(" [Wants]   : %.2f\n", state->wants);
    printf("=========================================\n");
}

void displayMenu() {
    printf("\nActions:\n");
    printf(" [1] Record Expense\n");
    printf(" [2] Add Income/Stipend\n");
    printf(" [3] Reset Wallet\n");
    printf(" [4] Save & Exit\n");
}

void clearScreen() {
    // Portable clear screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseConsole() {
    printf("\nPress Enter to continue...");
    while(getchar() != '\n'); // flush buffer
    getchar(); // wait for input
}
