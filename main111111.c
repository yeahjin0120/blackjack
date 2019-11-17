#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int configUser(void) {
	int num;
	do{
	printf("The number of users:");
	scanf("%d", num);
	}while(num > 5);

}
