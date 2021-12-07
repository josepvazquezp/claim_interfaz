#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "claim.h"

Stack* newStack() // creacion de nuevo Stack
{
    Stack *s = malloc(sizeof(Stack));
    s->head = NULL;
    s->cN = 0;
    s->t = 0;
    return s;
}

void push(Stack* s, Node* data) // añadir nodo parte por parte de la estructura de claim
{
    if(s->head == NULL) // caso del primer elemento
    {
        s->head = malloc(sizeof(Node));
        s->head->level = data->level;
        s->head->type = data->type;
        s->head->imageCard = data->imageCard;
        s->head->textureCard = data->textureCard;
        s->head->next = NULL;
        return;
    }

    // caso de un nuevo nodo
    Node* n = malloc(sizeof(Node));
    n->level = data->level;
    n->type = data->type;
    n->imageCard = data->imageCard;
    n->textureCard = data->textureCard;
    n->next = s->head;
    s->head = n;

}

void* pop(Stack* s) // quitar nodo y obtener dicho valor
{
    if(s->head == NULL) // caso en tener un Stack vacio
        return NULL;

    // eliminacion del nodo
    Node* toDel = s->head;
    Node* toRet = malloc(sizeof(Node));
    toRet->level = s->head->level;
    toRet->type = s->head->type;
    toRet->imageCard = s->head->imageCard;
    toRet->textureCard = s->head->textureCard;
    s->head = s->head->next;
    free(toDel);

    return toRet;
}

void* peek(Stack* s) // obtener el ultimo valor del Stack sin quitarlo
{
    if(s->head == NULL)
        return NULL;
    return s->head;
}