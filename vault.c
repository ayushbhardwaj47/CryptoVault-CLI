#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct {
    char website[50];
    char identifier[50]; 
    char password[50];
} Credential;

void xorCipher(char *str) {
    char key = 'A'; 
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] ^= key;
    }
}

void printDynamicBanner(char *username) {
    char upperName[50];
    strcpy(upperName, username);
    for(int i = 0; upperName[i] != '\0'; i++) {
        upperName[i] = toupper(upperName[i]);
    }
    printf("\n==================================================\n");
    printf("             %s'S SECURE VAULT             \n", upperName);
    printf("==================================================\n");
}

void analyzeStrength(char *pass) {
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    for(int i = 0; pass[i] != '\0'; i++) {
        if(isupper(pass[i])) hasUpper = 1;
        else if(islower(pass[i])) hasLower = 1;
        else if(isdigit(pass[i])) hasDigit = 1;
        else hasSpecial = 1;
    }
    int score = hasUpper + hasLower + hasDigit + hasSpecial;
    
    printf("Strength: [");
    for(int i = 0; i < 4; i++) {
        if(i < score) printf("==");
        else printf("  ");
    }
    printf("] ");
    if(score < 2) printf("Weak (Add numbers/symbols)\n");
    else if(score == 2) printf("Fair\n");
    else if(score == 3) printf("Good\n");
    else printf("Strong\n");
}

void sortVault(Credential *vault, int count) {
    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            if(strcmp(vault[j].website, vault[j+1].website) > 0) {
                Credential temp = vault[j];
                vault[j] = vault[j+1];
                vault[j+1] = temp;
            }
        }
    }
}

void generatePassword(char *buffer, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
    for (int i = 0; i < length; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        buffer[i] = charset[key];
    }
    buffer[length] = '\0';
}

int main() {
    srand(time(NULL)); 
    int capacity = 2; 
    int count = 0;
    int choice;
    char inputBuffer[50];
    
    char username[50], masterPin[50], decoyPin[50], recoveryWord[50]; 

    printf("==================================================\n");
    printf("        WELCOME TO SECURE VAULT SETUP             \n");
    printf("==================================================\n");
    
    printf("Enter your Name: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Create your Master PIN: ");
    fgets(masterPin, sizeof(masterPin), stdin);
    masterPin[strcspn(masterPin, "\n")] = '\0';

    printf("Create a DECOY PIN (Fake PIN for emergencies): ");
    fgets(decoyPin, sizeof(decoyPin), stdin);
    decoyPin[strcspn(decoyPin, "\n")] = '\0';

    printf("Set a Recovery Word (If you forget PIN): ");
    fgets(recoveryWord, sizeof(recoveryWord), stdin);
    recoveryWord[strcspn(recoveryWord, "\n")] = '\0'; 

    printf("\n[+] Setup Complete! Your vault is now secured.\n");

    Credential *vault = (Credential *)malloc(capacity * sizeof(Credential));

    while(1) { 
        printDynamicBanner(username);
        printf("1. Add Manual Password\n");
        printf("2. Generate Strong Password\n");
        printf("3. View All Passwords (SECURED)\n");
        printf("4. Exit & Lock\n");
        printf("~$: ");
        
        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) break;
        if (sscanf(inputBuffer, "%d", &choice) != 1) continue;

        switch(choice) { 
            case 1:
            case 2:
                if (count >= capacity) {
                    capacity *= 2;
                    vault = (Credential *)realloc(vault, capacity * sizeof(Credential));
                }

                printf("Enter App/Website Name: ");
                fgets(vault[count].website, 50, stdin);
                vault[count].website[strcspn(vault[count].website, "\n")] = '\0';

                printf("Enter linked Username/Email/Phone: ");
                fgets(vault[count].identifier, 50, stdin);
                vault[count].identifier[strcspn(vault[count].identifier, "\n")] = '\0';

                if (choice == 1) {
                    printf("Enter Password: ");
                    fgets(vault[count].password, 50, stdin);
                    vault[count].password[strcspn(vault[count].password, "\n")] = '\0';
                    analyzeStrength(vault[count].password);
                } else {
                    generatePassword(vault[count].password, 12);
                    printf("[+] Auto-Generated Password: %s\n", vault[count].password);
                    analyzeStrength(vault[count].password);
                }

                xorCipher(vault[count].password);
                printf("[+] Saved securely to vault!\n");
                count++;
                break;

            case 3:
                printf("Re-enter PIN to unlock: ");
                fgets(inputBuffer, sizeof(inputBuffer), stdin);
                inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

                int isDecoy = 0;

                if (strcmp(inputBuffer, decoyPin) == 0) {
                    isDecoy = 1;
                    printf("\n[!] WARNING: Decoy PIN detected. Booting fake environment...\n");
                } 
                else if (strcmp(inputBuffer, masterPin) != 0) {
                    printf("[-] Incorrect PIN! Forgot PIN? (y/n): ");
                    char forgotChoice[10];
                    fgets(forgotChoice, sizeof(forgotChoice), stdin);
                    
                    if (forgotChoice[0] == 'y' || forgotChoice[0] == 'Y') {
                        printf("Security Question: What is your secret recovery word?\nAnswer: ");
                        fgets(inputBuffer, sizeof(inputBuffer), stdin);
                        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';
                        
                        if (strcmp(inputBuffer, recoveryWord) == 0) {
                            printf("[+] Verification Successful! Enter new Master PIN: ");
                            fgets(masterPin, 50, stdin);
                            masterPin[strcspn(masterPin, "\n")] = '\0';
                            printf("[+] PIN Reset Complete! Please select Option 3 again.\n");
                        } else {
                            printf("[-] Wrong Recovery Word! Security lockdown initiated.\n");
                        }
                    }
                    break; 
                }

                printf("\n--- SECURE DATA ---\n");

                if (isDecoy) {
                    printf("[1] Facebook   | ID: ayush123       | Pass: password123\n");
                    printf("[2] Instagram  | ID: user_ayush     | Pass: qwerty\n");
                    printf("[3] Email      | ID: test@email.com | Pass: admin000\n");
                    break;
                }

                if (count == 0) {
                    printf("[-] Vault is empty.\n");
                    break;
                }

                sortVault(vault, count); 

                for (int i = 0; i < count; i++) {
                    xorCipher(vault[i].password); 
                    printf("[%d] %-12s | ID: %-15s | Pass: %s\n", i+1, vault[i].website, vault[i].identifier, vault[i].password);
                    xorCipher(vault[i].password); 
                }
                break;

            case 4:
                free(vault); 
                printf("[*] Memory cleared. Vault locked. Goodbye, %s!\n", username);
                return 0;

            default:
                printf("[-] Invalid command.\n");
        }
    }
    return 0;
}
