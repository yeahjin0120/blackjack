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

//calculate the actual card number in the blackjack game
void getCardNum(trump m_card[])
{
   char shape[4][10] = { "SPD", "HRT", "DIA", "CLV" };
   for (int i = 0; i < 4; i++)
   {
      for (int j = i * 13; j < i * 13 + 13; j++)
      {
         m_card[j].order = i;
         strcpy(m_card[j].shape, shape[i]);
         int k = j % 13 +1;
         m_card[j].number =k;
         if(m_card[j].number > 10)
         {
            m_card[j].number =10; // J,Q,K cards are considered 10
         }
      }
   }
}

//card array controllers -------------------------------

//mix the card sets and put in the array
void mixCardTray()
{
   //shuffle the cards into a CardTray array using a random function
   printf(" --> card is mixed and put int to the tray\n");
   getCardNum(CardTray);
   int rnd;
   trump temp;
   srand((unsigned)time(NULL));
   for (int i = 0; i < 52; i++)
   {
      rnd = rand() % 52;
      temp = CardTray[rnd];
      CardTray[rnd] = CardTray[i];
      CardTray[i] = temp;
   }
   printf("All mixed.\n");
}

//get one card from the tray
trump pullCard(void) 
{
   return CardTray[cardIndex++]; //Divide one by one from the card tray
}
//playing game functions -----------------------------

//player settiing
int configUser(void) {
   printf("<<¡Ú¡Ú¡ÚYJ BlackJack¡Ú¡Ú¡Ú>>\n");
   do
	{
      if (n_user > N_MAX_USER)
      {
         printf("Too many player!\n");
      }
      printf("Input the number of players (MAX:%d) : ", N_MAX_USER);
      scanf("%d", &n_user);
      //determine number of players 
	} while (n_user > N_MAX_USER);
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
      bet[i] = (rand() % 5) + 1; //determine betting amount from 1 to 5
      printf("player%d bets $%d (out of $%d)\n", i, bet[i], dollar[i]);
   }
   printf("----------------------------\n");
}


//offering initial 2 cards
void offerCards(void) {
   int i;
   //1. give two card for each players
   for (i = 0; i < n_user; i++)
   {
      cardhold[i][0] = pullCard();
      cardSum[i] = sum(cardSum[i], cardhold[i][0].number);
      cardhold[i][1] = pullCard();
      cardSum[i] = sum(cardSum[i], cardhold[i][1].number);
   }
   //2. give two card for the operator
   cardhold[n_user][0] = pullCard();
   cardSum[n_user] = sum(cardSum[n_user], cardhold[n_user][0].number);
   cardhold[n_user][1] = pullCard();
   cardSum[n_user] = sum(cardSum[n_user], cardhold[n_user][1].number);
   return;
}

//print the card information (e.g. DiaA)
void printCard(trump m_card)
{
    printf("%s", m_card.shape);
    if (m_card.number == 1)
        printf("%-2s", "A"); 
    else if (m_card.number == 11)
        printf("%-2s ", "Jack");
    else if (m_card.number == 12)
        printf("%-2s ", "Queen");
    else if (m_card.number == 13)
    	printf("%-2s ", "King");
    else
        printf("%-2d ", m_card.number);
}

//print initial card status
void printCardInitialStatus(void) {
   printf(" --------- CARD OFFERING ---------\n");
   printf(" --- server       : X "); 
   printCard(cardhold[n_user][1]); //Only second card revealed
   printf("\n");

   printf("   -> you         : "); // your turn
   printCard(cardhold[0][0]); printCard(cardhold[0][1]); printf("\n");

   for (int i = 1; i < n_user; i++)
   {
      printf("   -> player %d    : ", i);
      printCard(cardhold[i][0]); printCard(cardhold[i][1]); printf("\n");
   }
   printf("\n");
}

int getAction(void) 
{
   int actionNum;
   printf("::: Action? (0 - go, others - stay) :");
   scanf("%d", &actionNum);
   return actionNum;
}


void printUserCardStatus(int user, int cardcnt)
{
   printf("   -> card : ");
   for (int i = 0; i < cardcnt; i++)
   {
      printCard(cardhold[user][i]);
   }
}


// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult(int player) {
   // 1. under 21, 2. over 21, 3. blackjack
   if (cardSum[player] < 21)
   {
      return 1;
   }
   else if (cardSum[player] > 21)
   {
      return 2;
   }
   else if (cardSum[player] == 21)
   {
      return 3;
   }
}

int checkResult() 
{
   for (int i = 0; i < n_user; i++)
   {
      if (i == 0)
      {
         printf("   --> your result : ");
      }
      else
      {
         printf("   --> %d'th player's result : ",i);
      }

      if (cardSum[i] > 21)
      {
         printf("lose due to overflow! ($%d)\n", dollar[i]);
      }
      else if (cardSum[n_user] > 21)
      {
         dollar[i] += bet[i];
         printf("win (sum:%d) --> ($%d)\n", cardSum[i], dollar[i]);
      }
      else if (cardSum[i] == cardSum[n_user])
      {
         printf("Draw.. (sum:%d) --> ($%d)\n", cardSum[i], dollar[i]);
      }
      else if (cardSum[i] == 21)
      {
         printf("BlackJack!! (sum:%d) --> ($%d)\n", cardSum[i], dollar[i]);
      }
      else if (cardSum[i] > cardSum[n_user])
      {
         dollar[i] += bet[i];
         printf("win (sum:%d) --> ($%d)\n", cardSum[i], dollar[i]);
      }
      else if (cardSum[i] < cardSum[n_user])
      {
         dollar[i] -= bet[i];
         printf("lose! (sum:%d) --> ($%d)\n", cardSum[i], dollar[i]);
      }
      
   }
   printf("\n\n");
}

//int checkWinner() {
//
//}



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
