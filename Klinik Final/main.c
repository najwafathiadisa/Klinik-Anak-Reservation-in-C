#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "receptionist.h"
#include "queryexec.h"
//Proyek Akhir kelompok 15
//Najwa Fathiadisa - 2106654391
// Rian Abrar Makarim - 2106708242

// input buffer
static char input[100] = "greet";

// --> contoh input
static bool getInput(void){
    printf("\n--> ");
    return fgets(input, sizeof input, stdin) != NULL;
}

int main(){
	// Emp ada di employees.h
	Emp *temp;
	loadFromText(&head1);
	
	// User ada di receptionist.h
    User user = { 
		.username = "", 		
		.password = "", 
		.isAdmin = false,  
		.queriesDone = 0
	};
	
	// Fitur register, login, & admin
    receptionist(&user);
    // ref: https://helderman.github.io/htpataic/htpataic02.html
    printf("\n== MENU QUERY ==\n");
    // Selama blm quit, minta input
    while (queryAndExec(input, user.isAdmin) && getInput())
		user.queriesDone++;
    printf("\nBye!\n");
    queriesStat(user);
    
    deallocate(&head1);
    return 0;
}
