//
//  Ahmed.c
//  Ahmed
//
//  Created by Ahmed Masoud on 3/11/15.
//  Copyright (c) 2015 Ahmed Masoud. All rights reserved.
//

#include <stdio.h>
#include "Ahmed.h"

void initialize(stack *s){s->top=0;}
void push(stack *s,type value) {if(!isfull(s))s->items[s->top++]=value;}
void pushc(stack *s,char value) {s->items[s->top++]=value;}
type pop(stack *s) {if(!isempty(s))return s->items[--s->top];return 0;}
char popc(stack *s) {return s->items[--s->top];}
int isfull(stack *s) {return s->top<stacksize?0:1 ;}
int isempty(stack *s) {return s->top==0?1:0;}
void makeempty(stack *s) { while (!isempty(s))pop(s);}
void display(stack *s) {
    stack cop; initialize(&cop);
    printf("[");
    while (!isempty(s)) {
        float x=pop(s);
        printf("%.2f ",x);
        push(&cop,x); }
    printf("]\n");
    while (!isempty(&cop))
        push (s,pop(&cop)); }
int peep( stack *s){
    int x=pop(s);
    push(s,x);
    return x;
}
char getstackchartop(stack *s){
    return s->items[s->top];
}