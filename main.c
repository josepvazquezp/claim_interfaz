#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include <time.h>
#include "claim.h"
#include "stack.h"

int main(void)
{
    const int screenWidth = 1600;
    const int screenHeight = 900;
    int start = 1;
    int shuffleR = 1;
    int r2 = 0;
    int nextround = 0;
    int winner = 0;

    Stack *V1;
    Stack *V2;
    Stack *D;
    Stack *P1R2;
    Stack *P2R2;
    Stack *P1;
    Stack *P2;
    Stack *eI;

    InitWindow(screenWidth, screenHeight, "CLAIM");

    SetTargetFPS(60);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if(shuffleR == 1)
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

        if(start == 1)
            drawStart();

        if(GetKeyPressed() == KEY_ENTER)
            start = 0;

        if (GetKeyPressed() == KEY_N)
            r2 = 1;


        if(start == 0)
        {
            if(peek(D) != NULL)
            {
                itsGoTimeBBY(D, V1, V2, P1, P2, P1R2, P2R2, eI);
                nextround = 1;
            }
            else if(nextround == 1)
            {
                drawRound2(eI);
                r2++;
            }

            if(peek(P1R2) != NULL && peek(P2R2) != NULL && r2 >= 50 )
            {
                round2(D, V1, V2, P1R2, P2R2, eI);
                nextround = 0;
                winner = 1;
            }
            //else
            //{   if (winner == 1)
            //{
            //    claimWinner(V1, V2, eI);
            //  }

            //}
        }

        EndDrawing();
    }

    CloseWindow();

    unloadsExtraImages(eI);

    if(peek(D) != NULL)
        unloadsImages(D, P1, P2);
    else if(peek(P1R2) != NULL && peek(P2R2) != NULL)
        unloadsImages(D, P1R2, P1R2);

    return 0;
}
