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



void printUserCardStatus(int user, int cardcnt)
{
   printf("   -> card : ");
   for (int i = 0; i < cardcnt; i++)
   {
      printCard(cardhold[user][i]);
   }
}






