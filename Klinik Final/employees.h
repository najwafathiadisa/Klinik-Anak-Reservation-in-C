#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include "strcasestr.h"
#include "swap.h"

typedef struct Employee {
	char *string;
    char *name;
    int id;
    int isAvailable;
    struct Employee *next;
} Emp;

void printEmp(Emp *emp);
void printEmps(Emp *head, bool onlyAvailables);
Emp *createEmp(char name[], int id, int isAvailable);

Emp *findEmpByID(Emp *head, int id);
Emp *findEmpByName(Emp *head, const char *substr);

void insertAtHead(Emp **head, Emp *newEmp);
void insertAtEnd(Emp **head, Emp *newEmp);
void removeEmp(Emp **head, int id);
void saveToText(Emp *head);
void loadFromText(Emp **head);
int countEmp(Emp *head);
void swapEmps(Emp *a, Emp *b);
void sortEmp(Emp *head, int mode);
void deallocate(Emp **head);

Emp *head1 = NULL;

// Print 1 employee
void printEmp(Emp *emp){
	printf("%-10s %-4d %-10s\n", 
	emp->name, emp->id,
	// ternary operator ? :
	emp->isAvailable == 1 ? "Yes" : "No");
}

// Print LL
void printEmps(Emp *head, bool onlyAvailables){
	printf("%-10s %-4s %-10s\n", "Name", "ID", "Available");
	#pragma omp parallel
	{
		Emp *temp = head;
		#pragma omp single
		{
			while (temp != NULL) {
				#pragma omp task firstprivate(temp)
				{
					#pragma omp critical
					if(onlyAvailables){
						if(temp->isAvailable == 1){
							printEmp(temp);
						}
					}
					else{
						printEmp(temp);
					}
				}
				temp = temp->next;
			}
		}
	}
	printf("\n");
}

// Bikin 1 employee
Emp *createEmp(char name[], int id, int isAvailable){
	Emp *emp = (Emp *)malloc(sizeof(Emp));
	emp->name = strdup(name);
	emp->id = id;
	emp->isAvailable = isAvailable;
	emp->next = NULL;
	return emp;
}

// Tambahin employee di awal LL
void insertAtHead(Emp **head, Emp *newEmp){
	newEmp->next = *head;
	*head = newEmp;
}

// Tambahin employee di akhir LL
void insertAtEnd(Emp **head, Emp *newEmp){
	if(*head == NULL){
		*head = newEmp;
		return;
	}
	
	Emp *curr;
	for(curr = *head; curr->next != NULL; curr = curr->next);
	curr->next = newEmp;
}

// Menghapus 1 employee
void removeEmp(Emp **head, int id){
	if(*head == NULL) return;
	
	if((*head)->id == id){
		Emp *toRemove = *head;
		*head = (*head)->next;
		free(toRemove);
		return;
	}
	
	for(Emp *curr = *head; curr->next != NULL; curr = curr->next){
		if(curr->next->id == id){
			Emp *toRemove = curr->next;
			curr->next = curr->next->next;
			free(toRemove);
			return;
		}
	}
}

// Mencari 1 employee dengan id tertentu
Emp *findEmpByID(Emp *head, int id){
	for(Emp *temp = head; temp != NULL; temp = temp->next)
		if(temp->id == id) 
			return temp;
	return NULL;
}

// Mencari 1 employee dengan substring nama tertentu
Emp *findEmpByName(Emp *head, const char *substr){
	for(Emp *temp = head; temp != NULL; temp = temp->next)
		if(strcasestr(temp->name, substr) != NULL) 
			return temp;
	return NULL;
}

// Menghapus memori LL
void deallocate(Emp **head){
	for(Emp *temp = *head; temp != NULL; temp = temp->next){
		Emp *toBeFreed = temp;
		free(toBeFreed);
	}
	*head = NULL;
}

// Menyimpan LL ke employee.txt
void saveToText(Emp *head){
	FILE * file = fopen("employee.txt", "w");
	if(file == NULL) exit(1);
	// ref: https://stackoverflow.com/questions/49801820/trying-to-process-linked-list-data-in-parallel-with-openmp
	#pragma omp parallel
	{
		Emp *temp = head;
		#pragma omp single
		{
			while (temp != NULL) {
				#pragma omp task firstprivate(temp)
				{
					#pragma omp critical
					fprintf(file, "%s;%d;%d\n", temp->name, temp->id, temp->isAvailable);
				}
				temp = temp->next;
			}
		}
	}
	fclose(file);
}

// Memuat LL dari employee.txt
void loadFromText(Emp **head){
	FILE * file = fopen("employee.txt", "r");
	if(file == NULL) exit(2);
	
	deallocate(head);
	
	char line[30];
	while(fgets(line, sizeof(line), file)){
		Emp *temp = (Emp*)malloc(sizeof(Emp));
		temp->string = strdup(line);
		temp->name = strtok(temp->string, ";");
		temp->id = atoi(strtok(NULL, ";"));
		temp->isAvailable = atoi(strtok(NULL, ";"));
		temp->next = NULL;
		insertAtEnd(head, temp);
	}
	fclose(file);
}

// Menghitung jumlah employee di LL
int countEmp(Emp *head){
	int count = 0;
	for(Emp *temp = head; temp != NULL; temp = temp->next)
		count++;
	return count;
}

// Menukar employee. Digunakan di sorting
void swapEmps(Emp *a, Emp *b){
	swapInt(&a->id, &b->id);
	swapInt(&a->isAvailable, &b->isAvailable);
	swapString(&a->name, &b->name);
	swapString(&a->string, &b->string);
}

// Sorting employee dengan 6 mode
void sortEmp(Emp *head, int mode){
    for(Emp *i = head; i->next != NULL; i = i->next){
    	for(Emp *j = i->next; j != NULL; j = j->next){
    		// ID naik
    		if(mode == 1){
    			if(i->id >= j->id){
	    			swapEmps(i, j);
				}
			}
			// ID turun
			else if(mode == 2){
    			if(i->id <= j->id){
	    			swapEmps(i, j);
				}
			}
			// name naik
			else if(mode == 3){
    			if(strcmpi(i->name, j->name) > 0){
    				swapEmps(i, j);
				}
			}
			// name turun
			else if(mode == 4){
    			if(strcmpi(i->name, j->name) < 0){
    				swapEmps(i, j);
				}
			}
			// available naik
    		else if(mode == 5){
    			if(i->isAvailable > j->isAvailable){
	    			swapEmps(i, j);
				}
			}
			// available turun
			else if(mode == 6){
    			if(i->isAvailable < j->isAvailable){
	    			swapEmps(i, j);
				}
			}
		}
	}
}

