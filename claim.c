#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "claim.h"
#include "stack.h"
#include "raylib.h"

Stack *extraImages()
{
    Stack *n = newStack();
    Node *tempNode = malloc(sizeof(Node));

    // cargar gameMode
    tempNode->type = 'G';
    tempNode->level = 7;
    tempNode->imageCard = LoadImage("cards/game_mode.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    // cargar backCard180
    tempNode->type = 'B';
    tempNode->level = 6;
    tempNode->imageCard = LoadImage("cards/back.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    // cargar Rules
    tempNode->type = 'R';
    tempNode->level = 5;
    tempNode->imageCard = LoadImage("cards/rules.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    // cargar Winner
    tempNode->type = 'W';
    tempNode->level = 4;
    tempNode->imageCard = LoadImage("cards/Winner.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    // cargar round2
    tempNode->type = 'R';
    tempNode->level = 3;
    tempNode->imageCard = LoadImage("cards/R2.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    // cargar P2
    tempNode->type = 'P';
    tempNode->level = 2;
    tempNode->imageCard = LoadImage("cards/P2.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    // cargar P1
    tempNode->type = 'P';
    tempNode->level = 1;
    tempNode->imageCard = LoadImage("cards/P1.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    // cargar cardBack
    tempNode->type = 'P';
    tempNode->level = 1;
    tempNode->imageCard = LoadImage("cards/fback.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    // cargar tablero
    tempNode->type = 'T';
    tempNode->level = 0;
    tempNode->imageCard = LoadImage("cards/Tablero.png");
    tempNode->textureCard = LoadTextureFromImage(tempNode->imageCard);
    push(n, tempNode);
    n->cN++;

    return n;
}

void drawStart() // dibujar menu
{
    Color backGround = {23, 32, 42, 255};
    Color textStart = {219, 182,0, 255};
    ClearBackground(backGround);
    DrawText("Claim", 500, 250, 250, WHITE);
    DrawText("BY PABLITO & SEBAS", 700, 480, 20, WHITE);
    DrawText("Press enter to START", 450, 600, 60, textStart);
    DrawText("Press shift for RULES", 565, 673, 40, YELLOW);

}

void drawMode(Stack *eI) // dibujar pantalla de seleccion de jugador
{
    Node *focusNode = eI->head;

    for(int i = 0 ; i < 8 ; i++)
        focusNode = focusNode->next;

    DrawTexture(focusNode->textureCard, 0, 0, WHITE);
}

void drawRound2(Stack *eI) // dibujar pantalla de cambio de round1 (ItsGoTimeBBY) a round2
{
    Node *focusNode = eI->head;

    for(int i = 0 ; i < 4 ; i++)
        focusNode = focusNode->next;

    DrawTexture(focusNode->textureCard, 0, 0, WHITE);
}

void displayRules(Stack *eI) // dibuja reglas
{
    Node *focusNode = eI->head;

    for(int i = 0 ; i < 6 ; i++)
        focusNode = focusNode->next;

    DrawTexture(focusNode->textureCard, 0 , 0, WHITE );
}

void Winner(Stack *eI, int w, int AI) // dibujar ganador
{
    Node *focusNode = eI->head;

    for(int i = 0 ; i < 5 ; i++)
        focusNode = focusNode->next;

    DrawTexture(focusNode->textureCard, 0, 0, WHITE);

    if(w == 1) // p1 winner
    {
        DrawText("P1", 678, 460, 150, WHITE);
        DrawText("P1", 675, 460, 150, PINK);
    }
    else if(w == 2)
    {
        if(AI == 1) // p2 winner
        {
            DrawText("CPU", 598, 460, 150, WHITE);
            DrawText("CPU", 595, 460, 150, PURPLE);
        }
        else // cpu winner
        {
            DrawText("P2", 657, 460, 150, WHITE);
            DrawText("P2", 654, 460, 150, BLUE);
        }
    }
}

void rotateImage(Node *tC) // rotar imagen del deck
{
    ImageRotateCCW(&tC->imageCard);
    tC->textureCard = LoadTextureFromImage(tC->imageCard);
}

void drawTable(Stack *P, Stack *eI) // dibujar tablero
{
    // dibujar fondo
    Node *focusEI = eI->head;
    DrawTexture(focusEI->textureCard, 0, 0, WHITE);
    focusEI = focusEI->next->next;

    // dibujar rectangulos en la posicion de las cartas como margen
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

    //CARTA DE COMBATE
    DrawRectangle(657, 350, 135, 202, WHITE);
    DrawRectangle(976, 350, 135, 202, WHITE);
    DrawRectangle(657, 350, 131, 198, BLACK);
    DrawRectangle(976, 350, 131, 198, BLACK);
    DrawText("VS", 843, 420, 60, WHITE);
    DrawText("VS", 840, 420, 60, RED);

    DrawTexture(focusEI->textureCard, 653, 558, WHITE); // dibujar imagen P1
    focusEI = focusEI->next;
    DrawTexture(focusEI->textureCard, 970, 560, WHITE); // dibujar imagen P2
}

void displayDeckCard(Node *tC) // dibujar carta del deck en el round 1 (itsGoTimeBBY)
{
    DrawRectangle(1390, 382, 202, 135, WHITE);
    DrawTexture(tC->textureCard, 1392, 384, WHITE);
}

void displayPDeck(Stack *P, Stack *eI) // dibujar tablero con las cartas del actual jugador
{
    drawTable(P, eI);

    Node *focusNodeP = P->head; // cartas del jugador

    int i = 0;
    int ac = 15;

    Node *focusEI = eI->head;
    focusEI = focusEI->next; // imagenes de atras de la carta

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

void displayBackCards(Stack *P, Stack *eI) // dibujar todas las cartas boca abajo en la battle phase
{
    drawTable(P, eI);

    Node *focusNodeP = P->head; // para determinar el numero de cartas actuales del jugador

    int i = 0;
    int ac = 15;

    Node *focusEI = eI->head;
    focusEI = focusEI->next; // imagen de parte de atras de las cartas superior

    Node *focusBP = eI->head;

    for(i = 0 ; i < 7 ; i++)
        focusBP = focusBP->next; // imagen de parte de atras de las cartas inferior

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

void displaySelect(Node *nT, Node *nT2) // dibujar cartas seleccionadas por el jugador
{
    if(nT != NULL)
        DrawTexture(nT->textureCard, 657, 350, WHITE);
    if(nT2 != NULL)
        DrawTexture(nT2->textureCard, 976, 350, WHITE);
}

void unloadsImages(Stack *D, Stack *P1, Stack *P2) // funcion unload optimizada al Deck, P1, P2, P1R2 y P1R2
{
    Node *focusNodeDeck = D->head;
    Node *focusNodeP1 = P1->head;
    Node *focusNodeP2 = P2->head;

    while(focusNodeDeck != NULL) // unload deck
    {
        UnloadImage(focusNodeDeck->imageCard);
        focusNodeDeck = focusNodeDeck->next;
    }

    while(focusNodeP1 != NULL) // unload P1 o P1R2
    {
        UnloadImage(focusNodeP1->imageCard);
        focusNodeP1 = focusNodeP1->next;
    }

    while(focusNodeP2 != NULL) // unload P2 o P2R2
    {
        UnloadImage(focusNodeP2->imageCard);
        focusNodeP2 = focusNodeP2->next;
    }
}

void unloadsExtraImages(Stack *eI) // unload de todas las imagenes extras
{
    Node *focusNode = eI->head;

    while(focusNode != NULL)
    {
        UnloadImage(focusNode->imageCard);
        focusNode = focusNode->next;
    }
}

Stack *encapsulation(char temp[52][2]) // encapsulada de los nodos del deck
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

            D->head->level = e - 48; // guardar char como int del shuffle deck por random
            D->head->type = temp[i][1]; // guardar char de type
            D->head->next = NULL;

            // cambiar el root para tener la direccion actual de la carta
            root[6] = temp[i][1];
            root[7] = temp[i][0];

            // cargar imagen y textura a la estructura
            D->head->imageCard = LoadImage(root);
            D->head->textureCard = LoadTextureFromImage(D->head->imageCard);

            focusNode = D->head;
        }
        else
        {
            focusNode->next = malloc(sizeof(Node));
            focusNode = focusNode->next;

            e = (int*)temp[i][0];

            focusNode->level = e - 48; // guardar char como int del shuffle deck por random
            focusNode->type = temp[i][1]; // guardar char de type
            focusNode->next = NULL;

            // cambiar el root para tener la direccion actual de la carta
            root[6] = temp[i][1];
            root[7] = temp[i][0];

            // cargar imagen y textura a la estructura
            focusNode->imageCard = LoadImage(root);

            if(i >= 25 && i % 2 == 0) // rotar solo las cartas que se quedaran en el deck para un futuro display
                ImageRotateCW(&focusNode->imageCard);

            focusNode->textureCard = LoadTextureFromImage(focusNode->imageCard);
        }

        D->cN++;

    }

    return D;
}

Stack *newDeck() // funcion para revolver el deck al iniciar partida
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

    for(i = 0 ; i < 52 ; i++) // asignar valor random de nuestra matriz y comprobar que no se repitan los valores
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

Stack *newPlayer(Stack *D) // obtener 13 cartas para un jugador del deck
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

int selectCard(Stack *D, Node *nT, Node *nT2, Stack *P1, Stack *P2) // funcion para seleccionar carta segun el teclado
{
    int i = 0;
    Node *focusNode = NULL;

    if(nT == NULL && nT2 != NULL) // turno jugador 1
        focusNode = P1->head;
    else if(nT2 == NULL && nT != NULL) // turno del jugador 2
        focusNode = P2->head;
    else if(nT == NULL && nT2 == NULL)
    {
        if(D->t == 0)
            focusNode = P1->head; // turno jugador 1
        else if(D->t == 1)
            focusNode = P2->head; // turno del jugador 2
    }

    while(focusNode != NULL) // obtener la cantidad actual de cartas del jugador
    {
        i++;
        focusNode = focusNode->next;
    }

    // condiciones para elegir carta
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

Node *craigOption(Node *temp, Node *focusNode) // optimizacion de guardar nodo en el temporal
{
    temp = malloc(sizeof(Node));

    temp->type = focusNode->type;
    temp->level = focusNode->level;
    temp->imageCard = focusNode->imageCard;
    temp->textureCard = focusNode->textureCard;

    return temp;
}

int craig(Stack *D, Stack *P2, Node *nT) // funcion IA para seleccionar carta
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

    if(peek(D) != NULL) //round1 (itsGoTimeBBY)
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
                    else if(focusNode->type == 'D') // guardar dopplegangers
                    {
                        if(tempD == NULL)
                        {
                            tempD = craigOption(temp, focusNode);
                            cD = i;
                        }
                        else if(tempD->level <= focusNode->level)
                        {
                            tempD = craigOption(temp, focusNode);
                            cD = i;
                        }
                    }
                    else if(focusNode->type == 'K') // guardar knight
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
                    else //guardar min
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
                else //guardar min
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

            if(cT != 0) //checar si hay carta del mismo tipo
                return cT;
            else if(cK != 0 && nT->type == 'G') //caso de no tener Goblin checar si hay knight para matar Goblin
                return cK;
            else if(cD != 0 && nT->level < tempD->level) // caso de no tener del mismo tipo checar si hay Doppleganger
                return cD;
            else if(min != 0) // caso de no tener del mismo tipo y no tener Doppleganger
                return min;
            else
                return 1;
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
                    else if(tempD->level <= focusNode->level)
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

            if(cE != 0)
                return cE;
            else if(cT != 0) //checar si hay carta del mismo tipo
                return cT;
            else if(cK != 0 && nT->type == 'G') //caso de no tener Goblin checar si hay knight para matar Goblin
                return cK;
            else if(cD != 0 && nT->level < tempD->level) // caso de no tener del mismo tipo checar si hay Doppleganger
                return cD;
            else if(min != 0) // caso de no tener del mismo tipo y no tener Doppleganger
                return min;
            else
                return 1;

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

void itsGoTimeBBY(Stack *D, Stack *V1, Stack *V2, Stack *P1, Stack *P2, Stack *P1R2, Stack *P2R2, Stack *eI, int AI) // comienza la primera ronda del juego
{
    Stack *temp = newStack();
    Node *tC;
    Node *nT = NULL;
    Node *nT2 = NULL;
    int neXt = 0;

    while(peek(D) != NULL) // se checa que el deck no este vació para saber cuando terminar la ronda
    {
        BeginDrawing();
        tC = peek(D);
        Node *r = NULL;
        int c = 0;
        int i = 0;

        if(IsKeyPressed(KEY_SPACE))// se utiliza para detectar quese pulso la tecla space y se puede pasar al siguiente turno
            neXt = 15;

        if(nT == NULL || nT2 == NULL) // se verifica sialguno de los dos jugadores no ha selecionado carta para que pueda elegir
            c = selectCard(D, nT, nT2, P1, P2);// llama a la función para elegir carta

        if(D->t == 0) // se checa si es turno del jugador 1
        {
            if(nT != NULL && nT2 != NULL) // detecta que los jugadores ya tengan una carta seleccionar apara comenzar la batlle phase
            {
                displayBackCards(P1, eI);
                displayDeckCard(tC);
                displaySelect(nT, nT2);
            }
            else if(nT == NULL) // Se verifica si el jugador 1 todavia no elige carta
            {
                displayPDeck(P1, eI);
                displayDeckCard(tC);
                DrawText("P1", 1455, 560, 80, WHITE);
                DrawText("P1", 1453, 560, 80, PINK);

                if(c != 0) // se verifica si el jugador unoya eligio carta
                {
                    for(i = 0; i < c; i++) // se recorren las cartas del player 1 hasta encontrar la elegida
                    {
                        r = pop(P1);
                        push(temp, r);
                    }

                    nT = pop(temp);
                    displaySelect(nT, nT2); // se muestra la carta elegida
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
            else if(nT != NULL) // se checa si el player uno ya eligio carta para comenzar el turno del player 2
            {
                if(AI == 0) // se verifica si la bandera de la inteligencia artificial esta apagada para saber el modo del juego
                    displayPDeck(P2, eI);

                displayDeckCard(tC);
                displaySelect(nT, nT2);

                if(AI == 0)
                {
                    DrawText("P2", 1455, 560, 80, WHITE);
                    DrawText("P2", 1453, 560, 80, BLUE);
                }

                if(AI == 1) // detecta la bandera de AI  prendida por lo qeu llama a la función de nuestro AI
                    c = craig(D, P2, nT);

                if(c != 0) // se verifica si el jugador unoya eligio carta
                {
                    for(i = 0; i < c; i++)// se recorren las cartas del player 1 hasta encontrar la elegida
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
        else if(D->t == 1) // se verifica si es turno del player 2
        {
            if(nT != NULL && nT2 != NULL) // se verifica si los dos jugadores ya eligieron carta
            {
                displayBackCards(P1, eI);
                displayDeckCard(tC);
                displaySelect(nT, nT2);
            }
            else if(nT2 == NULL)
            {
                if(AI == 0) // se verifica si la bandera de la inteligencia artificial esta apagada para saber el modo del juego
                    displayPDeck(P2, eI);

                displayDeckCard(tC);

                if(AI == 0) // si la AI esta apagada imprime que es turno del player 2
                {
                    DrawText("P2", 1455, 560, 80, WHITE);
                    DrawText("P2", 1453, 560, 80, BLUE);
                }

                if(AI == 1) // detecta si esta prendida la bandera de la intelgiencia artificial para llamar la función de AI
                    c = craig(D, P2, nT);

                if(c != 0) // se verifica que ya se haya seleccionado carta
                {
                    for(i = 0; i < c; i++) // se busca la carta en el deck del jugador
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
            else if(nT2 != NULL) // se checa que ya haya jugado el player 2 para comenzar el turno depl player 1
            {
                displayPDeck(P1, eI);
                displayDeckCard(tC);
                displaySelect(nT, nT2);

                DrawText("P1", 1455, 560, 80, WHITE);
                DrawText("P1", 1453, 560, 80, PINK);

                if(c != 0) // se verifica que ya haya elegido carta el player 1
                {
                    for(i = 0; i < c; i++) // se busca la carta en el deck del player 1
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

        if(nT != NULL && nT2 != NULL && neXt == 15) // se verifica que ya los dos players hayan elegido sus cartas para comenzar el battle phase
        {
            tC = pop(D);
            rotateImage(tC);

            if(nT->type == nT2->type || nT->type == 'D' || nT2->type == 'D') //comparacion de nivel y comodin
            {
                if(D->t == 0 && nT2->type == 'N' && nT->type == 'D') // se verifica que el player 1 haya elegido Duppleganger el player 2 necromancer y sea el turno del player 1
                {
                    push(V1, nT2);
                    push(P1R2, tC);
                    D->t = 0;
                }
                else if(D->t == 1 && nT->type == 'N' && nT2->type == 'D') // se verifica que el player 2 haya elegido Duppleganger el player 1 necromancer y sea el turno del player 2
                {
                    push(V2, nT);
                    push(P2R2, tC);
                    D->t = 1;
                }
                else if(nT->type == 'N' || nT2->type == 'N') // se verifica que cualquier jugador seleccione necromancer
                {
                    int b = 0;
                    if(nT->type == nT2->type) // si ambos son necromancer
                        b = 1;
                    else if(D->t == 0 && nT2->type == 'D' && nT->type == 'N') // si player 1 es necromancer y el player 2 es Doppleganger y es turno del palyer 1
                        b = 2;
                    else if(D->t == 1 && nT->type == 'D' && nT2->type == 'N') // si player 2 es necromancer y el player 1 es Doppleganger y es turno del palyer 2
                        b = 3;

                    if(nT->level > nT2->level || (nT->level == nT2->level && D->t == 0)) // si la carta del player 1 es mayor a la carta del palyer 2 o que sean del mismo level en el turno del jugador 1
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
                    else if(nT->level < nT2->level || (nT->level == nT2->level && D->t == 1)) // se verifica que la carta del palyer 1 sea menor a la carta del palyer 2 o que tengan el mismo nivel pero sea turno del jugador 1
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
                else if(D->t == 0 && nT->type == 'D' && nT2->type != 'D')  // se verifica que sea turno del P1 , que P1 haya puesto Duppelganger y que P2 tambien haya puesto Duppelganger
                {
                    push(P1R2, tC);
                    D->t = 0;
                }
                else if(D->t == 1 && nT2->type == 'D' && nT->type != 'D') // se verifica que sea turno del P2 , que P1 haya puesto Duppelganger y que P2 tambien haya puesto Duppelganger
                {
                    push(P2R2, tC);
                    D->t = 1;
                }
                else if(nT->level > nT2->level || (nT->level == nT2->level && D->t == 0)) // se checa que el level de la carat del P1 sea mayor a la del P2 o que los levels de ambos players sean iguales y que sea turno del P0
                {
                    push(P1R2, tC);
                    D->t = 0;
                }
                else if(nT->level < nT2->level || (nT->level == nT2->level && D->t == 1)) // Se verifica que el level del P2 sea mayor o que sean iguales los levels y sea truno del P2
                {
                    push(P2R2, tC);
                    D->t = 1;
                }
            }
            else if(nT->type != nT2->type) // se verifica si los types son diferentes 
            {
                if(D->t == 0 && nT->type == 'N' && nT->level > nT2->level) //necromancers puntos directos
                {
                    push(V1, nT);
                    push(P1R2, tC);
                    D->t = 0;
                }
                else if
                        (D->t == 1 && nT2->type == 'N' && nT->level < nT2->level) // se le dan puntos dirctos a P2 por haber ganado con necromancer 
                {
                    push(V2, nT);
                    push(P2R2, tC);
                    D->t = 1;
                }
                else if(D->t == 0 && nT2->type == 'N' && nT->level > nT2->level) // Puntos directos  a P1 por ganar con nrecromancer 
                {
                    push(V1, nT2);
                    push(P1R2, tC);
                    D->t = 0;
                }
                else if(D->t == 1 && nT->type == 'N' && nT->level < nT2->level) // se le dan puntos dirctos a P2 por haber ganado con necromancer  
                {
                    push(V2, nT);
                    push(P2R2, tC);
                    D->t = 1;
                }
                else if(D->t == 0 && nT->type == 'G' && nT2->type == 'K') // se checa que el P1 haya puesto Goblin y el P2 knight para darle la victroia al P2
                {
                    push(P2R2, tC);
                    D->t = 1;
                }
                else if(D->t == 1 && nT->type == 'K' && nT2->type == 'G') // se checa que el P2 haya puesto Goblin y el P2 knight para darle la victroia al P1
                {
                    push(P1R2, tC);
                    D->t = 0;
                }
                else if(D->t == 0) // se verifica que P1 haya empezado para darle la victoria del turno
                {
                    push(P1R2, tC);
                    D->t = 0;
                }
                else if(D->t == 1) // se verifica que P2 haya empezado para darle la victoria del turno
    
                {
                    push(P2R2, tC);
                    D->t = 1;
                }
            }

            if(D->t == 0) // se verifican los turnos para cambiar al que sigue 
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
            neXt = 0; // se reincian las cariables para la segunda vuelta 
        }
        EndDrawing();
    }

}

void round2(Stack *D, Stack *V1, Stack *V2,Stack *P1R2, Stack *P2R2, Stack *eI, int AI) // comienza la ronda 2 
{

    Stack *temp = newStack();
    Node *nT = NULL;
    Node *nT2 = NULL;
    int end = 0;
    int neXt = 0;

    while(end < 13) // se realizan los 13 turnos y cuadno se juega el utlimo termina la ronda 
    {
        BeginDrawing();

        Node *r = NULL;
        int c;
        int i = 0;


        if(IsKeyPressed(KEY_SPACE)) // se utiliza para detectar que se pulso la tecla space y se puede pasar al siguiente turno
            neXt = 15;

        if(nT == NULL || nT2 == NULL) // se verifica sialguno de los dos jugadores no ha selecionado carta para que pueda elegir
            c = selectCard(D, nT, nT2, P1R2, P2R2);

        if(D->t == 0) // se checa si es turno del jugador 1
        {
            if(nT != NULL && nT2 != NULL) // detecta que los jugadores ya tengan una carta seleccionar apara comenzar la batlle phase
            {
                displayBackCards(P1R2, eI);
                displaySelect(nT, nT2);
            }
            else if(nT == NULL) // Se verifica si el jugador 1 todavia no elige carta
            {
                displayPDeck(P1R2, eI);

                DrawText("P1", 1455, 560, 80, WHITE);
                DrawText("P1", 1453, 560, 80, PINK);

                if(c != 0) // se verifica si el jugador unoya eligio carta
                {
                    for(i = 0; i < c; i++) // se recorren las cartas del player 1 hasta encontrar la elegida
                    {
                        r = pop(P1R2);
                        push(temp, r);
                    }

                    nT = pop(temp);
                    displaySelect(nT, nT2);  // se muestra la carta elegida
                    P1R2->cN--;

                    while(peek(temp) != NULL)
                    {
                        r = pop(temp);
                        push(P1R2, r);
                    }

                    c = 0;
                    neXt = 0;
                }
            }
            else if(nT != NULL) // se checa si el player uno ya eligio carta para comenzar el turno del player 2
            {
                displayPDeck(P2R2, eI);
                displaySelect(nT, nT2);

                if(AI == 0) // se verifica si la bandera de la inteligencia artificial esta apagada para saber el modo del juego
                {
                    DrawText("P2", 1455, 560, 80, WHITE);
                    DrawText("P2", 1453, 560, 80, BLUE);
                }

                if(AI == 1) // detecta la bandera de AI  prendida por lo qeu llama a la función de nuestro AI
                    c = craig(D, P2R2, nT);

                if(c != 0) // se verifica si el jugador unoya eligio carta
                {
                    for(i = 0; i < c; i++) // se recorren las cartas del player 1 hasta encontrar la elegida
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
        else if(D->t == 1) // se verifica si es turno del player 2
        {
            if(nT != NULL && nT2 != NULL)  // se verifica si los dos jugadores ya eligieron carta
            {
                displayBackCards(P1R2, eI);
                displaySelect(nT, nT2);
            }
            else if(nT2 == NULL)
            {
                displayPDeck(P2R2, eI);

                if(AI == 0) // si la AI esta apagada imprime que es turno del player 2
                {
                    DrawText("P2", 1455, 560, 80, WHITE);
                    DrawText("P2", 1453, 560, 80, BLUE);
                }

                if(AI == 1)// detecta si esta prendida la bandera de la intelgiencia artificial para llamar la función de AI
                    c = craig(D, P2R2, nT);

                if(c != 0) // se verifica que ya se haya seleccionado carta
                {
                    for(i = 0; i < c; i++) // se busca la carta en el deck del jugador
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
            else if(nT2 != NULL) // se checa que ya haya jugado el player 2 para comenzar el turno depl player 1
            {
                displayPDeck(P1R2, eI);
                displaySelect(nT,nT2);

                DrawText("P1", 1455, 560, 80, WHITE);
                DrawText("P1", 1453, 560, 80, PINK);

                if(c != 0) // se verifica que ya haya elegido carta el player 1
                {
                    for(i = 0; i < c; i++)  // se busca la carta en el deck del player 1
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

        if(nT != NULL && nT2 != NULL && neXt == 15)  // se verifica que ya los dos players hayan elegido sus cartas para comenzar el battle phase
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

int claimWinner(Stack *V1, Stack *V2, Stack *eI) // se verfica quein gano el juego
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


    while(peek(V1) != NULL) // se revisa cuantos hay en el stack de votantes del player 1
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

    while(peek(V2) != NULL) // se revisa cuantos hay en el stack de votantes del player 2
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

    //Goblins
    if(P1TG > P2TG) // con estas condiciones se define quein gano la mayoria de votantes de cada clase
        VT1++;
    else if(P2TG > P1TG)
        VT2++;
    else if(P1TG == P2TG)
    {
        if(P1GMax > P2GMax)
            VT1++;
        else if(P2GMax > P1GMax)
            VT2++;
    }

    //Enanos
    if(P1TE > P2TE)
        VT1++;
    else if(P2TE > P1TE)
        VT2++;
    else if(P1TE == P2TE)
    {
        if(P1EMax > P2EMax)
            VT1++;
        else if (P2EMax > P1EMax)
            VT2++;
    }

    //necromancers
    if(P1TN > P2TN)
        VT1++;
    else if(P2TN > P1TN)
        VT2++;
    else if(P1TN == P2TN)
    {
        if(P1NMax > P2NMax)
            VT1++;
        else if(P2NMax > P1NMax)
            VT2++;
    }

    //doppelgangers
    if(P1TD > P2TD)
        VT1++;
    else if(P2TD > P1TD)
        VT2++;
    else if(P1TD == P2TD)
    {
        if(P1DMax > P2DMax)
            VT1++;
        else if(P2DMax > P1DMax)
            VT2++;
    }

    //knights
    if(P1TK > P2TK)
        VT1++;
    else if(P2TK > P1TK)
        VT2++;
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
