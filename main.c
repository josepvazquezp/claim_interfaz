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

    Stack *V1 = newStack();
    Stack *V2 = newStack();
    Stack *D = newStack();
    Stack *P1R2 = newStack();
    Stack *P2R2 = newStack();
    Stack *P1 = newStack();
    Stack *P2 = newStack();

    InitWindow(screenWidth, screenHeight, "CLAIM");

    SetTargetFPS(60);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

        if(start == 1)
            drawStart();

        if(shuffleR == 1)
        {
            V1 = newStack();
            V2 = newStack();
            D = newDeck();
            P1R2 = newStack();
            P2R2 = newStack();
            P1 = newPlayer(D);
            P2 = newPlayer(D);

            shuffleR = 0;
        }

        if(GetKeyPressed() == KEY_ENTER)
            start = 0;

        if(start == 0)
        {
            //displayPDeck(D, P1, peek(D));


            itsGoTimeBBY(D, V1, V2, P1, P2, P1R2, P2R2);


            /*
            while (peek(P1R2) != NULL && peek(P2R2) != NULL)
            {
                round2(D, V1, V2, P1R2, P2R2);
            }
             */

            //claimWinner(V1, V2);
        }

        EndDrawing();
    }

    CloseWindow();


    return 0;
}
