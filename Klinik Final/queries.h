#include <stdio.h>
#include <string.h>
#include "employees.h"

void executeBook();
void executeView(const char *object);
void executeSearch(const char *object, const char *arg);
void executeSort(const char *object, const char *arg);
void executeHelp();
void executeSave();
void executeInsert();
void executeRemove(const char *object, const char *arg);
void executeLoad();

// Respons perintah "view"
void executeView(const char *object){
	// view all
    if (object != NULL && strcmp(object, "all") == 0){
		printEmps(head1, false);
    }
    else{
        printf("I don't understand what you want to view.\n");
        printf("\nTry these:\n");
        printf("\tview all\n");
    }
}

// Respons perintah "save"
void executeSave(){
	saveToText(head1);
}

// Respons perintah "book"
void executeBook(){
	int id;
	printf("\nYou are about to book an appointment.\n");
	printf("Lists of available doctors:\n");
	printEmps(head1, true);
	printf("Enter the ID of your preferred doctor: \n");
	printf("--> ");
	scanf("%d", &id);
	getchar();
	Emp *temp = findEmpByID(head1, id);
	if(temp == NULL){
		printf("\nDoctor with ID %d does not exist.", id);
		printf("\nCancelling your appointment...\n");
	}
	else{
		if(temp->isAvailable == 1){
			printf("\nProcessing your request...");
			temp->isAvailable = 0;
			printf("\nYour appointment with Dr. %s is scheduled for tomorrow at 9 P.M.", temp->name);
			printf("\nThank you and get well soon!\n");
			executeSave();
		}
		else{
			printf("\nDoctor with ID %d is not available.", id);
			printf("\nCancelling your appointment...\n");
		}
	}
}


// Respons perintah "insert"
void executeInsert(){
	char name[100];
	int id;
	printf("ID: ");
	scanf("%d", &id);
	if(findEmpByID(head1, id) != NULL){
		printf("\nA doctor with the same id is found.");
		printf("\nCancelling insertion...\n");
		getchar();
		return;
	}
	printf("Name (no spaces): ");
	scanf("%s", name);
	insertAtEnd(&head1, createEmp(name, id, 1));
	printf("\nSuccessfuly inserted Dr. %s - %d.\n", name, id);
	executeSave();
	getchar();
}

// Respons perintah "remove"
void executeRemove(const char *object, const char *arg){
	int id;
	printf("ID: ");
	scanf("%d", &id);
	Emp* emp = findEmpByID(head1, id);
	if(emp != NULL){
		printf("\nSuccessfully removed doctor %s - %d.\n", emp->name, emp->id);
		removeEmp(&head1, emp->id);
		executeSave();
	}
	else{
		printf("\nID %d not found.", id);
		printf("\nCancelling removal...\n");
	}
	getchar();
}

// Respons perintah "load"
void executeLoad(){
	loadFromText(&head1);
}

// Respons perintah "sort"
void executeSort(const char *object, const char *arg){
	// sort id asc
    if (object != NULL && arg != NULL && strcmp(object, "id") == 0 && strcmp(arg, "asc") == 0){
    	sortEmp(head1, 1);
    }
    // sort id desc
    else if(object != NULL && arg != NULL && strcmp(object, "id") == 0 && strcmp(arg, "desc") == 0){
    	sortEmp(head1, 2);
	}
	// sort name asc
	else if(object != NULL && arg != NULL && strcmp(object, "name") == 0 && strcmp(arg, "asc") == 0){
    	sortEmp(head1, 3);
	}
	// sort name desc
	else if(object != NULL && arg != NULL && strcmp(object, "name") == 0 && strcmp(arg, "desc") == 0){
    	sortEmp(head1, 4);
	}
	// sort available asc
	else if(object != NULL && arg != NULL && strcmp(object, "available") == 0 && strcmp(arg, "asc") == 0){
    	sortEmp(head1, 5);
	}
	// sort available desc
	else if(object != NULL && arg != NULL && strcmp(object, "available") == 0 && strcmp(arg, "desc") == 0){
    	sortEmp(head1, 6);
	}
    else{
        printf("I don't understand what you want to sort.\n");
        printf("\nTry these:\n");
        printf("\tsort name asc\n");
        printf("\tsort id desc\n");
        printf("\tsort available desc\n");
    }
}

// Respons perintah "help"
void executeHelp(){
	printf("Glad you asked for help! :)\n");
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

// Respons perintah "search"
void executeSearch(const char *object, const char *arg){
	// search name arg
    if (object != NULL && arg != NULL && strcmp(object, "name") == 0){
		printf("%-10s %-4s %-10s\n", "Name", "ID", "Available");
    	Emp *temp = findEmpByName(head1, arg);
    	bool found = false;
    	while(temp != NULL){
			printEmp(temp);
			temp = findEmpByName(temp->next, arg);
			found = true;
		}
		if(!found){
			printf("\nNo doctors contain the word \"%s\" in their name\n", arg);
		}
	}
	// search id arg
	else if(object != NULL && atoi(arg) != 0 && strcmp(object, "id") == 0){
		printf("%-10s %-4s %-10s\n", "Name", "ID", "Available");
    	Emp *emp = findEmpByID(head1, atoi(arg));
    	if(emp != NULL){
    		printEmp(emp);
		}
		else{
			printf("\nDoctor with ID %d not found\n", atoi(arg));
		}
	}
    else{
        printf("I don't understand what you want to search.\n");
        printf("\nTry these:\n");
        printf("\tsearch name En\n");
        printf("\tsearch id 91\n");
    }
}

