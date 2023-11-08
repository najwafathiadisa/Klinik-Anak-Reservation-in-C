#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "queries.h"

// Parser input. Dihandle lebih lanjut di queries.h dan employee.h
bool queryAndExec(char *input, bool isAdmin){
    char *verb = strtok(input, " \n");
    char *object = strtok(NULL, " \n");
    char *arg = strtok(NULL, " \n");

    if (verb != NULL){
        if (strcmp(verb, "quit") == 0){
            return false;
        }
        else if (strcmp(verb, "book") == 0){
        	if(isAdmin) printf("\nAdmin can\'t book an appointment.\n");
        	else executeBook();
        }
        else if (strcmp(verb, "view") == 0){
            executeView(object);
        }
        else if (strcmp(verb, "search") == 0){
            executeSearch(object, arg);
        }
        else if (strcmp(verb, "sort") == 0){
            executeSort(object, arg);
        }
        else if (strcmp(verb, "help") == 0){
            executeHelp();
        }
        else if (strcmp(verb, "greet") == 0){
            printf("Hello there!\n");
			printf("There are 11 things you can do:\n");
			printf("--> book : books an appointment. Get well soon!\n");
			printf("--> view : views the whole LL. Try it!\n");
			printf("--> search : searches the LL. Try it!\n");
			printf("--> sort : sorts the LL. Try it!\n");
			printf("--> help : helps you! :D\n");
			printf("--> greet : greets you!\n");
			printf("--> clear : clears terminal. Squeaky clean!\n");
			printf("--> save : saves the LL to \"employee.txt\" file. Admin mode only\n");
			printf("--> insert : inserts a doctor to the LL. Admin mode only\n");
			printf("--> remove : removes a doctor from the LL. Admin mode only\n");
			printf("--> load : loads the LL from \"employee.txt\" file. Admin mode only\n");				
			printf("--> quit : gives a temporary goodbye :(...\n");
        }
        else if (strcmp(verb, "clear") == 0){
            system("cls");
        }
        else if (strcmp(verb, "save") == 0){
        	if(isAdmin) executeSave();
        	else printf("\nSorry, you are not an admin.\n");
        }
        else if (strcmp(verb, "insert") == 0){
        	if(isAdmin) executeInsert();
        	else printf("\nSorry, you are not an admin.\n");
        }
        else if (strcmp(verb, "remove") == 0){
        	if(isAdmin) executeRemove(object, arg);
        	else printf("\nSorry, you are not an admin.\n");
        }
        else if (strcmp(verb, "load") == 0){
        	if(isAdmin) executeLoad();
        	else printf("\nSorry, you are not an admin.\n");
        }
        else{
            printf("I don't know how to '%s'.\n", verb);
        }
    }
    return true;
}
