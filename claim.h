#ifndef CLAIM_CLAIM_H
#define CLAIM_CLAIM_H

#include "raylib.h"

struct node
{
    int level;
    char type;
    char card[16];
    struct node *next;
};

typedef struct node Node;

struct stack
{
    Node *head;
    int cN;
    int t;
};

typedef struct stack Stack;

Stack *newDeck();
Stack *newPlayer(Stack *D);

void itsGoTimeBBY(Stack *D, Stack *V1, Stack *V2, Stack *P1, Stack *P2, Stack *P1R2, Stack *P2R2);
void round2(Stack *D, Stack *V1, Stack *V2,Stack *P1R2, Stack *P2R2);
void claimWinner(Stack *V1, Stack *V2);

//void displayD(Stack * D);
void drawStart();
void drawTable(Stack *P);
void displayDeckCard(Node *tC);
void displayPDeck(Stack *D, Stack *P, Node *tC);
void displaySelect(Stack *D, Node *pC);

int selectCard();

#endif