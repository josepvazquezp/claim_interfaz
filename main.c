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
    int WResult = 0;
    int rules = 0;


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

    while(!WindowShouldClose())    // Detect window close button or ESC key
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

        if(rules == 1)
            displayRules(eI);

        if(IsKeyPressed(KEY_ENTER))
            start = 0;

        if(start == 1 && IsKeyPressed(KEY_LEFT_SHIFT))
        {
            rules = 1;
            start = 2;
        }

        if(start == 2 && IsKeyPressed(KEY_M))
        {
            rules = 0;
            start = 1;
        }

        if(start == 0)
        {
            if(peek(D) != NULL)
            {
                itsGoTimeBBY(D, V1, V2, P1, P2, P1R2, P2R2, eI);
                nextround = 1;
            }

            if(peek(D) == NULL && nextround == 1)
            {
                drawRound2(eI);
                r2++;

                if(r2 >= 50)
                    nextround = 0;
            }

            if(peek(P1R2) != NULL && peek(P2R2) != NULL && r2 >= 50 && winner == 0)
            {
                round2(D, V1, V2, P1R2, P2R2, eI);
                winner = 1;
                r2 = 0;

                while(peek(P1R2) != NULL )
                    pop(P1R2);
                while(peek(P2R2) != NULL )
                    pop(P2R2);

                WResult = claimWinner(V1, V2, eI);
                ClearBackground(BLACK);
            }

            if(WResult != 0)
                Winner(eI, WResult);

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
