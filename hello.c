#include <stdio.h>
#include <string.h>
// there is no database management used in this, reset ho jayega agar ek bar refresh kiya toh 💀💀
// Bank account ki information ke liye ek structure define kar rahe hain
struct BankAccount {
    int accountNumber;    // Account number
    char name[100];       // Account holder ka naam
    float balance;        // Account ka balance
};

// Function prototypes
void createAccount(struct BankAccount accounts[], int *numAccounts);
void deposit(struct BankAccount accounts[], int numAccounts);
void withdraw(struct BankAccount accounts[], int numAccounts);
void checkBalance(struct BankAccount accounts[], int numAccounts);
int findAccount(struct BankAccount accounts[], int numAccounts, int accountNumber);

int main() {
    struct BankAccount accounts[100];  // 100 bank accounts store karne ke liye ek array
    int numAccounts = 0;  // Ab tak banaye gaye accounts ki sankhya
    int choice;

    do {
        // User ke liye menu dikhaya ja raha hai
        printf("\n--- Bank Management System ---\n");
        printf("1. Account banaaye\n");
        printf("2. Paise jama karne hai?\n");
        printf("3. Paise nikaalein\n");
        printf("4. Balance check karne hai?\n");
        printf("5. Exit karne hai?\n");
        printf("Apna choice de: ");
        scanf("%d", &choice);

        // User ke choice ke anusaar operation perform karne hai?
        switch (choice) {
            case 1:
                createAccount(accounts, &numAccounts);  // Naya account banane ka function
                break;
            case 2:
                deposit(accounts, numAccounts);        // Paise jama karne ka function
                break;
            case 3:
                withdraw(accounts, numAccounts);       // Paise nikaalne ka function
                break;
            case 4:
                checkBalance(accounts, numAccounts);   // Balance check karne ka function
                break;
            case 5:
                printf("System se exit ho rahe hain.\n"); // Exit case
                break;
            default:
                printf("Invalid choice! Phir se try karne hai?.\n");
        }
    } while (choice != 5);  // Jab tak user exit nahi karta, program chalega

    return 0;
}

// Naya account banane ka function
void createAccount(struct BankAccount accounts[], int *numAccounts) {
    struct BankAccount newAccount;
    // User se account number le rahe hain
    printf("Account number de: ");
    scanf("%d", &newAccount.accountNumber);
    // User se account holder ka naam le rahe hain
    printf("Account holder ka naam de: ");
    getchar();  // Buffer mein bacha newline character clear karte hain
    fgets(newAccount.name, sizeof(newAccount.name), stdin);
    newAccount.name[strlen(newAccount.name) - 1] = '\0';  // Newline character hata rahe hain
    newAccount.balance = 0.0;  // Starting balance 0 rahega

    accounts[*numAccounts] = newAccount;  // Naya account array mein add kar rahe hain
    (*numAccounts)++;  // Accounts ki sankhya badha rahe hain

    printf("Account successfully bana diya gaya!\n");
}

// Paise jama karne ka function
void deposit(struct BankAccount accounts[], int numAccounts) {
    int accountNumber;
    float amount;
    // User se account number le rahe hain jisme paise jama karne hain
    printf("Account number de: ");
    scanf("%d", &accountNumber);

    int index = findAccount(accounts, numAccounts, accountNumber);  // Account dhoondhte hain
    if (index != -1) {
        // User se deposit karne wali amount le rahe hain
        printf("Jitni amount deposit karni hai wo de: ");
        scanf("%f", &amount);
        if (amount > 0) {
            accounts[index].balance += amount;  // Balance mein paise jod rahe hain
            printf("Deposit successful! New balance: %.2f\n", accounts[index].balance);
        } else {
            printf("Amount positive honi chahiye!\n");
        }
    } else {
        printf("Account nahi mila!\n");
    }
}

// Paise nikaalne ka function
void withdraw(struct BankAccount accounts[], int numAccounts) {
    int accountNumber;
    float amount;
    // User se account number le rahe hain jisme se paise nikalne hain
    printf("Account number de: ");
    scanf("%d", &accountNumber);

    int index = findAccount(accounts, numAccounts, accountNumber);  // Account dhoondhte hain
    if (index != -1) {
        // User se withdrawal ke liye amount le rahe hain
        printf("Jitni amount withdraw karni hai wo de: ");
        scanf("%f", &amount);
        if (amount > 0 && amount <= accounts[index].balance) {
            accounts[index].balance -= amount;  // Balance mein se paise ghat rahe hain
            printf("Withdrawal successful! New balance: %.2f\n", accounts[index].balance);
        } else {
            printf("Insufficient balance ya galat amount!\n");
        }
    } else {
        printf("Account nahi mila!\n");
    }
}

// Account balance check karne ka function
void checkBalance(struct BankAccount accounts[], int numAccounts) {
    int accountNumber;
    // User se account number le rahe hain jiska balance check karna hai
    printf("Account number de: ");
    scanf("%d", &accountNumber);

    int index = findAccount(accounts, numAccounts, accountNumber);  // Account dhoondhte hain
    if (index != -1) {
        printf("Account holder: %s\n", accounts[index].name);
        printf("Current balance: %.2f\n", accounts[index].balance);  // Balance dikhate hain
    } else {
        printf("Account nahi mila!\n");
    }
}

// Account ko account number ke base pe dhoondhne ka function
int findAccount(struct BankAccount accounts[], int numAccounts, int accountNumber) {
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return i;  // Account mil gaya
        }
    }
    return -1;  // Agar account nahi milta to -1 return karte hain
}
