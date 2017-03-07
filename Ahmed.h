//
//  Ahmed.h
//  Ahmed
//
//  Created by Ahmed Masoud on 3/11/15.
//  Copyright (c) 2015 Ahmed Masoud. All rights reserved.
//

#ifndef Ahmed_Ahmed_h
#define Ahmed_Ahmed_h
#define type float
#define stacksize 1000

typedef struct {
    int top;
    type items[stacksize];
}stack;
void initialize(stack *s) ;
void push(stack *s,type value) ;
type pop(stack *s) ;
int isfull(stack *s) ;
int isempty(stack *s) ;
void makeempty(stack *s);
void display(stack *s);
void pushc(stack *s,char value);
char popc(stack *s);
int peep( stack *s);
char getstackchartop(stack *s);


#endif
