#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include <time.h>
#include "claim.h"
#include "stack.h"

int main(void)
{
    // inicializar variables y banderas
    const int screenWidth = 1600;
    const int screenHeight = 900;
    int start = 1;
    int shuffleR = 1;
    int r2 = 0;
    int nextround = 0;
    int winner = 0;
    int WResult = 0;
    int rules = 0;
    int AI = 0;
    int mode = 0;
    int *P1G = initEncapsulation();
    int *P2G = initEncapsulation();
    int *P1E = initEncapsulation();
    int *P2E = initEncapsulation();
    int *P1N = initEncapsulation();
    int *P2N = initEncapsulation();
    int *P1D = initEncapsulation();
    int *P2D = initEncapsulation();
    int *P1K = initEncapsulation();
    int *P2K = initEncapsulation();

    Stack *V1;
    Stack *V2;
    Stack *D;
    Stack *P1R2;
    Stack *P2R2;
    Stack *P1;
    Stack *P2;
    Stack *eI;

    InitWindow(screenWidth, screenHeight, "CLAIM"); // crear ventana

    SetTargetFPS(60); // velocidad de cada frame

    while(!WindowShouldClose())    // Detect window close button or ESC key
    {
        if(shuffleR == 1) // creacion de nueva partida
        {
            V1 = newStack();
            V2 = newStack();
            D = newDeck();
            P1R2 = newStack();
            P2R2 = newStack();
            P1 = newPlayer(D);
            P2 = newPlayer(D);
            eI = extraImages();

            shuffleR = 0;
        }

        BeginDrawing();

        if(start == 1) // mostrar menu
            drawStart();

        if(rules == 1) // mostrar reglas
            displayRules(eI);

        if(mode == 1 && winner == 0) // mostrar pantalla de seleccion de jugador
            drawMode(eI);

        if(IsKeyPressed(KEY_ENTER)) // cambiar banderas de start y mode para comenzar round 1
        {
            start = 0;
            mode = 1;
        }

        if(start == 1 && IsKeyPressed(KEY_LEFT_SHIFT)) // cambiar banderas de start y rules para ir a pantalla de seleccion
        {
            rules = 1;
            start = 2;
        }

        if(start == 2 && IsKeyPressed(KEY_M)) // cambiar banderas de start y rules para regresar al menu
        {
            rules = 0;
            start = 1;
        }

        if(mode == 1) // cambiar banderas de AI y mode para seleccionar el modo de juego
        {
            if(IsKeyPressed(KEY_C))
            {
                mode = 0;
                AI = 1;
            }
            else if(IsKeyPressed(KEY_V))
                mode = 0;
        }

        if(start == 0 && mode == 0) // comienzo del juego
        {
            if(peek(D) != NULL) // round 1
            {
                itsGoTimeBBY(D, V1, V2, P1, P2, P1R2, P2R2, eI, AI);
                nextround = 1;
            }

            if(peek(D) == NULL && nextround == 1) // cambio a round 2
            {
                drawRound2(eI);
                r2++;

                if(r2 >= 50)
                    nextround = 0;
            }

            if(peek(P1R2) != NULL && peek(P2R2) != NULL && r2 >= 50 && winner == 0) // round 2
            {
                round2(D, V1, V2, P1R2, P2R2, eI, AI);
                winner = 1;
                r2 = 0;

                // vaciado de stacks globales
                while(peek(P1R2) != NULL)
                    pop(P1R2);
                while(peek(P2R2) != NULL)
                    pop(P2R2);

                WResult = claimWinner(V1, V2, eI, AI, P1G, P2G, P1E, P2E, P1N, P2N, P1D, P2D, P1K, P2K); // obtener al ganador
                ClearBackground(BLACK);
            }

            if(WResult != 0) // mostrar pantalla del ganador
            {
                Winner(eI, WResult, AI);
                displayResultTable(AI, P1G, P2G, P1E, P2E, P1N, P2N, P1D, P2D, P1K, P2K);
            }

        }

        EndDrawing();
    }

    CloseWindow();

    unloadsExtraImages(eI); // unload de imagenes extras

    if(peek(D) != NULL) // unload round 1
        unloadsImages(D, P1, P2);
    else if(peek(P1R2) != NULL && peek(P2R2) != NULL) // unload round 2
        unloadsImages(D, P1R2, P1R2);

    return 0;
}
