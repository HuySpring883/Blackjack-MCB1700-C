#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <KBD.h>
#include <GLCD.h>

#define __FI_LARGE 1
#define __FI_SMALL 0

extern void Delay (uint32_t);

// Functions
int funcBlackjack (void);
void menuBlackjack (void);
int selectionManagerBlackjack (void);
int startGame (void);
void printRules (void);
void shuffleDeck (void);
void playerTurn (void);
void dealerTurn (void);
int drawCard (void);
void winCondition (void);

int playerScore = 0;
int dealerScore = 0;
int deck[52];
int deckIndex = 0;

int funcBlackjack (void) {

  // Display menu
  menuBlackjack();

  int selection = selectionManagerBlackjack();

  switch (selection) {
    case 3:
      startGame();
      break;
    case 4:
      printRules();
      break;
    case 5:
      GLCD_Clear();
      GLCD_DisplayString(, "EXITING");
      Delay(100000000);
      break;
  }
}

int selectionManagerBlackjack (void) {
  
}

void menuBlackjack (void) {

  GLCD_Clear(White);
  GLCD_SetBackColor(White);
  GLCD_DisplayString(0, 4, __FI_LARGE, "Blackjack");
  GLCD_DisplayString(3, 3, __FI_LARGE, "Start Game");
  GLCD_DisplayString(4, 3, __FI_LARGE, "Rules");
  GLCD_SetBackColor(Red);
  GLCD_DisplayString(5, 3, __FI_LARGE, "Exit");

}

int startGame (void) {

  GLCD_Clear(White);
  GLCD_DisplayString(0, 4, __FI_LARGE, "Blackjack");
  GLCD_DisplayString(2, 0, __FI_LARGE, "Your Score:");
  GLCD_DisplayString(3, 0, __FI_LARGE, "Dealer Score:");
  
  while (1) {
    // Run game here
    playerTurn();
    dealerTurn();
    winCondition();
  }
}

void printRules (void) {
}

void shuffleDeck (void) {
  
  for (int i = 0; i < 52; i++) {
    if (i < 4)
      deck[i] = 1;
    else if (i < 36)
      deck[i] = (i / 4) + 2;
    else
      deck[i] = 10;
  }
  
  for (int i = 51; i > 0; i--) {
    int j = rand() % (i + 1);
    int temp = deck[i];
    deck[i] = deck[j];
    deck[j] = temp;
  }
  
  deck_index = 0;
  
}

int drawCard (void) {

  if (deckIndex >= 52) {
    shuffleDeck();
  }
  return deck[deckIndex++];
}

void playerTurn (void) {

  while (1) {
    if (get_button() == KBD_LEFT) {
      int card = drawCard();
      playerScore += card;
      char buffer[20];
      sprintf(buffer, "Drew: %d", card);
      GLCD_DisplayString(2, 7 , __FI_LARGE, buffer);

      if (playerScore > 21)
        break;
    }
    if (get_button() == KBD_RIGHT)
      break;
  }
}

void dealerTurn (void) {
  
  while (dealerScore < 17) {
    int card = drawCard();
    dealerScore += card;
    char buffer[20];
    sprintf(buffer, "Drew: %d", card);
    GLCD_DisplayString(2, 7 , __FI_LARGE, buffer);
  }
  
}

void winCondition (void) {
  
  if (playerScore > 21) {
    GLCD_DisplayString(5, 0, __FI_LARGE, "Bust Dealer Wins");
  } else if (dealerScore > 21 || playerScore > dealerScore) {
    GLCD_DisplayString(5, 0, __FI_LARGE, "Player Wins");
  } else {
    GLCD_DisplayString(5, 0, __FI_LARGE, "Dealer Wins");
  }
  
}
