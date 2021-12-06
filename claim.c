#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "claim.h"
#include "stack.h"
#include "raylib.h"

Stack *extraImages()
{
    Stack *n = newStack();
    Node *tempNode = malloc(sizeof(Node));

    //cargar gameMode
    tempNode->type = 'G';
    tempNode->level = 7;
    tempNode->imageCard = LoadImage("cards/game_mode.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    //cargar backCard180
    tempNode->type = 'B';
    tempNode->level = 6;
    tempNode->imageCard = LoadImage("cards/back.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    //cargar Rules
    tempNode->type = 'R';
    tempNode->level = 5;
    tempNode->imageCard = LoadImage("cards/rules.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    //cargar Winner
    tempNode->type = 'W';
    tempNode->level = 4;
    tempNode->imageCard = LoadImage("cards/Winner.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    //cargar round2
    tempNode->type = 'R';
    tempNode->level = 3;
    tempNode->imageCard = LoadImage("cards/R2.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    //cargar P2
    tempNode->type = 'P';
    tempNode->level = 2;
    tempNode->imageCard = LoadImage("cards/P2.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    //cargar P1
    tempNode->type = 'P';
    tempNode->level = 1;
    tempNode->imageCard = LoadImage("cards/P1.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    //cargar cardBack
    tempNode->type = 'P';
    tempNode->level = 1;
    tempNode->imageCard = LoadImage("cards/fback.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    //cargar tablero
    tempNode->type = 'T';
    tempNode->level = 0;
    tempNode->imageCard = LoadImage("cards/Tablero.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    return n;
}

void drawStart()
{
    Color backGround = {23, 32, 42, 255};
    Color textStart = {219, 182,0, 255};
    ClearBackground(backGround);
    DrawText("Claim", 500, 250, 250, WHITE);
    DrawText("BY PABLITO & SEBAS", 700, 480, 20, WHITE);
    DrawText("Press enter to START", 450, 600, 60, textStart);
    DrawText("Press shift for RULES", 565, 673, 40, YELLOW);

}

void drawMode(Stack *eI)
{
    Node *focusNode = eI->head;

    for(int i = 0 ; i < 8 ; i++)
        focusNode = focusNode->next;

    DrawTexture(focusNode->textureCard, 0, 0, WHITE);
}

void drawRound2(Stack *eI)
{
    Node *focusNode = eI->head;

    for(int i = 0 ; i < 4 ; i++)
        focusNode = focusNode->next;

    DrawTexture(focusNode->textureCard, 0, 0, WHITE);
}

void displayRules(Stack *eI)
{
    Node *focusNode = eI->head;

    for(int i = 0 ; i < 6 ; i++)
        focusNode = focusNode->next;

    DrawTexture(focusNode->textureCard, 0 , 0, WHITE );
}

void Winner(Stack *eI, int w, int AI)
{
    Node *focusNode = eI->head;

    for(int i = 0 ; i < 5 ; i++)
        focusNode = focusNode->next;

    DrawTexture(focusNode->textureCard, 0, 0, WHITE);

    if(w == 1)
    {
        DrawText("P1", 678, 460, 150, WHITE);
        DrawText("P1", 675, 460, 150, PINK);
    }
    else if(w == 2)
    {
        if(AI == 1)
        {
            DrawText("CPU", 598, 460, 150, WHITE);
            DrawText("CPU", 595, 460, 150, PURPLE);
        }
        else
        {
            DrawText("P2", 657, 460, 150, WHITE);
            DrawText("P2", 654, 460, 150, BLUE);
        }
    }
}

void rotateImage(Node *tC)
{
    ImageRotateCCW(&tC->imageCard);
    tC->textureCard = LoadTextureFromImage(tC->imageCard);
}

void drawTable(Stack *P, Stack *eI)
{
    Node *focusEI = eI->head;
    DrawTexture(focusEI->textureCard, 0, 0, WHITE);
    focusEI = focusEI->next->next;

    Node *focusNode = P->head;
    int i = 0;
    int ac = 13;
    while(focusNode != NULL)
    {
        if(i < 10)
        {
            DrawRectangle(ac, 8, 135, 202, WHITE);
            DrawRectangle(ac, 688, 135, 202, WHITE);
        }
        else
        {
            if(i == 10)
                ac = 13;

            DrawRectangle(ac, 218, 135, 202, WHITE);
            DrawRectangle(ac, 478, 135, 202, WHITE);
        }

        ac += 160;

        focusNode = focusNode->next;

        i++;

    }

    DrawRectangle(657, 350, 135, 202, WHITE);
    DrawRectangle(976, 350, 135, 202, WHITE);

    //CARTA DE COMBATE
    DrawRectangle(657, 350, 131, 198, BLACK);
    DrawRectangle(976, 350, 131, 198, BLACK);
    DrawText("VS", 843, 420, 60, WHITE);
    DrawText("VS", 840, 420, 60, RED);

    DrawTexture(focusEI->textureCard, 653, 558, WHITE);
    focusEI = focusEI->next;
    DrawTexture(focusEI->textureCard, 970, 560, WHITE);
}

void displayDeckCard(Node *tC)
{
    DrawRectangle(1390, 382, 202, 135, WHITE);
    DrawTexture(tC->textureCard, 1392, 384, WHITE);
}

void displayPDeck(Stack *P, Stack *eI)
{
    drawTable(P, eI);

    Node *focusNodeP = P->head;

    int i = 0;
    int ac = 15;

    Node *focusEI = eI->head;
    focusEI = focusEI->next;

    while(focusNodeP != NULL)
    {
        if(i < 10)
        {
            DrawTexture(focusNodeP->textureCard, ac, 690, WHITE);
            DrawTexture(focusEI->textureCard, ac, 10, WHITE);
        }
        else
        {
            if(i == 10)
                ac = 15;

            DrawTexture(focusNodeP->textureCard, ac, 480, WHITE);
            DrawTexture(focusEI->textureCard, ac, 220, WHITE);
        }

        ac += 160;

        focusNodeP = focusNodeP->next;

        i++;

    }
}

void displayBackCards(Stack *P, Stack *eI)
{
    drawTable(P, eI);

    Node *focusNodeP = P->head;

    int i = 0;
    int ac = 15;

    Node *focusEI = eI->head;
    focusEI = focusEI->next;

    Node *focusBP = eI->head;

    for(i = 0 ; i < 7 ; i++)
        focusBP = focusBP->next;

    i = 0;

    while(focusNodeP != NULL)
    {
        if(i < 10)
        {
            DrawTexture(focusBP->textureCard, ac, 690, WHITE);
            DrawTexture(focusEI->textureCard, ac, 10, WHITE);
        }
        else
        {
            if(i == 10)
                ac = 15;

            DrawTexture(focusBP->textureCard, ac, 480, WHITE);
            DrawTexture(focusEI->textureCard, ac, 220, WHITE);
        }

        ac += 160;

        focusNodeP = focusNodeP->next;

        i++;

    }
}

void displaySelect(Node *nT, Node *nT2)
{
    if(nT != NULL)
        DrawTexture(nT->textureCard, 657, 350, WHITE);
    if(nT2 != NULL)
        DrawTexture(nT2->textureCard, 976, 350, WHITE);
}

void unloadsImages(Stack *D, Stack *P1, Stack *P2)
{
    Node *focusNodeDeck = D->head;
    Node *focusNodeP1 = P1->head;
    Node *focusNodeP2 = P2->head;

    while(focusNodeDeck != NULL)
    {
        UnloadImage(focusNodeDeck->imageCard);
        focusNodeDeck = focusNodeDeck->next;
    }

    while(focusNodeP1 != NULL)
    {
        UnloadImage(focusNodeP1->imageCard);
        focusNodeP1 = focusNodeP1->next;
    }

    while(focusNodeP2 != NULL)
    {
        UnloadImage(focusNodeP2->imageCard);
        focusNodeP2 = focusNodeP2->next;
    }
}

void unloadsExtraImages(Stack *eI)
{
    Node *focusNode = eI->head;

    while(focusNode != NULL)
    {
        UnloadImage(focusNode->imageCard);
        focusNode = focusNode->next;
    }
}
/*
void saveGame(Stack *D, Stack *P1, Stack *P2, Stack *P1R2, Stack *P2R2, Stack *V1, Stack *V2)
{
    /*Color sText= {5, 211, 102, 255};
    DrawRectangle(400, 300, 1000, 150, BLACK);
    DrawText("Saving Data ...", 843, 420, 60, WHITE);
    DrawText("Saving Data ...", 840, 420, 60, sText);

    //guardar deck
    if(peek(D) != NULL)
    {
        FILE *saveD = fopen("save_data/deck.dat", "w+b");

        if(saveD)
        {
            fwrite(D, sizeof(Stack), 1, saveD);

            Node *focusNode = D->head;

            while(focusNode != NULL)
            {
                fwrite(focusNode, sizeof(Node), 1, saveD);
                /*fwrite(focusNode->imageCard, sizeof(Image), 1, saveD);
                fwrite(focusNode->textureCard, sizeof(Texture2D), 1, saveD);
                focusNode = focusNode->next;
            }

            fclose(saveD);
        }
    }

    //guardar P1
    if(peek(P1) != NULL)
    {
        FILE *saveP1 = fopen("save_data/p1.dat", "w+b");

        if(saveP1)
            fwrite(P1, sizeof(Stack), 1, saveP1);

        fclose(saveP1);
    }

    //guardar P2
    if(peek(P2) != NULL)
    {
        FILE *saveP2 = fopen("save_data/p2.dat", "w+b");

        if(saveP2)
            fwrite(P2, sizeof(Stack), 1, saveP2);

        fclose(saveP2);
    }

    //guardar P1R2
    if(peek(P1R2) != NULL)
    {
        FILE *saveP1R2 = fopen("save_data/p1_r2.dat", "w+b");

        if(saveP1R2)
            fwrite(P1R2, sizeof(Stack), 1, saveP1R2);

        fclose(saveP1R2);
    }

    //guardar P2R2
    if(peek(P2R2) != NULL)
    {
        FILE *saveP2R2 = fopen("save_data/p2_r2.dat", "w+b");

        if(saveP2R2)
            fwrite(P2R2, sizeof(Stack), 1, saveP2R2);

        fclose(saveP2R2);
    }

    //guardar V1
    if(peek(V1) != NULL)
    {
        FILE *saveV1 = fopen("save_data/v1.dat", "w+b");

        if(saveV1)
            fwrite(V1, sizeof(Stack), 1, saveV1);

        fclose(saveV1);
    }

    //guardar V2
    if(peek(V2) != NULL)
    {
        FILE *saveV2 = fopen("save_data/v2.dat", "w+b");

        if(saveV2)
            fwrite(V2, sizeof(Stack), 1, saveV2);

        fclose(saveV2);
    }

    Color sText= {5, 211, 102, 255};
    DrawRectangle(400, 300, 1000, 150, BLACK);
    DrawText("Saving Data ...", 843, 420, 60, WHITE);
    DrawText("Saving Data ...", 840, 420, 60, sText);

}

Stack *loadDeck(Stack *D)
{
    FILE *save = fopen("deck.dat", "r+b");

    if(save != NULL)
    {
        D = newStack();
        fread(D, sizeof(Stack), 1, save);

        D->head = malloc(sizeof(Node));

        Node *focusNode = D->head;

        while(focusNode != NULL)
        {
            fread(focusNode, sizeof(Node), 1, save);
            focusNode = focusNode->next;
        }

        fclose(save);
    }
    /*else
        D = newDeck();

    return D;
}

Stack *loadP1(Stack *P1)
{
    FILE *save = fopen("p1.dat", "r+b");

    if(save != NULL)
    {
        P1 = newStack();
        fread(P1, sizeof(Stack), 1, save);
        fclose(save);
    }

    return P1;
}

Stack *loadP2(Stack *P2)
{
    FILE *save = fopen("p2.dat", "r+b");

    if(save != NULL)
    {
        P2 = newStack();
        fread(P2, sizeof(Stack), 1, save);
        fclose(save);
    }

    return P2;
}*/

Stack *encapsulation(char temp[52][2])
{
    Stack *D = newStack();
    int i;
    int e;

    D->cN = 0;

    Node *focusNode;

    char root[] = "cards/G0.png";

    for(i = 0 ; i < 52 ; i++)
    {
        if(D->cN == 0)
        {
            D->head = malloc(sizeof(Node));
            e = (int*)temp[i][0];

            D->head->level = e - 48;
            D->head->type = temp[i][1];
            D->head->next = NULL;

            root[6] = temp[i][1];
            root[7] = temp[i][0];

            D->head->imageCard = LoadImage(root);
            D->head->textureCard = LoadTextureFromImage(D->head->imageCard);

            focusNode = D->head;
        }
        else
        {
            focusNode->next = malloc(sizeof(Node));
            focusNode = focusNode->next;

            e = (int*)temp[i][0];

            focusNode->level = e - 48;
            focusNode->type = temp[i][1];
            focusNode->next = NULL;

            root[6] = temp[i][1];
            root[7] = temp[i][0];

            focusNode->imageCard = LoadImage(root);

            if(i >= 25 && i % 2 == 0)
                ImageRotateCW(&focusNode->imageCard);

            focusNode->textureCard = LoadTextureFromImage(focusNode->imageCard);
        }

        D->cN++;

    }

    return D;
}

Stack *newDeck()
{
    char list[52][2] = {{'0' , 'G'}, {'0' , 'G'}, {'0' , 'G'}, {'0' , 'G'}, {'0' , 'G'},
                        {'1' , 'G'}, {'2' , 'G'}, {'3' , 'G'}, {'4' , 'G'}, {'5' , 'G'},
                        {'6' , 'G'}, {'7' , 'G'}, {'8', 'G'}, {'9', 'G'},

                        {'0' , 'E'}, {'1' , 'E'}, {'2' , 'E'}, {'3' , 'E'}, {'4' , 'E'},
                        {'5' , 'E'}, {'6' , 'E'}, {'7' , 'E'}, {'8' , 'E'}, {'9' , 'E'},

                        {'0' , 'N'}, {'1' , 'N'}, {'2' , 'N'}, {'3' , 'N'}, {'4' , 'N'},
                        {'5' , 'N'}, {'6' , 'N'}, {'7' , 'N'}, {'8' , 'N'}, {'9' , 'N'},

                        {'0' , 'D'}, {'1' , 'D'}, {'2' , 'D'}, {'3' , 'D'}, {'4' , 'D'},
                        {'5' , 'D'}, {'6' , 'D'}, {'7' , 'D'}, {'8' , 'D'}, {'9' , 'D'},

                        {'2' , 'K'}, {'3' , 'K'}, {'4' , 'K'}, {'5' , 'K'}, {'6' , 'K'},
                        {'7' , 'K'}, {'8' , 'K'}, {'9' , 'K'},

    };

    int i;
    int j;
    int b = 0;
    int n = 52;
    int r;
    srand(time(NULL));

    char temp[52][2];
    int repeated[52];

    for(i = 0 ; i < 52 ; i++)
    {
        r = rand() % n;
        for(j = 0 ; j < i ; j++)
        {
            if(repeated[j] == r)
            {
                b = 1;
                break;
            }
        }

        if(b == 0)
        {
            temp[i][0] = list[r][0];
            temp[i][1] = list[r][1];
            repeated[i] = r;
        }
        else
        {
            b = 0;
            i--;
        }

    }

    return encapsulation(temp);

}

Stack *newPlayer(Stack *D)
{
    Stack *p = newStack();

    int i;
    Node *temp;
    for(i = 0 ; i < 13 ; i++)
    {
        temp = pop(D);
        push(p, temp);

        D->cN--;
        p->cN++;
    }

    return p;
}

int selectCard(Stack *D, Node *nT, Node *nT2, Stack *P1, Stack *P2)
{
    int i = 1;
    Node *focusNode = NULL;

    if(nT != NULL)
        focusNode = P1->head;
    else if(nT2 != NULL)
        focusNode = P2->head;
    else if(nT == NULL && nT2 == NULL)
    {
        if(D->t == 0)
            focusNode = P1->head;
        else if(D->t == 1)
            focusNode = P2->head;
    }

    while(focusNode != NULL)
    {
        i++;
        focusNode = focusNode->next;
    }

    if(IsKeyPressed(KEY_SPACE))
        return 0;
    else if(i >= 1 && IsKeyPressed(KEY_Q))
        return 1;
    else if(i >= 2 && IsKeyPressed(KEY_W))
        return 2;
    else if(i >= 3 && IsKeyPressed(KEY_E))
        return 3;
    else if(i >= 4 && IsKeyPressed(KEY_R))
        return 4;
    else if(i >= 5 && IsKeyPressed(KEY_T))
        return 5;
    else if(i >= 6 && IsKeyPressed(KEY_Y))
        return 6;
    else if(i >= 7 && IsKeyPressed(KEY_U))
        return 7;
    else if(i >= 8 && IsKeyPressed(KEY_I))
        return 8;
    else if(i >= 9 && IsKeyPressed(KEY_O))
        return 9;
    else if(i >= 10 && IsKeyPressed(KEY_P))
        return 10;
    else if(i >= 11 && IsKeyPressed(KEY_A))
        return 11;
    else if(i >= 12 && IsKeyPressed(KEY_S))
        return 12;
    else if(i == 13 && IsKeyPressed(KEY_D))
        return 13;
    else if(WindowShouldClose())
        return 14;
    else
        return 0;
}

Node *craigOption(Node *temp, Node *focusNode)
{
    temp = malloc(sizeof(Node));

    temp->type = focusNode->type;
    temp->level = focusNode->level;
    temp->imageCard = focusNode->imageCard;
    temp->textureCard = focusNode->textureCard;

    return temp;
}

int craig(Stack *D, Stack *P2, Node *nT)
{
    Node *focusNode = P2->head;
    Node *deck = peek(D);
    Node *temp = malloc(sizeof(Node));
    Node *tempT = NULL;
    Node *tempD = NULL;
    Node *tempK = NULL;
    Node *tempM = NULL;
    int i = 1;
    int cT = 0;
    int cD = 0;
    int cK = 0;
    int min = 0;

    if(deck != NULL) //round1 (itsGoTimeBBY)
    {
        if(D->t == 0) //responde craig
        {
            while(focusNode != NULL)
            {
                if((deck->type != 'E' && deck->level >= 6) || (deck->type == 'E' && deck->level <= 5)) // considerar la del deck apropiada para round2
                {
                    if(nT->type == focusNode->type) //guardar valor más alto de ese tipo
                    {
                        if(tempT == NULL)
                        {
                            tempT = craigOption(temp, focusNode);
                            cT = i;
                        }
                        else if(tempT->level < focusNode->level)
                        {
                            tempT = craigOption(temp, focusNode);
                            cT = i;
                        }
                    }
                    else if(focusNode->type == 'D')
                    {
                        if(tempD == NULL)
                        {
                            tempD = craigOption(temp, focusNode);
                            cD = i;
                        }
                        else if(tempD->level < focusNode->level)
                        {
                            tempD = craigOption(temp, focusNode);
                            cD = i;
                        }
                    }
                    else if(focusNode->type == 'K')
                    {
                        if(tempK == NULL)
                        {
                            tempK = craigOption(temp, focusNode);
                            cK = i;
                        }
                        else if(tempK->level < focusNode->level)
                        {
                            tempK = craigOption(temp, focusNode);
                            cK = i;
                        }
                    }
                    else
                    {
                        if(tempM == NULL)
                        {
                            tempM = craigOption(temp, focusNode);
                            min = i;
                        }
                        else if(tempM->level > focusNode->level)
                        {
                            tempM = craigOption(temp, focusNode);
                            min = i;
                        }
                    }
                }
                else if(nT->type == focusNode->type) //guardar valor más alto de ese tipo
                {
                    if(tempT == NULL)
                    {
                        tempT = craigOption(temp, focusNode);
                        cT = i;
                    }
                    else if(tempT->level < focusNode->level)
                    {
                        tempT = craigOption(temp, focusNode);
                        cT = i;
                    }
                }
                else
                {
                    if(tempM == NULL)
                    {
                        tempM = craigOption(temp, focusNode);
                        min = i;
                    }
                    else if(tempM->level > focusNode->level)
                    {
                        tempM = craigOption(temp, focusNode);
                        min = i;
                    }
                }

                i++;
                focusNode = focusNode->next;
            }

            if(i == 1) //ultima carta
                return 1;

            if(cT != 0) //checar si hay carta del mismo tipo
                return cT;
            else if(cK != 0 && nT->type == 'G') //caso de no tener Goblin checar si hay knight para matar Goblin
                return cK;
            else if(cD != 0 && nT->level < tempD->level) // caso de no tener del mismo tipo checar si hay Doppleganger
                return cD;
            else // caso de no tener del mismo tipo y no tener Doppleganger
                return min;
        }
        else if(D->t == 1) // empieza craig
        {
            while(focusNode != NULL)
            {
                if((deck->type != 'E' && deck->level >= 6) || (deck->type == 'E' && deck->level <= 5)) // considerar la del deck apropiada para round2
                {
                    if(tempT == NULL)
                    {
                        tempT = craigOption(temp, focusNode);
                        cT = i;
                    }
                    else if(tempT->level < focusNode->level)
                    {
                        tempT = craigOption(temp, focusNode);
                        cT = i;
                    }
                }
                else
                {
                    if(tempM == NULL)
                    {
                        tempM = craigOption(temp, focusNode);
                        min = i;
                    }
                    else if(tempM->level > focusNode->level)
                    {
                        tempM = craigOption(temp, focusNode);
                        min = i;
                    }
                }

                i++;
                focusNode = focusNode->next;
            }

            if(i == 1) //caso de ultima carta
                return 1;

            if(cT != 0) //si hay del mismo tipo
                return cT;
            else
                return min;
        }
    }
    else // round2
    {
        Node *tempE = NULL;
        int cE = 0;

        if(D->t == 0) // responde craig
        {
            while(focusNode != NULL)
            {
                if(nT->type == focusNode->type) //guardar valor más alto de ese tipo
                {
                    if(tempT == NULL)
                    {
                        tempT = craigOption(temp, focusNode);
                        cT = i;
                    }
                    else if(nT->type == 'E' && nT->level > focusNode->level)
                    {
                        tempE = craigOption(temp, focusNode);
                        cE = i;
                    }
                    else if(tempT->level < focusNode->level)
                    {
                        tempT = craigOption(temp, focusNode);
                        cT = i;
                    }
                }
                else if(focusNode->type == 'D')
                {
                    if(tempD == NULL)
                    {
                        tempD = craigOption(temp, focusNode);
                        cD = i;
                    }
                    else if(tempD->level < focusNode->level)
                    {
                        tempD = craigOption(temp, focusNode);
                        cD = i;
                    }
                }
                else if(focusNode->type == 'K')
                {
                    if(tempK == NULL)
                    {
                        tempK = craigOption(temp, focusNode);
                        cK = i;
                    }
                    else if (tempK->level < focusNode->level){
                        tempK = craigOption(temp, focusNode);
                        cK = i;
                    }
                }
                else
                {
                    if(tempM == NULL)
                    {
                        tempM = craigOption(temp, focusNode);
                        min = i;
                    }
                    else if(tempM->level > focusNode->level)
                    {
                        tempM = craigOption(temp, focusNode);
                        min = i;
                    }
                }

                i++;
                focusNode = focusNode->next;
            }

            if(i == 1) //ultima carta
                return 1;

            if(cE != 0)
                return cE;
            else if(cT != 0) //checar si hay carta del mismo tipo
                return cT;
            else if(cK != 0 && nT->type == 'G') //caso de no tener Goblin checar si hay knight para matar Goblin
                return cK;
            else if(cD != 0 && nT->level < tempD->level) // caso de no tener del mismo tipo checar si hay Doppleganger
                return cD;
            else // caso de no tener del mismo tipo y no tener Doppleganger
                return min;

        }
        else if(D->t == 1) // empieza craig
        {
            while(focusNode != NULL)
            {
                if(tempT == NULL)
                {
                    tempT = craigOption(temp, focusNode);
                    cT = i;
                }
                else if(tempT->level < focusNode->level)
                {
                    tempT = craigOption(temp, focusNode);
                    cT = i;
                }

                i++;
                focusNode = focusNode->next;
            }

            if(i == 1) //caso de ultima carta
                return 1;

            else if(cT != 0) //si hay del mismo tipo
                return cT;
        }
    }
}

void itsGoTimeBBY(Stack *D, Stack *V1, Stack *V2, Stack *P1, Stack *P2, Stack *P1R2, Stack *P2R2, Stack *eI, int AI)
{
    Stack *temp = newStack();
    Node *tC;
    Node *nT = NULL;
    Node *nT2 = NULL;
    int neXt = 0;

    while(peek(D) != NULL)
    {
        BeginDrawing();
        tC = peek(D);
        Node *r = NULL;
        int c = 0;
        int i = 0;

        if(IsKeyPressed(KEY_SPACE))
            neXt = 15;

        if(nT == NULL || nT2 == NULL)
            c = selectCard(D, nT, nT2, P1, P2);

        if(D->t == 0)
        {
            if(nT != NULL && nT2 != NULL)
            {
                displayBackCards(P1, eI);
                displayDeckCard(tC);
                displaySelect(nT, nT2);
            }
            else if(nT == NULL)
            {
                displayPDeck(P1, eI);
                displayDeckCard(tC);
                DrawText("P1", 1455, 560, 80, WHITE);
                DrawText("P1", 1453, 560, 80, PINK);

                if(c != 0)
                {
                    for(i = 0; i < c; i++)
                    {
                        r = pop(P1);
                        push(temp, r);
                    }

                    nT = pop(temp);
                    displaySelect(nT, nT2);
                    P1->cN--;

                    while(peek(temp) != NULL)
                    {
                        r = pop(temp);
                        push(P1, r);
                    }
                    c = 0;
                    neXt = 0;
                }
            }
            else if(nT != NULL)
            {
                displayPDeck(P2, eI);
                displayDeckCard(tC);
                displaySelect(nT, nT2);

                DrawText("P2", 1455, 560, 80, WHITE);
                DrawText("P2", 1453, 560, 80, BLUE);

                if(AI == 1)
                    c = craig(D, P2, nT);

                if(c != 0)
                {
                    for(i = 0; i < c; i++)
                    {
                        r = pop(P2);
                        push(temp, r);
                    }

                    nT2 = pop(temp);


                    displaySelect(nT, nT2);

                    P2->cN--;

                    while(peek(temp) != NULL)
                    {
                        r = pop(temp);
                        push(P2, r);
                    }
                    c = 0;
                }
            }
        }
        else if(D->t == 1)
        {
            if(nT != NULL && nT2 != NULL)
            {
                displayBackCards(P1, eI);
                displayDeckCard(tC);
                displaySelect(nT, nT2);
            }
            else if(nT2 == NULL)
            {
                displayPDeck(P2, eI);
                displayDeckCard(tC);

                DrawText("P2", 1455, 560, 80, WHITE);
                DrawText("P2", 1453, 560, 80, BLUE);

                if(AI == 1)
                    c = craig(D, P2, nT);

                if(c != 0)
                {
                    for(i = 0; i < c; i++)
                    {
                        r = pop(P2);
                        push(temp, r);
                    }

                    nT2 = pop(temp);
                    P2->cN--;

                    while(peek(temp) != NULL)
                    {
                        r = pop(temp);
                        push(P2, r);
                    }
                    c = 0;
                    neXt = 0;
                }
            }
            else if(nT2 != NULL)
            {
                displayPDeck(P1, eI);
                displayDeckCard(tC);
                displaySelect(nT, nT2);

                DrawText("P1", 1455, 560, 80, WHITE);
                DrawText("P1", 1453, 560, 80, PINK);

                if(c != 0)
                {
                    for(i = 0; i < c; i++)
                    {
                        r = pop(P1);
                        push(temp, r);
                    }

                    nT = pop(temp);
                    displaySelect(nT, nT2);
                    P1->cN--;

                    while(peek(temp) != NULL)
                    {
                        r = pop(temp);
                        push(P1, r);
                    }
                    c = 0;
                }
            }
        }

        /*if(IsKeyPressed(KEY_V))
            saveGame(D, P1, P2, P1R2, P2R2, V1, V2);*/

        if(nT != NULL && nT2 != NULL && neXt == 15)
        {
            tC = pop(D);
            rotateImage(tC);

            if(nT->type == nT2->type || nT->type == 'D' || nT2->type == 'D') //comparacion de nivel y comodin
            {
                if(D->t == 0 && nT2->type == 'N' && nT->type == 'D')
                {
                    push(V1, nT2);
                    push(P1R2, tC);
                    D->t = 0;
                }
                else if(D->t == 1 && nT->type == 'N' && nT2->type == 'D')
                {
                    push(V2, nT);
                    push(P2R2, tC);
                    D->t = 1;
                }
                else if(nT->type == 'N' || nT2->type == 'N')
                {
                    int b = 0;
                    if(nT->type == nT2->type)
                        b = 1;
                    else if(D->t == 0 && nT2->type == 'D' && nT->type == 'N')
                        b = 2;
                    else if(D->t == 1 && nT->type == 'D' && nT2->type == 'N')
                        b = 3;

                    if(nT->level > nT2->level || (nT->level == nT2->level && D->t == 0))
                    {
                        if(b == 1)
                        {
                            push(V1, nT);
                            push(V1, nT2);
                            push(P1R2, tC);
                            D->t = 0;
                        }
                        else if(b == 2)
                        {
                            push(V1, nT);
                            push(P1R2, tC);
                            D->t = 0;
                        }
                        else if(b == 3)
                        {
                            push(V1, nT2);
                            push(P1R2, tC);
                            D->t = 0;
                        }
                    }
                    else if(nT->level < nT2->level || (nT->level == nT2->level && D->t == 1))
                    {
                        if(b == 1)
                        {
                            push(V2, nT);
                            push(V2, nT2);
                            push(P2R2, tC);
                            D->t = 1;
                        }
                        else if(b == 2)
                        {
                            push(V2, nT);
                            push(P2R2, tC);
                            D->t = 1;
                        }
                        else if(b == 3)
                        {
                            push(V2, nT2);
                            push(P2R2, tC);
                            D->t = 1;
                        }
                    }
                }
                else if(D->t == 0 && nT->type == 'D' && nT2->type != 'D')
                {
                    push(P1R2, tC);
                    D->t = 0;
                }
                else if(D->t == 1 && nT2->type == 'D' && nT->type != 'D')
                {
                    push(P2R2, tC);
                    D->t = 1;
                }
                else if(nT->level > nT2->level || (nT->level == nT2->level && D->t == 0))
                {
                    push(P1R2, tC);
                    D->t = 0;
                }
                else if(nT->level < nT2->level || (nT->level == nT2->level && D->t == 1))
                {
                    push(P2R2, tC);
                    D->t = 1;
                }
            }
            else if(nT->type != nT2->type)
            {
                if(D->t == 0 && nT->type == 'N' && nT->level > nT2->level) //necromancers puntos directos
                {
                    push(V1, nT);
                    push(P1R2, tC);
                    D->t = 0;
                }
                else if
                        (D->t == 1 && nT2->type == 'N' && nT->level < nT2->level)
                {
                    push(V2, nT);
                    push(P2R2, tC);
                    D->t = 1;
                }
                else if(D->t == 0 && nT2->type == 'N' && nT->level > nT2->level)
                {
                    push(V1, nT2);
                    push(P1R2, tC);
                    D->t = 0;
                }
                else if(D->t == 1 && nT->type == 'N' && nT->level < nT2->level)
                {
                    push(V2, nT);
                    push(P2R2, tC);
                    D->t = 1;
                }
                else if(D->t == 0 && nT->type == 'G' && nT2->type == 'K')
                {
                    push(P2R2, tC);
                    D->t = 1;
                }
                else if(D->t == 1 && nT->type == 'K' && nT2->type == 'G')
                {
                    push(P1R2, tC);
                    D->t = 0;
                }
                else if(D->t == 0)
                {
                    push(P1R2, tC);
                    D->t = 0;
                }
                else if(D->t == 1)
                {
                    push(P2R2, tC);
                    D->t = 1;
                }
            }

            if(D->t == 0)
            {
                tC = pop(D);
                push(P2R2, tC);
            }
            else if(D->t == 1)
            {
                tC = pop(D);
                push(P1R2, tC);
            }

            tC = NULL;
            nT = NULL;
            nT2 = NULL;
            neXt = 0;
        }
        EndDrawing();
    }

}

void round2(Stack *D, Stack *V1, Stack *V2,Stack *P1R2, Stack *P2R2, Stack *eI, int AI)
{

    Stack *temp = newStack();
    Node *nT = NULL;
    Node *nT2 = NULL;
    int end = 0;
    int neXt = 0;

    while(end < 13)
    {
        BeginDrawing();

        Node *r = NULL;
        int c;
        int i = 0;


        if(IsKeyPressed(KEY_SPACE))
            neXt = 15;

        if(nT == NULL || nT2 == NULL)
            c = selectCard(D, nT, nT2, P1R2, P2R2);

        if(D->t == 0)
        {
            if(nT != NULL && nT2 != NULL)
            {
                displayBackCards(P1R2, eI);
                displaySelect(nT, nT2);
            }
            else if(nT == NULL)
            {
                displayPDeck(P1R2, eI);

                DrawText("P1", 1455, 560, 80, WHITE);
                DrawText("P1", 1453, 560, 80, PINK);

                for(i = 0; i < c; i++)
                {
                    r = pop(P1R2);
                    push(temp, r);
                }

                nT = pop(temp);
                displaySelect(nT,nT2);
                P1R2->cN--;

                while(peek(temp) != NULL)
                {
                    r = pop(temp);
                    push(P1R2, r);
                }
                c = 0;
                neXt = 0;
            }
           else if(nT != NULL)
            {
                displayPDeck(P2R2, eI);
                displaySelect(nT, nT2);

                DrawText("P2", 1455, 560, 80, WHITE);
                DrawText("P2", 1453, 560, 80, BLUE);

                if(AI == 1)
                    c = craig(D, P2R2, nT);

                if(c != 0)
                {
                    for(i = 0; i < c; i++)
                    {
                        r = pop(P2R2);
                        push(temp, r);
                    }

                    nT2 = pop(temp);
                    displaySelect(nT,nT2);
                    P2R2->cN--;

                    while(peek(temp) != NULL)
                    {
                        r = pop(temp);
                        push(P2R2, r);
                    }
                    c = 0;
                }
            }
        }
        else if(D->t == 1)
        {
            if(nT != NULL && nT2 != NULL)
            {
                displayBackCards(P1R2, eI);
                displaySelect(nT, nT2);
            }
            else if(nT2 == NULL)
            {
                displayPDeck(P2R2, eI);

                DrawText("P2", 1455, 560, 80, WHITE);
                DrawText("P2", 1453, 560, 80, BLUE);

                if(AI == 1)
                    c = craig(D, P2R2, nT);

                if(c != 0)
                {
                    for(i = 0; i < c; i++)
                    {
                        r = pop(P2R2);
                        push(temp, r);
                    }

                    nT2 = pop(temp);
                    displaySelect(nT, nT2);
                    P2R2->cN--;

                    while(peek(temp) != NULL)
                    {
                        r = pop(temp);
                        push(P2R2, r);
                    }
                    c = 0;
                    neXt = 0;
                }
            }
            else if(nT2 != NULL)
            {
                displayPDeck(P1R2, eI);
                displaySelect(nT,nT2);

                DrawText("P1", 1455, 560, 80, WHITE);
                DrawText("P1", 1453, 560, 80, PINK);

                if(c != 0)
                {
                    for(i = 0; i < c; i++)
                    {
                        r = pop(P1R2);
                        push(temp, r);
                    }

                    nT = pop(temp);
                    displaySelect(nT,nT2);
                    P1R2->cN--;

                    while(peek(temp) != NULL)
                    {
                        r = pop(temp);
                        push(P1R2, r);
                    }
                    c = 0;
                }
            }
        }

        if(nT != NULL && nT2 != NULL && neXt == 15)
        {
            //CONDICIONES GOBLIN Y KNIGHT
            if(D->t == 1 && nT->type == 'K' && nT2->type == 'G')
            {
                push(V1, nT);
                push(V1, nT2);
                D->t = 0;
            }
            else if(D->t == 0 && nT2->type == 'K' && nT->type == 'G')
            {
                push(V2, nT);
                push(V2, nT2);
                D->t = 1;
            }
                //COMPARACIONES DE MISMA CLASE
            else if(nT->type == nT2->type)
            {
                if(nT->type == 'E' && nT2->type == 'E') //caso 2 enanos
                {
                    if(nT->level < nT2->level)
                    {
                        push(V1, nT);
                        push(V1, nT2);
                        D->t = 1;
                    }
                    else if(nT2->level < nT->level)
                    {
                        push(V2, nT);
                        push(V2, nT2);
                        D->t = 0;
                    }
                }
                else if(nT->level > nT2->level)
                {
                    push(V1, nT);
                    push(V1, nT2);
                    D->t = 0;
                }
                else if(nT->level < nT2->level)
                {
                    push(V2, nT);
                    push(V2, nT2);
                    D->t = 1;
                }
            }
                //COMPARACIONES DE DIFERENTE CLASE SIN DUPPLEGANGER
            else if(nT->type != nT2->type && nT->type != 'D' && nT2->type != 'D')
            {
                if(nT->type == 'E' || nT2->type == 'E') //enano perdedor
                {
                    push(V1, nT);
                    push(V2, nT2);
                }
                else if(D->t == 0)
                {
                    push(V1, nT);
                    push(V1, nT2);
                    //D->t = 0; al estar implicito
                }
                else if(D->t == 1)
                {
                    push(V2, nT);
                    push(V2, nT2);
                    //D->t = 1; al estar implicito
                }
            }
                //COMPARACIONES DE DIFERENTE CLASE CON DUPPLEGANGER
            else if(D->t == 0 && nT->type == 'D')
            {
                if(nT2->type != 'D')
                {
                    if(nT2->type == 'E') //enano perdedor
                    {
                        push(V1, nT);
                        push(V2, nT2);
                    }
                    else
                    {
                        push(V1, nT);
                        push(V1, nT2);
                        D->t = 0;
                    }
                }
                else if(nT2->type == 'D')
                {
                    if(nT->level > nT2->level)
                    {
                        push(V1, nT);
                        push(V1, nT2);
                        D->t = 0;
                    }
                    else if(nT->level < nT2->level)
                    {
                        push(V2, nT);
                        push(V2, nT2);
                        D->t = 1;
                    }
                }
            }
            else if(D->t == 1 && nT2->type == 'D')
            {
                if(nT->type != 'D')
                {
                    if (nT2->type == 'E') //enano perdedor
                    {
                        push(V1, nT);
                        push(V2, nT2);
                    }
                    else
                    {
                        push(V2, nT);
                        push(V2, nT2);
                        D->t = 1;
                    }
                }
                else if(nT->type == 'D')
                {
                    if(nT->level > nT2->level)
                    {
                        push(V1, nT);
                        push(V1, nT2);
                        D->t = 0;
                    }
                    else if(nT->level < nT2->level)
                    {
                        push(V2, nT);
                        push(V2, nT2);
                        D->t = 1;
                    }
                }
            }
            else if(nT->type == 'D' || nT2->type == 'D')
            {
                if(nT->level > nT2->level)
                {
                    if(nT2->type == 'E') //enano perdedor
                    {
                        push(V1, nT);
                        push(V2, nT2);
                    }
                    else
                    {
                        push(V1, nT);
                        push(V1, nT2);
                        D->t = 0;
                    }
                }
                else if(nT->level < nT2->level)
                {
                    if(nT->type == 'E') //enano perdedor
                    {
                        push(V1, nT);
                        push(V2, nT2);
                    }
                    else
                    {
                        push(V2, nT);
                        push(V2, nT2);
                        D->t = 1;
                    }
                }
            }
            nT = NULL;
            nT2 = NULL;
            end++;
            neXt = 0;
        }
        EndDrawing();
    }
}

int claimWinner(Stack *V1, Stack *V2, Stack *eI)
{
    int P1TG = 0;
    int P1TE = 0;
    int P1TN = 0;
    int P1TD = 0;
    int P1TK = 0;
    int VT1 = 0;
    int P1GMax = 0;
    int P1EMax = 0;
    int P1NMax = 0;
    int P1DMax = 0;
    int P1KMax = 0;


    while(peek(V1) != NULL)
    {
        if(V1->head->type == 'G')
        {
            if(V1->head->level > P1GMax)
                P1GMax = V1->head->level;

            P1TG++;
        }
        else if(V1->head->type == 'E')
        {
            if(V1->head->level > P1EMax)
                P1EMax = V1->head->level;

            P1TE++;
        }
        else if(V1->head->type == 'N')
        {
            if(V1->head->level > P1NMax)
                P1NMax = V1->head->level;

            P1TN++;
        }
        else if(V1->head->type == 'D')
        {
            if(V1->head->level > P1DMax)
                P1DMax = V1->head->level;

            P1TD++;
        }
        else if(V1->head->type == 'K')
        {
            if(V1->head->level > P1KMax)
                P1KMax = V1->head->level;

            P1TK++;
        }

        pop(V1);
    }

    int P2TG = 0;
    int P2TE = 0;
    int P2TN = 0;
    int P2TD = 0;
    int P2TK = 0;
    int VT2 = 0;
    int P2GMax = 0;
    int P2EMax = 0;
    int P2NMax = 0;
    int P2DMax = 0;
    int P2KMax = 0;

    while(peek(V2) != NULL)
    {
        if(V2->head->type == 'G')
        {
            if (V2->head->level > P2GMax)
                P2GMax = V2->head->level;

            P2TG++;
        }
        else if(V2->head->type == 'E')
        {
            if(V2->head->level > P2EMax)
                P2EMax = V2->head->level;

            P2TE++;
        }
        else if(V2->head->type == 'N')
        {
            if(V2->head->level > P2NMax)
                P2NMax = V2->head->level;

            P2TN++;
        }
        else if(V2->head->type == 'D')
        {
            if(V2->head->level > P2DMax)
                P2DMax = V2->head->level;

            P2TD++;
        }
        else if(V2->head->type == 'K')
        {
            if(V2->head->level > P2KMax)
                P2KMax = V2->head->level;

            P2TK++;
        }

        pop(V2);
    }
    /*
    printf("\n[P1TG]: %d\t[P1TE]: %d\t[P1TN]: %d\t[P1TD]: %d\t[P1TK]: %d\t\n", P1TG, P1TE, P1TN, P1TD, P1TK);
    printf("[P1GMax]: %d\t[P1EMax]: %d\t[P1NMax]: %d\t[P1DMax]: %d\t[P1KMax]: %d\t\n", P1GMax, P1EMax, P1NMax, P1DMax, P1KMax);
    printf("\n[P2TG]: %d\t[P2TE]: %d\t[P2TN]: %d\t[P2TD]: %d\t[P2TK]: %d\t\n", P2TG, P2TE, P2TN, P2TD, P2TK);
    printf("[P2GMax]: %d\t[P2EMax]: %d\t[P2NMax]: %d\t[P2DMax]: %d\t[P2KMax]: %d\t\n", P2GMax, P2EMax, P2NMax, P2DMax, P2KMax);
    */
    //Goblins
    if(P1TG > P2TG)
    {
        //printf("Mas Goblins Votaron por el Jugador 1\n");
        VT1++;
    }
    else if(P2TG > P1TG)
    {
        //printf("Mas Goblins Votaron por el Jugador 2\n");
        VT2++;
    }
    else if(P1TG == P2TG)
    {
        //printf("Empate\n");

        if(P1GMax > P2GMax)
        {
            //printf("El Jugador 1 Tiene el voto del Goblin mas alto, por lo que se lleva el voto de los Goblins\n");
            VT1++;
        }
        else if(P2GMax > P1GMax)
        {
            //printf("El Jugador 2 Tiene el voto del Goblin mas alto, por lo que se lleva el voto de los Goblins\n");
            VT2++;
        }
    }

    //Enanos
    if(P1TE > P2TE)
    {
        //printf("Mas Enanos Votaron por el Jugador 1\n");
        VT1++;
    }
    else if(P2TE > P1TE)
    {
        //printf("Mas Enanos Votaron por el Jugador 2\n");
        VT2++;
    }
    else if(P1TE == P2TE)
    {
        //printf("Empate\n");

        if(P1EMax > P2EMax)
        {
            //printf("El Jugador 1 Tiene el voto del Enano mas alto, por lo que se lleva el voto de los Enanos\n");
            VT1++;
        }
        else if (P2EMax > P1EMax)
        {
            //printf("El Jugador 2 Tiene el voto del Enano mas alto, por lo que se lleva el voto de los Enanos\n");
            VT2++;
        }
    }

    //necromancers
    if(P1TN > P2TN)
    {
        //printf("Mas Necromancers Votaron por el Jugador 1\n");
        VT1++;
    }
    else if(P2TN > P1TN)
    {
        //printf("Mas Necromancers Votaron por el Jugador 2\n");
        VT2++;
    }
    else if(P1TN == P2TN)
    {
        //printf("Empate\n");

        if(P1NMax > P2NMax)
        {
            //printf("El Jugador 1 Tiene el voto del Necromancer mas alto, por lo que se lleva el voto de los Necromancers\n");
            VT1++;
        }
        else if(P2NMax > P1NMax)
        {
            //printf("El Jugador 2 Tiene el voto del Necromancer mas alto, por lo que se lleva el voto de los Necromancers\n");
            VT2++;
        }
    }

    //doppelgangers
    if(P1TD > P2TD)
    {
        //printf("Mas Doppelgangers Votaron por el Jugador 1\n");
        VT1++;
    }
    else if(P2TD > P1TD)
    {
        //printf("Mas Doppelgangers Votaron por el Jugador 2\n");
        VT2++;
    }
    else if(P1TD == P2TD)
    {
        //printf("Empate\n");

        if(P1DMax > P2DMax)
        {
            //printf("El Jugador 1 Tiene el voto del Doppelganger mas alto, por lo que se lleva el voto de los Doppelgangers\n");
            VT1++;
        }
        else if(P2DMax > P1DMax)
        {
            //printf("El Jugador 2 Tiene el voto del Doppelganger mas alto, por lo que se lleva el voto de los Doppelgangers\n");
            VT2++;
        }
    }

    //knights
    if(P1TK > P2TK)
    {
        //printf("Mas Knights Votaron por el Jugador 1\n");
        VT1++;
    }
    else if(P2TK > P1TK)
    {
        //printf("Mas Knights Votaron por el Jugador 2\n");
        VT2++;
    }
    else if(P1TK == P2TK)
    {
        if(P1KMax > P2KMax)
            VT1++;
        else if(P2KMax > P1KMax)
            VT2++;
    }

    //decision de GANADOR FINAL

    if(VT1 > VT2)
        return 1;
    else if(VT2 > VT1)
        return 2;
}
