// Header untuk swap. Baru digunakan di employees.h

void swapInt(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void swapString(char **a, char **b){
    char *temp = *a;
    *a = *b;
    *b = temp;
}
