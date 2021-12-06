#ifndef CLAIM_CLAIM_H
#define CLAIM_CLAIM_H

#include "raylib.h"

struct node
{
    int level;
    char type;
    Image imageCard;
    Texture2D textureCard;
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
void unloadsImages(Stack *D, Stack *P1, Stack *P2);
Stack *extraImages();
void unloadsExtraImages(Stack *eI);
void rotateImage(Node *tC);
//Stack *loadDeck(Stack *D);
//Stack *loadP1(Stack *P1);
//Stack *loadP2(Stack *P2);

void itsGoTimeBBY(Stack *D, Stack *V1, Stack *V2, Stack *P1, Stack *P2, Stack *P1R2, Stack *P2R2, Stack *eI, int AI);
void round2(Stack *D, Stack *V1, Stack *V2,Stack *P1R2, Stack *P2R2, Stack *eI, int AI);
int claimWinner(Stack *V1, Stack *V2, Stack *eI);

void drawStart();
void drawMode(Stack *eI);
void drawTable(Stack *P, Stack *eI);
void displayDeckCard(Node *tC);
void displayPDeck(Stack *P, Stack *eI);
void displaySelect(Node *nT, Node *nT2);
void drawRound2(Stack *eI);
void Winner(Stack *eI, int w, int AI);
void displayRules(Stack *eI);

#endif
