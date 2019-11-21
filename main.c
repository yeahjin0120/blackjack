#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N_CARDSET         	1
#define N_CARD            	52
#define N_DOLLAR         	50


#define N_MAX_CARDNUM      	13
#define N_MAX_USER         	5
#define N_MAX_CARDHOLD      10
#define N_MAX_GO         	17
#define N_MAX_BET         	5
#define N_MIN_ENDCARD      	30

typedef struct
{
   int order;
   int number;
   char shape[3];
}trump; //create trump struct

//card tray object
trump CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;


//player info
int dollar[N_MAX_USER];                  //dollars that each player has
int n_user;                           	//number of users


//play yard information
trump cardhold[N_MAX_USER + 1][N_MAX_CARDHOLD];   //cards that currently the players hold
int cardCount[N_MAX_USER + 1];  	//The total number of cards you currently have
int cardSum[N_MAX_USER];               //sum of the cards
int bet[N_MAX_USER];                  //current betting 
int gameEnd = 0;                      //game end flag

//card processing functions ---------------



int sum(int sum, int num)
{
   sum += num;
   return sum;
}


int main(int argc, char *argv[]) 
{
   int roundIndex = 0;
   int max_user;

   trump Trump;		// call trump card

   //set the number of players
   configUser();


   //Game initialization --------
   //1. players' dollar
   
   for (int i = 0; i < n_user; i++)
   {
      dollar[i] = N_DOLLAR;
   } // reset all player money to 50.

   //2. card tray
   mixCardTray();
   //mix card 


   //Game start --------
	do {
    	for (int i = 0; i < n_user+1; i++)
        {
         cardCount[i] = 2;
         cardSum[i] = 0;
        }

      roundIndex++;
      printf("\n------------------------------------------------------\n");
      printf("------------- Round %d (cardIndex:%d)-----------------\n\n", roundIndex, cardIndex);

      betDollar();
      offerCards(); //1. give cards to all the players

      printCardInitialStatus();
      printf("\n------------------ GAME start --------------------------\n");

      //your turn
      printf(">>> my turn! -----------------\n");
      int i = 0;
      int myAction = 0;
      while (myAction == 0) //do until the player dies or player says stop
         {
         //print current card status printUserCardStatus();
         printUserCardStatus(i, cardCount[i]);
         //check the card status ::: calcStepResult()
         switch (calcStepResult(i))
         {
         case 1:
            //GO? STOP? ::: getAction()
            myAction = getAction();
            if (myAction == 0)
            {
               cardhold[i][cardCount[i]] = pullCard();
               cardSum[i] = sum(cardSum[i], cardhold[i][cardCount[i]].number);
               cardCount[i]++;
               break;
            }
         case 2:
            dollar[i] -= bet[i];
            printf("::: DEAD (sum:%d) --> -$%d, ($%d)\n\n", cardSum[i], bet[i], dollar[i]);
            myAction = 1;
            break;
         case 3:
            dollar[i] += (bet[i] * 2);
            printf("::: Black Jack! Congratulation, you win!! --> +$%d ($%d)\n\n", bet[i], dollar[i]);
            myAction = 1;
            break;
         }
         //check if the turn ends or not
      }

      //each player's turn
      int eachAction;
      for (int i = 1; i < n_user; i++) //each player
      {
         eachAction = 0;
         printf("\n\n>>> player %d turn! ------------\n", i);
         while (eachAction == 0) //do until the player dies or player says stop
         {
            //print current card status printUserCardStatus();
            printUserCardStatus(i, cardCount[i]);
            //check the card status ::: calcStepResult()
            switch (calcStepResult(i))
            {
            case 1:
               //GO? STOP? ::: getAction()
               if (cardSum[i] >= 17) 
               {
                  eachAction = 1;
                  printf("  ::: STAY! ");
                  printf("\n");
                  break;
               }
               else
               {
                  printf("  ::: Go! ");
                  eachAction = 0;
                  cardhold[i][cardCount[i]] = pullCard(); // give a card to player 
                  cardSum[i] = sum(cardSum[i], cardhold[i][cardCount[i]].number);
                  cardCount[i]++;
                  printf("\n");
                  break;
               }
            case 2:
               dollar[i] -= bet[i];
               printf("  ::: DEAD (sum:%d) --> -$%d, ($%d)\n", cardSum[i], bet[i], dollar[i]);
               eachAction = 1;
               break;
            case 3:
               dollar[i] += (bet[i] * 2);
               printf("  ::: Black Jack! \n");
               eachAction = 1;
               break;
            }
            //check if the turn ends or not
         }
      }
      

      //server's turn
      printf("\n\n>>> server turn! -----------------\n");
      i = n_user;
      eachAction = 0;
      while (eachAction == 0) //do until the player dies or player says stop
      {
         //print current card status printUserCardStatus();
         printUserCardStatus(i, cardCount[i]);
         //check the card status ::: calcStepResult()
         switch (calcStepResult(i))
         {
         case 1:
            //GO? STOP? ::: getAction()
            if (cardSum[i] > 16) // µô·¯ ±ÔÄ¢ÀÓ!
            {
               eachAction = 1;
               printf("  ::: STAY! ");
               printf("\n");
               break;
            }
            else
            {
               printf("  ::: Go! ");
               eachAction = 0;
               cardhold[i][cardCount[i]] = pullCard();
               cardSum[i] = sum(cardSum[i], cardhold[i][cardCount[i]].number);
               cardCount[i]++;
               printf("\n");
               break;
            }
         case 2:
            printf("  ::: DEAD \n");
            eachAction = 1;
            break;
         case 3:
            printf("  ::: Black Jack!\n");
            eachAction = 1;
            break;
         }
      }
      printf("[[[[[[[ server result is ...  %d ]]]]]]]\n", cardSum[n_user]);

      //result
      printf("\n---------------- Round %d result ....\n", roundIndex);
      checkResult();


   } while (gameEnd == 0);

   //checkWinner();


   return 0;
}
