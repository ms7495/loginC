#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define CREDENTIALS_FILE "credentials.txt"

// Structure to hold user information
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

// Function prototypes
void signup(User users[], int *userCount);
void signin(User users[], int userCount);
void saveCredentialsToFile(User users[], int userCount);
void loadCredentialsFromFile(User users[], int *userCount);

int main() {
    User users[MAX_USERS];  // Array to store user data
    int userCount = 0;      // Number of users currently signed up

    loadCredentialsFromFile(users, &userCount);

    int choice;
    do {
        printf("\n1. Sign Up\n");
        printf("2. Sign In\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                signup(users, &userCount);
                break;
            case 2:
                signin(users, userCount);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 3);

    saveCredentialsToFile(users, userCount);

    return 0;
}

void signup(User users[], int *userCount) {
    if (*userCount >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }

    printf("Enter username: ");
    scanf("%s", users[*userCount].username);
    printf("Enter password: ");
    scanf("%s", users[*userCount].password);

    (*userCount)++;

    printf("User signed up successfully.\n");
}

void signin(User users[], int userCount) {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int i;
    for (i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Welcome, %s!\n", username);
            return;
        }
    }
    printf("Invalid username or password.\n");
}

void saveCredentialsToFile(User users[], int userCount) {
    FILE *file = fopen(CREDENTIALS_FILE, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(file);
}

void loadCredentialsFromFile(User users[], int *userCount) {
    FILE *file = fopen(CREDENTIALS_FILE, "r");
    if (file == NULL) {
        printf("No existing credentials file found.\n");
        return;
    }

    while ((*userCount < MAX_USERS) && (fscanf(file, "%s %s", users[*userCount].username, users[*userCount].password) == 2)) {
        (*userCount)++;
    }

    fclose(file);
}
