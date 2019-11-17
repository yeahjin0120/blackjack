#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N_CARDSET         1
#define N_CARD            52
#define N_DOLLAR         50


#define N_MAX_CARDNUM      13
#define N_MAX_USER         5
#define N_MAX_CARDHOLD      10
#define N_MAX_GO         17
#define N_MAX_BET         5

#define N_MIN_ENDCARD      30

//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;							



/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int configUser(void) {
	printf("<<¡Ú¡Ú¡ÚYJ BlackJack¡Ú¡Ú¡Ú>>\n");
	do{
	printf("Input the number of users(MAX:%d): ", N_MAX_USER);
	scanf("%d", &n_user);
	if(n_user > N_MAX_USER)
	{
		printf(" Too many player!\n")
	}
	}while(n_user > N_MAX_USER;)
	return n_users;
	}


//betting
int betDollar(void)
{
   srand((unsigned int)time(NULL));
   printf("------- BETTING STEP -------\n");
   printf("  -> your betting (total:$%d) : ", dollar[0]);
   scanf("%d", &bet[0]);
   for (int i = 1; i < n_user; i++)
   {
    	bet[i] = (rand() % 5) + 1;
    	printf("player%d bets $%d (out of $%d)\n", i, bet[i], dollar[i]);
   }
   printf("----------------------------\n");
}

