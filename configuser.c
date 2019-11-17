#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int configUser(void) {
	int num;
	do{
	printf("The number df users:");
	scanf("%d", num);
	}while(num > 5);

}

