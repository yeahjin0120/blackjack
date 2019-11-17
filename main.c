#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30

typedef struct
{
   int order;
   int number;
   char shape[4];
}trump; // Ʈ���� ī�� ����ü �� 


//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;							


//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0; 							//game end flag

//some utility functions

//get an integer input from standard input (keyboard)
//return : input integer value
//         (-1 is returned if keyboard input was not integer)
int getIntegerInput(void) {
    int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}


//card processing functions ---------------

//calculate the actual card number in the blackjack game
void getCardNum(trump m_card[])
{
   char shape[4][10] = { "Spade", "Hart", "Dia", "Club"};
   for (int i = 0; i < 4; i++)
   {
      for (int j = i * 13; j < i * 13 + 13; j++)
      {
         m_card[j].order = i;
         strcpy(m_card[j].shape, shape[i]);
         int k = j % 13 + 1;
         m_card[j].number = k;
      }
   }
}


//print the card information (e.g. DiaA)
void printCard(trump m_card)
{
      printf("%s", m_card.shape);
      if (m_card.number == 11)
         printf("%-2s ", "Jack");
      else if (m_card.number == 12)
         printf("%-2s ", "Queen");
      else if (m_card.number == 13)
         printf("%-2s ", "King");
      else
         printf("%-2d ", m_card.number);
}


//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {

}

//get one card from the tray
int pullCard(void) {
}


//playing game functions -----------------------------

//player settiing
int configUser(void) {
	printf("<<�ڡڡ�YJ BlackJack�ڡڡ�>>\n");
	do{
	printf("Input the number of users(MAX:%d): ", N_MAX_USERS);
	scanf("%d", %n_user);
	if(n_user > N_MAX_USER)
	{
		printf(" Too many player!\n")
	}
	}while(n_user > N_MAX_USER;)
	return n_users;
	}


//betting
int betDollar(void) {
	int i, p_bet, p0_bet; 
	printf("Your betting (total : %d)", N_DOLLAR)
	scanf("%d", &p0_bet);
	
	dollar[0]-=p0_bet;
	printf("user bets %d", p0_bet);
	for (i=1; i<n_user; i++)
	{
		p_bet=(1+rand()%10);
	}
	} 
	printf("")
	
}


//offering initial 2 cards
void offerCards(void) {
	int i;
	//1. give two card for each players
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();
		cardhold[i][1] = pullCard();
	}
	//2. give two card for the operator
	cardhold[n_user][0] = pullCard();
	cardhold[n_user][1] = pullCard();
	
	return;
}

//print initial card status
void printCardInitialStatus(void) {
	
}
int getAction(void) {
	int action;
	printf("\\\Action? (0-go, other integer-stop)");
	scanf("%d", &action);
}


void printUserCardStatus(int user, int cardcnt) {
	int i;
	
	printf("   -> card : ");
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\t ::: ");
}




// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult() {
	
}

int checkResult() {
	int dollar[n_user];
	int max, i;
	max = dollar[0];
	for (i=0; i<n_user; i++)
	{
		if ( dollar[i] > max)
			max= dollar[i]
	}
}

int checkWinner() {
	int dollar[n_user];
	int max,i;
	int winner;
	max = dollar[0];
		for(i=0; i<n_user; i++)
		{
			max = dollar[i];
		}
	
	
}



int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();


	//Game initialization --------
	//1. players' dollar
	
	//2. card tray
	mixCardTray();



	//Game start --------
	do {
		
		betDollar();
		offerCards(); //1. give cards to all the players
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
		//each player's turn
		for () //each player
		{
			while () //do until the player dies or player says stop
			{
				//print current card status printUserCardStatus();
				//check the card status ::: calcStepResult()
				//GO? STOP? ::: getAction()
				//check if the turn ends or not
			}
		}
		
		//result
		checkResult();
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}
