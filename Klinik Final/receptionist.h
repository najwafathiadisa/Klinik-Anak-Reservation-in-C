#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct UserStruct{
    char username[10];
    char password[10];
    int queriesDone;
    bool isAdmin;
} User;

void receptionist(User *user);
bool login(User *user);
void reg(User *user);
bool admin(User *user);

// Stat query terjalankan selama program berlangsung
void queriesStat(User user){
    printf("\nYou have done a total of %d queries!", user.queriesDone);
}

// Login dengan username dan password di users.txt
bool login(User *user){
    FILE* fptr;
    char usernameTemp[10], usernameRead[10];
    char passwordTemp[10], passwordRead[10];

    if(NULL == (fptr = fopen("users.txt", "r"))){
        exit(1);
    }

    printf("== LOGIN ==\n");
    printf("Username: ");
    scanf("%s", usernameTemp);
    printf("Password: ");
    scanf("%s", passwordTemp);
	getchar();
	
    while(fscanf(fptr, "%s %s", usernameRead, passwordRead) == 2){
        if(strcmp(usernameRead, usernameTemp) == 0 && strcmp(passwordRead, passwordTemp) == 0){
            fclose(fptr);
            printf("\nLogin successful!\n");
            strcpy(user->username, usernameRead);
            strcpy(user->password, passwordRead);
            return true;
        }
    }

    fclose(fptr);
    printf("\nLogin fail: incorrect username or password.\n");
    return false;
}

// Register dengan username dan password di users.txt
void reg(User *user){
    FILE* fptr;
    char usernameTemp[10], usernameRead[10];
    char passwordTemp[10], passwordRead[10];

    if(NULL == (fptr = fopen("users.txt", "a+"))){
        exit(1);
    }

    printf("== REGISTER ==\n");
    printf("Username: ");
    scanf("%s", usernameTemp);

    while(fscanf(fptr, "%s %s", usernameRead, passwordRead) == 2){
        if(strcmp(usernameRead, usernameTemp) == 0){
            printf("\nRegister fail: duplicate username\n");
            return;
        }
    }

    printf("Password: ");
    scanf("%s", passwordTemp);
	getchar();
	
    fprintf(fptr, "%s %s\n", usernameTemp, passwordTemp);
    fclose(fptr);

    printf("\nRegister successful!\n");
    return;
}

// Login sebagai admin
bool admin(User *user){
	char usernameTemp[10], passwordTemp[10];
    printf("== ADMIN MODE ==\n");
    printf("Username: ");
    scanf("%s", usernameTemp);
    printf("Password: ");
    scanf("%s", passwordTemp);
	getchar();
	
	if(strcmp(usernameTemp, "admin") == 0 && strcmp(passwordTemp, "admin123") == 0){
        printf("\nAdmin mode successful\n");
	    strcpy(user->username, usernameTemp);
	    strcpy(user->password, passwordTemp);
	    user->isAdmin = true;
        return true;
    }

	printf("\nAdmin mode fail: incorrect username or password\n");
    return false;
}

// Menu untuk register, login, dan admin
void receptionist(User *user){
    bool loggedIn = false;
    do{
        int command;
        printf("\n ===========================\n");
        printf("\n ====== Klinik Anakku ======\n");
        printf("\n ===========================\n");
        printf(" --------- WELCOME ---------\n");
        
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Admin mode\n");
        printf("--> =");
        scanf("%d", &command);
        getchar();

        switch(command){
            case 1:
                reg(user);
                break;
            case 2:
                loggedIn = login(user);
                break;
            case 3:
            	loggedIn = admin(user);
            	break;
            default:
                printf("\nInvalid command.");
                break;
        }
    }while(!loggedIn);
}
