//interpreter







//developed by ahmed masoud







#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Ahmed.h"
typedef struct {
    char name[100];
    char args[100];
    char ops[100];
}function;
function my_funcs[1000];
char copytotk[500];
int counter=0;

int islet(char x){
    if (x>='a'&&x<='z') {
        return 1;
    }
    if (x>='A'&&x<='Z') {
        return 1;
    }
    return 0;
}

int IsNumber(char x){
    if ((x>='0' && x<='9') || x=='.') {
        return 1;
    }
    return 0;
}

int Isoperation2(char x){
    if (x=='+'||x=='-'||x=='/'||x=='*') {
        return 1;
    }
    return 0;
}

int count=0;

int check_avail(char*exp){
    int i=0;
    while (exp[i]!='\0') {
        if (exp[i]=='*'&&(exp[i+1]=='/'||exp[i+1]=='+'||exp[i+1]=='*')) {
            return 0;
        }
        if (exp[i]=='/'&&(exp[i+1]=='/'||exp[i+1]=='+'||exp[i+1]=='*')) {
            return 0;
        }
        if (exp[i]=='+'&&(exp[i+1]=='/'||exp[i+1]=='+'||exp[i+1]=='*')) {
            return 0;
        }
        if (exp[i]=='-'&&(exp[i+1]=='/'||exp[i+1]=='+'||exp[i+1]=='*')) {
            return 0;
        }
        if (Isoperation2(exp[i])&&Isoperation2(exp[i+1])&&Isoperation2(exp[i+2])) {
            return 0;
        }
        i++;
    }
    return 1;
}

float evaluate(char x,float op1,float op2){
    if(x=='+')
        return(op1+op2);
    if(x=='-')
        return(op1-op2);
    if(x=='*')
        return(op1*op2);
    if(x=='/')
        return(op1/op2);
    return 0;}

int priority(char c){
    if (c>='0' && c<= '9') return 0;
    if (c==' ') return 0;
    switch (c)
    {
        case '+' :
        case '-' :
            return 0;
        case '*' :
        case '/' :
            return 1;
        case '(' :
            return 2;
        default :
            return -1;
    }}

void seperate(char*exp,char*out){
    int i=0;
    int c=0;
    while (exp[i]!='\0') {
        if (Isoperation2(exp[i])&&out[c-1]!=' ') {
            out[c]=' ';
            out[c+1]=exp[i];
            out[c+2]=' ';
            c+=3;i++;
        }
        else{
            out[c]=exp[i];
            c++;i++;
        }
    }out[c]='\0';
}

void InfixToPostfix(char exp[],char postfix[]){
    int i;
    int c=0;
    stack s;
    initialize(&s);
    for(i=0; i<strlen(exp); i++)
    {
        if(IsNumber(exp[i])|| exp[i]=='.' ||(Isoperation2(exp[i])&&Isoperation2(exp[i-1])))
            postfix[c++]=exp[i];
        else if(exp[i]==')')
        {
            while(!isempty(&s)&&peep(&s)!='(')
            {
                postfix[c++]=' ';
                postfix[c++]=pop(&s);
            }
            pop(&s);
        }
        else if(isempty(&s))
        {
            if(c>0)
                postfix[c++]=' ';
            push(&s,exp[i]);
        }
        else
        {
            while(!isempty(&s)&&priority(peep(&s))>=priority(exp[i])&&peep(&s)!='(')
            {
                if (postfix[c-1]!=' ')
                    postfix[c++]=' ';
                postfix[c++]=pop(&s);
            }
            if (postfix[c-1]!=' ')
                postfix[c++]=' ';
            push(&s,exp[i]);
        }
    }
    while(!isempty(&s))
    {
        postfix[c++]=' ';
        postfix[c++]=pop(&s);
    }
    postfix[c]='\0';
}

float evaluatepost(char post[]){
    stack s;
    initialize(&s);
    float z;
    char *token;
    float op1,op2,val;
    token = strtok(post," ");
    while (token!=NULL)
    {
        if(IsNumber(token[0])||(Isoperation2(token[0])&&strlen(token)!=1))
        {
            float y= atof(token);
            push(&s,y);
        }
        else
        {
            op2=pop(&s);
            op1=pop(&s);
            val=evaluate(token[0],op1,op2);
            push(&s,val);
        }
        token=strtok(NULL," ");
    }
    val=pop(&s);
    return val;
}

int Isoperation(char x){
    if (x=='+'||x=='-'||x=='/'||x=='*'||x=='('||x==')'||x=='<'||x=='>') {
        return 1;
    }
    return 0;
}/*   123,456,789*/

struct node{
    char key[100];
    double value;
    struct node *next;
};

struct linkedlist{
    struct node *head,*tail;
};

void initll(struct linkedlist *list){
    list->head=NULL;
    list->tail=NULL;
}

struct node *newnode(char*key,double value){
    struct node*n = malloc(sizeof(struct node));
    int i=0;
    for (i =0; i<=strlen(key); i++) {
        n->key[i]=key[i];
    }
    // for (i =0; i<=strlen(value); i++) {
    n->value=value;
    //  }
    n->next = NULL;
    return n;
}

void addhead(struct linkedlist *list,char *key,double value){
    struct node *n = newnode(key, value);
    n->next=list->head;
    list->head=n;
    if (list->tail==NULL) {
        list->tail=n;
    }
}

double search(struct node*n,char *key){
    // if(n==NULL){*out = NULL;}
    while (n) {
        if (strcmp(n->key, key)==0) {
            return  n->value;
        }else{
            n=n->next;
        }}
    return -99;
}

void inter(char *input,struct linkedlist *ll){
    char key[500];
    char output[500];
    char value[500];
    //char input[500];
    char out[500];
    char print[500];
    char temp [500];
    char temp2 [500];
    char check[500];
    char evaluation[500];
    char line[500];
    char cond[500];
    char func_name[500];
    char func_var[500];
    char call_name[500];
    char call_args[500];
    char *tokenin;
    char *tokensv;
    char tknsv[500];
    char *tknin[500];
    char ops[500];
    char args_tok[500];
    char *bbibo;
    int i=0;
    int h,z;
    int xx=0;
    int brktop=0;
    int brktcls=0;
    int c=0;
    int flag5 =0;
    double bibo;
    double bibo2=0;
    double bibo3=0;
    int flag=0;
    int flag2=0;
    int flag3=0;
    int p =0;
    int cntr=0;
    addhead(ll, "e", 2.78);
    addhead(ll, "pi", 3.1415);
    addhead(ll, "masoud", 3.5);
    int nn=0;
    for(nn=0;nn<1;nn++){/*handle more than 1 key in the command line without numbers "handeled not enough testing"*/
        for (i=0; i<500; i++) {
            value[i]='\0';
            print[i]='\0';
            output[i]='\0';
            out[i]='\0';
            temp[i]='\0';
            temp2[i]='\0';
            check[i]='\0';
            line[i]='\0';
            cond[i]='\0';
            tknin[i]='\0';
            tknsv[i]='\0';
            func_name[i]='\0';
            func_var[i]='\0';
            args_tok[i]='\0';
            call_args[i]='\0';
            call_name[i]='\0';
        }
        i=c=h=z=p=cntr=0;
        flag = 0;flag2=0;flag3=0;xx=0;
        i=0;bibo=0;
        brktcls=brktop=0;
        // printf(">>");
        // gets(input);
        if (strcmp(input, "osama")==0) {
            printf("ya3am da 5aleegy w byetzareglo matektebhosh fel program tany :3\n");
            continue;
        }
        if (strlen(input)==0) {
            continue;
        }
        while (input[i]!='\0') {
            if (input[i]=='=') {
                flag=1;
                cntr++;
            }
            i++;
        }
        i=0;c=0;
        while (input[i]!='\0') {
            if (input[i]==' ') {i++;}else{
                temp[c]=input[i];
                c++;i++;
            }
        }
        for (i=0; i<4; i++)
            temp2[i]=temp[i];
        if (strcmp(temp2, "func")==0) {
            i=4;c=0;
            while(temp[i]!='\0'){
                temp2[c]=temp[i];
                i++;c++;}
            //         printf("%s",temp2);
            i=0;c=0;
            while (temp2[i]!='{') {
                func_name[c]=temp2[i];
                i++;c++;
            }
            func_name[c]='\0';
            i++;c=0;
            //           printf("\nname : %s\n",func_name);
            while (temp2[i]!='\0') {
                func_var[c]=temp2[i];
                i++;c++;
            }
            func_var[c-1]='\0';
            //            printf("vars : %s\n",func_var);
            i=c=0;
            // we have two strings func name and func vars//
            while (strcmp(line, "end")!=0) {
                printf(">");gets(line);
                if (strcmp(line, "end")!=0){
                    strcat(my_funcs[counter].ops,strcat(line,",")) ;
                    strcat(my_funcs[counter].args,strcat(func_var, ","));
                    strcpy(my_funcs[counter].name, func_name);}
            }
            counter++;
            //printf("func name : %s\nfunc args: %s\nfunc ops: %s\n",my_funcs->name,my_funcs->args,my_funcs->ops);
            continue;
        }
        for (i=0; i<500; i++) {
            temp2[i]='\0';
        }i=c=0;
        while (temp[i]!='\0') {
            if (temp[i]=='{'){
                flag5=10;
                break;}
            i++;
        }
        p=i;if(flag5==10){
            for (i=0; i<p; i++) {
                call_name[c]=temp[i];
                c++;
            }
            p++;c=0;
            while(temp[p]!='\0'){
                call_args[c]=temp[p];
                c++;p++;}
            call_args[c-1]='\0';
            //  printf("call name : %s call vars : %s",call_name,call_args );
            i=c=p=0;
            for (i=0; i<=counter; i++) {
                if (strcasecmp(call_name, my_funcs[i].name)==0) {
                    //    printf("found\n");
                    strcpy(args_tok, my_funcs[counter-1].args);
                    tokensv=strtok(args_tok, ",");
                    while (tokensv!=NULL) {
                        tknsv[c]=*tokensv;
                        tokensv=strtok(NULL, ",");
                        c++;
                    }
                    tknsv[c]='\0';
                    c=0;
                    tokenin=strtok(call_args, ",");
                    while (tokenin!=NULL) {
                        tknin[c]=malloc(strlen(tokenin));
                        strcpy(tknin[c],tokenin);
                        tokenin=strtok(NULL, ",");
                        c++;
                    }
                    tknin[c]='\0';
                    c=0;
                    while (tknin[c]!='\0'&&tknsv[c]!='\0') {
                        char sv[10];
                        sv[0]=tknsv[c];
                        sv[1]='\0';
                        char *in[10];
                        in[0]=malloc(strlen(tknin[c]));
                        in[0]=tknin[c];
                        if (islet(*in[0])) {
                            if (search(ll->head, *in)!=-99) {
                                sprintf(*in, "%g",search(ll->head, *in));
                            }else{printf("wrong function argument\n");flag2=100;return;}
                        }
                        addhead(ll, sv, atof(in[0]));
                        c++;
                    }
                    char *hangarab[500];
                    int equall=0;
                    int greater=0;
                    int smaller=0;
                    strcpy(copytotk, my_funcs[counter-1].ops);
                    i=0;int comma=0;
                    while (copytotk[i]!='\0') {
                        if(copytotk[i]==',')
                            comma++;
                        i++;
                    }
                    bbibo=strtok_r(copytotk, ",",hangarab);
                    // hangarab[0][strlen(hangarab[0])]='\0';
                    //while(bbibo!=NULL){
                    while(bbibo!=NULL) {
                        if (bbibo[0]=='i'&&bbibo[1]=='f') {
                            p=0;
                            c=3;flag5=flag3=0;
                            while (bbibo[c]!='\0') {
                                if(bbibo[c]=='=')
                                    equall=1;
                                if(bbibo[c]=='<')
                                    smaller=1;
                                if(bbibo[c]=='>')
                                    greater=1;
                                c++;
                            }
                            c=3;
                            /*remove spaces from bbibo*/
                            if(equall){
                                while (bbibo[c]!='=') {
                                    check[p]=bbibo[c];
                                    p++;c++;
                                }c++;p=0;
                                while (bbibo[c]!='\0') {
                                    value[p]=bbibo[c];
                                    p++;c++;
                                }
                                if (search(ll->head, check)==atof(value)) {
                                    inter(bbibo=strtok_r(*hangarab,",",&hangarab[0]), ll);
                                    bbibo=strtok_r(*hangarab,",",&hangarab[0]);
                                    if(bbibo==NULL) return;
                                    if (strcmp(bbibo, "else")==0) {
                                        bbibo=strtok_r(*hangarab,",",&hangarab[0]);
                                        bbibo=strtok_r(*hangarab,",",&hangarab[0]);
                                        if(bbibo==NULL)return;
                                        inter(bbibo, ll);
                                        bbibo=strtok_r(*hangarab,",",&hangarab[0]);
                                        while (bbibo!=NULL) {
                                            inter(bbibo, ll);
                                            bbibo=strtok_r(*hangarab,",",&hangarab[0]);
                                            if (strcmp(*hangarab, "")) {
                                                bbibo=NULL;
                                            }}
                                    }
                                    flag5=10;
                                }else{
                                    //printf("false\n");
                                    bbibo=strtok_r(*hangarab,",",&hangarab[0]);
                                    if (strcmp(hangarab[0], "")==0)
                                        return;
                                    if (strcmp(hangarab[0], "else")) {
                                        bbibo=strtok_r(*hangarab,",",&hangarab[0]);
                                        bbibo=strtok_r(*hangarab,",",&hangarab[0]);
                                        inter(bbibo, ll);
                                    }
                                    if (strcmp(hangarab[0],"")==0) {
                                        bbibo=NULL;
                                        continue;
                                    }else{
                                        bbibo=strtok_r(*hangarab,",",&hangarab[0]);
                                        flag3=100;
                                        continue;}
                                }}
                            p=0;
                            c=3;flag5=flag3=0;
                            if(smaller){
                                while (bbibo[c]!='<') {
                                    check[p]=bbibo[c];
                                    p++;c++;
                                }c++;p=0;
                                while (bbibo[c]!='\0') {
                                    value[p]=bbibo[c];
                                    p++;c++;
                                }
                                if (search(ll->head, check)<atof(value)) {
                                    inter(bbibo=strtok_r(*hangarab,",",&hangarab[0]), ll);
                                    bbibo=strtok_r(*hangarab,",",&hangarab[0]);
                                    flag5=10;
                                }else{
                                    printf("false\n");
                                    bbibo=strtok_r(*hangarab,",",&hangarab[0]);
                                    if (strcmp(hangarab[0],"")==0) {
                                        bbibo=NULL;
                                        continue;
                                    }else{
                                        bbibo=strtok_r(*hangarab,",",&hangarab[0]);
                                        flag3=100;
                                        continue;}
                                }}
                            p=0;
                            c=3;flag5=flag3=0;
                            if(greater){
                                while (bbibo[c]!='>') {
                                    check[p]=bbibo[c];
                                    p++;c++;
                                }c++;p=0;
                                while (bbibo[c]!='\0') {
                                    value[p]=bbibo[c];
                                    p++;c++;
                                }
                                if (search(ll->head, check)>atof(value)) {
                                    inter(bbibo=strtok_r(*hangarab,",",&hangarab[0]), ll);
                                    bbibo=strtok_r(*hangarab,",",&hangarab[0]);
                                    flag5=10;
                                }else{
                                    printf("false\n");
                                    bbibo=strtok_r(*hangarab,",",&hangarab[0]);
                                    if (strcmp(hangarab[0],"")==0) {
                                        bbibo=NULL;
                                        continue;
                                    }else{
                                        bbibo=strtok_r(*hangarab,",",&hangarab[0]);
                                        flag3=100;
                                        continue;}
                                }}
                            if (flag3!=100&&flag5!=10) {
                                bbibo=NULL;
                                continue;
                            }}
                        if (bbibo==NULL) {
                            return;
                        }
                        inter(bbibo, ll);
                        bbibo=strtok_r(*hangarab,",",&hangarab[0]);
                    }
                    //}
                    // inter(bbibo, ll);
                    break;
                    // printf("token sv : %s token in : %s",tknsv,tknin);
                }else if(i>counter){
                    printf("not found\n");
                    continue;
                }
            }
            continue;
        }
        i=0;c=0;p=0;flag5=0;
        if (flag==0) {
            while (input[i]!='\0') {
                if (input[i]==' ') {i++;}else{
                    temp[c]=input[i];
                    c++;i++;
                }
            }
            i=c=0;
            for (i=0; i<5; i++) {
                check[i]=temp[i];
            }i++;
            if (strcmp(check, "print")==0) {
                while(input[i]!='\0')
                { print[c]=input[i];
                    c++;i++;}
                printf("%s\n",print);
                continue;
            }
            for (i=0; i<500; i++) {
                check[i]='\0';
                print[i]='\0';
            }
            c=0;
            i=2;
            while (temp[i]!='\0') {
                temp2[c]=temp[i];c++;i++;}
            if (temp[0]=='+'&&temp[1]=='+'&&search(ll->head, temp2)!=-99) {
                printf("%s -> %g\n",temp2,search(ll->head, temp2));
                addhead(ll, temp2, search(ll->head, temp2)+1) ;
                continue;
            }
            for (i=0; i<500; i++) {
                temp2[i]='\0';
            }
            i=c=0;
            i=2;
            while (temp[i]!='\0') {
                temp2[c]=temp[i];c++;i++;}
            if (temp[0]=='-'&&temp[1]=='-'&&search(ll->head, temp2)!=-99) {
                printf("%s -> %g\n",temp2,search(ll->head, temp2));
                addhead(ll, temp2, search(ll->head, temp2)-1) ;
                continue;
            }
            for (i=0; i<500; i++) {
                temp2[i]='\0';
            }
            i=c=0;
            while (!Isoperation2(temp[i])&&temp[i]!='\0') {
                temp2[c]=temp[i];c++;i++;
            }
            if (search(ll->head, temp2)!=-99) {
                if (temp[i]=='+'&&temp[i+1]=='+'&&temp[i+2]=='\0') {
                    printf("%s -> %g\n",temp2,search(ll->head, temp2)+1);
                    addhead(ll, temp2, search(ll->head, temp2)+1);
                    continue;
                }
            }
            for (i=0; i<500; i++) {
                temp2[i]='\0';
            }
            i=c=0;
            while (!Isoperation2(temp[i])&&temp[i]!='\0') {
                temp2[c]=temp[i];c++;i++;
            }
            if (search(ll->head, temp2)!=-99) {
                if (temp[i]=='-'&&temp[i+1]=='-'&&temp[i+2]=='\0') {
                    printf("%s -> %g\n",temp2,search(ll->head, temp2)-1);
                    addhead(ll, temp2, search(ll->head, temp2)-1);
                    continue;
                }
            }
            for (i=0; i<500; i++) {
                temp2[i]='\0';
            }
            i=c=0;
            if (!check_avail(temp)) {
                printf("bad arguments\n");
                continue;
            }
            flag=0;
            i=0;
            while (temp[i]!='\0') {
                if (temp[i]== ')') {
                    brktcls++;
                }
                if (temp[i]=='(') {
                    brktop++;
                }
                if (temp[i]==')'&&temp[i+1]=='(') {
                    flag=1;
                }
                i++;
            }
            if (brktop!=brktcls) {
                printf("bad arguments\n");
                continue;
            }
            if (flag) {
                printf("bad arguments\n");
                continue;
            }
            i=0;flag=0;
            while (temp[i]!= '\0') {
                if (!(IsNumber(temp[i])||Isoperation(temp[i]))) {
                    //out[c]=value[i];
                    while ( !Isoperation(temp[i])&& temp[i]!='\0') {//osama 5aleegy error !is number kant hna
                        out[c]=temp[i];
                        i++;
                        c++;
                    }
                    //    output[h]=search(ll.head, out);
                    if (search(ll->head, out)==-99) {
                        printf("bad arguments\n");
                        flag2=1;
                        break;
                    }
                    sprintf(&output[h], "%g",search(ll->head, out));
                    sprintf(temp2, "%g",search(ll->head, out));
                    double bibo = strlen(temp2);
                    h+=bibo;
                }
                else{
                    output[h]=temp[i];
                    h++;
                    i++;
                    flag5=2;
                    for (p=0; p<500; p++) {
                        out[p]='\0';
                    }p=0;c=0;
                }
            }
            if (flag2) {
                continue;
            }
            if (flag5) {i=0;
                while (input[i]!='\0') {
                    if (Isoperation(input[i])||IsNumber(input[i])) {
                        /*if anything goes wrong by tomorrow monday undo is operation to is number */
                        xx=1;
                    }
                    i++;
                }
                if(xx){
                    //here you should calculate output then inject it//
                    if (!Isoperation2(input[i-1])) {
                        InfixToPostfix(output, evaluation);
                        bibo=evaluatepost(evaluation);
                        key[0]='A';key[1]='N';key[2]='S';
                        addhead(ll, "ANS", bibo);
                        printf("%s -> %g\n",key,bibo);
                        continue;}
                    else {
                        printf("bad arguments\n");
                        continue;
                    }
                }
            }
            if (flag == 2) {
                double bibo = atof(output);
                addhead(ll, "ANS", bibo);
                printf("ANS -> %s\n",output);
                continue;
            }
            i=c=flag=0;p=0;
            while (input[i]!='\0') {
                if (input[i]==' ') {i++;}
                else{
                    temp[p]=input[i];
                    p++;
                    i++;
                }
            }
            if(( search(ll->head, temp))==-99)
                printf("bad arguments or variable not pre assigned\n");
            else{
                printf("%s -> %g\n",temp,search(ll->head, temp));continue;}
        }
        i=c=p=0;
        if(flag){
            while (input[i]!='\0') {
                if (input[i]!=' ') {
                    temp[c]=input[i];
                    c++;i++;
                }
                else {i++;}}
            c=0;i=2;p=0;
            if (temp[0]=='i'&&temp[1]=='f') {
                while (temp[i]!='\0') {
                    check[c]=temp[i];
                    i++;c++;
                }
                c=0;
                while (check[c]!='=') {
                    key[p]=check[c];
                    c++;p++;
                }
                c++;p=0;
                while (check[c]!='\0') {
                    value[p]=check[c];
                    p++;c++;
                }
                p=i=c=0;
                while (value[i]!='\0') {
                    if (Isoperation2(value[i])) {
                        if(!check_avail(value)){
                            flag2=5;break;}
                        InfixToPostfix(value, cond);
                        sprintf(value, "%g",evaluatepost(cond));
                    }i++;
                }
                if (flag2==5) {
                    printf("bad arguments\n");
                    continue;
                }
                if (search(ll->head, key)==(float)atof(value)) {
                    flag5=5;
                }
                printf(">");gets(line);
                p=i=c=0;
                while (line[i]!='\0') {
                    if (line[i]==' ') {
                        i++;
                    }else{
                        temp2[c]=line[i];
                        i++;c++;
                    }
                }for (p=0; p<500; p++)
                    temp[p]='\0';
                for (p=0; p<=4; p++) {
                    temp[p]=temp2[p];
                }
                p=5;c=0;
                while (temp2[p]!='\0') {
                    print[c]=temp2[p];
                    p++;c++;
                }
                if (strcmp(temp, "print")==0&&flag5==5) {
                    printf("%s\n",print);
                    continue;
                }
                if (flag5==5) {
                    inter(line, ll);
                    continue;
                }else{
                    printf("FALSE\n");
                    continue;
                }
            }
            c=i=0;
            while (input[i]!='\0')  {
                if (input[i] == ' '){i++;} //removing spaces
                else{
                    if (input[i]== '=' )
                        break;
                    else{
                        key[c]=input[i];
                        c++;
                        i++;
                    }
                }
            }
            key[c]='\0';
            c=0;
            p=0;
            if (!islet(key[0])) {
                printf("bad arguments\n");
                continue;
            }
            while (key[c]) {
                if (Isoperation(key[c])) {
                    printf("bad arguments\n");
                    flag3=1;
                    break;
                }
                if (!IsNumber(key[c])) {
                    flag=5;
                }c++;
            }
            if (flag3) {
                continue;
            }
            if (flag!=5) {
                printf("bad arguments\n");
                continue;
            }
            flag=0;
            p=0;
            c=0;
            i++;
            while (input[i]!='\0'){
                if(input[i]!=' '){
                    value[c]=input[i];
                    c++;i++;
                }
                else i++;
            }
            // printf("=%s\n",value);
            value[c]='\0';
            i=c=0;
            int h =1;int z=0;
            /*dont forget handeling function to check availiity of 2 conseq. oper. and dont forget to handle it if no =*/
            if (Isoperation2(value[0])&&value[0]!='-') {
                printf("bad arguments\n");
                continue;
            }
            while (value[h]!='\0') {
                check[z]=value[h];
                h++;z++;
            }
            check[z]='\0';
            h=0;z=0;
            if (cntr==2) {
                if(!IsNumber(check[0])){
                    sprintf(temp,"%g",search(ll->head, check));
                    sprintf(temp2,"%g",search(ll->head, key));
                    if (search(ll->head, check)==-99||search(ll->head, key)==-99) {
                        printf("bad arguments\n");
                        continue;
                    }
                    if (strcmp(temp, temp2)==0) {
                        printf("they are equall\n");
                        continue;
                    }else{
                        printf("not equall\n");
                        continue;
                    }
                }else{
                    sprintf(temp2,"%g",search(ll->head, key));
                    if (search(ll->head, key)==-99) {
                        printf("bad arguments\n");
                        continue;
                    }
                    if (strcmp(check, temp2)==0) {
                        printf("they are equall\n");
                        continue;
                    }else{
                        printf("not equall\n");
                        continue;
                    }
                }
            }
            if (!check_avail(value)) {
                printf("bad arguments\n");
                continue;
            }
            while (value[i]!='\0') {
                if (value[i]== ')') {
                    brktcls++;
                }
                if (value[i]=='(') {
                    brktop++;
                }
                if (value[i]==')'&&value[i+1]=='(') {
                    flag=1;
                }
                i++;
            }
            if (brktop!=brktcls) {
                printf("bad arguments\n");
                continue;
            }
            if (flag) {
                printf("bad arguments\n");
                continue;
            }
            i=0;flag=0;
            while (value[i]!= '\0') {
                if (!(IsNumber(value[i])||Isoperation(value[i]))) {
                    //out[c]=value[i];
                    while ((!IsNumber(value[i]) && !Isoperation(value[i]))&& value[i]!='\0') {
                        out[c]=value[i];
                        i++;c++;
                    }
                    //    output[h]=search(ll.head, out);
                    if (search(ll->head, out)==-99) {
                        printf("bad arguments\n");
                        flag2=1;
                        break;
                    }
                    sprintf(&output[h], "%g",search(ll->head, out));
                    sprintf(temp, "%g",search(ll->head, out));
                    double bibo = strlen(temp);
                    h+=bibo;
                }
                else{
                    output[h]=value[i];
                    h++;
                    i++;
                }
                for (int y =0; y<500; y++) {
                    out[y]='\0';
                    c=0;
                }
            }
            if (flag2||flag3) {
                continue;
            }
            value[i]='\0';
            //output[h]='\0';
            out[z]='\0';
            /*you should evaluate output then inject it */
            InfixToPostfix(output, evaluation);
            double bibo2=evaluatepost(evaluation);
            printf("%s = %g\n",key,bibo2);
            //           printf("ans : %f\n",bibo2);
            addhead(ll, key, bibo2);
            /*     for (i=0; i<500; i++) {
             value[i]='\0';
             output[i]='\0';
             out[i]='\0';
             temp[i]='\0';
             temp2[i]='\0';
             key[i]='\0';
             evaluation[i]='\0';
             input[i]='\0';
             }i=c=h=z=0;*/
        }
    }
}

int main(){
    char input[500];
    struct linkedlist  ll;
    initll(&ll);
    printf("in func if cond no space before or after = sign\n");
    for(;;){
        for (int i=0; i<500; i++) {
            input[i]='\0';
        }
        printf(">>");
        gets(input);
        if(strcmp(input, "exit")==0||strcmp(input, "quit")==0)return 0;
        if(strcmp(input, "bibo")==0){
            printf("bibo da gamd fash5\n");
        continue;}
        inter(input,&ll);
    }
    return 0;
}

