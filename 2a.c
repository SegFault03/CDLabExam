#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isOperator(char );
int isSpecialChar(char );
void processToken(char* , int );

int isOperator(char in)
{
    int i;
    char oparray[] = {'+','-','/','*','=','%','^'};
    int n =0;
    while (n<7) 
    {
        if(in==oparray[n])
        return 1;
        n++;
    }
    return 0;
}

int isSpecialChar(char in)
{
    char arr[] = {';','(',')','{','}','[',']'};
    int p = 0;
    while(p < 7)
    {
        if(in==arr[p])
        return 1;
        p++;
    }
    return 0;
}

void processToken(char *temp, int isdigit)
{
    if(isdigit==1)
    {
        printf("Constant = %s\n",temp);
        return;
    }
    char *keywords[] = {"auto","break",	"case",	"char",	"const",	"continue",	"default",	"do",
"double",	"else",	"enum",	"extern",	"float",	"for",	"goto",	"if",
"int",	"long",	"register",	"return",	"short",	"signed",	"sizeof",	"static",
"struct",	"switch",	"typedef",	"union",	"unsigned",	"void",	"volatile",	"while", ""}, **n;
  n = keywords;
  while (*n != "") {
    if(strcmp(*n,temp)==0)
    {
        printf("Keyword = %s\n",temp);
        return;
    }
    n++;
  }
   printf("Identifier = %s\n",temp);
}

int main()
{
    char input[100], curr, next, temp[10];
    int i = 0, f = 0, isDigit = 1;
    printf("Enter the input: ");
    fgets(input,100,stdin);
    fflush(stdin);
    while(input[i]!='\0')
    {
        curr = input[i];
        next = input[i+1];
        if(isOperator(curr)==1)
        {
            if(f>0)
            {
                temp[f] = '\0';
                processToken(temp, isDigit);
                f = 0;
                isDigit = 1;
            }

            if(next!='\0' && isOperator(next)==1)
            {
                printf("Operator = %c%c\n",curr,next);
                i+=2;
            }
            else
            {
                printf("Operator = %c\n",curr);
                i++;
            }
            continue;
        }
        if((curr >= 97 && curr <= 122) || (curr >=48 && curr <= 57) || curr == '_' || curr == '-')
        {
            if(curr >= 97 && curr <= 122) isDigit = 0;
            temp[f] = curr;
            f++;
            i++;
            continue;
        }
        if(isSpecialChar(curr)==1)
        {
            if(f>0)
            {
                temp[f] = '\0';
                processToken(temp, isDigit);
                f = 0;
                isDigit = 1;
            }
            printf("Special Character = %c\n",curr);
            i++;
            continue;
        }
        if(curr==' ')
        {
            if(f>0)
            {
                temp[f] = '\0';
                processToken(temp, isDigit);
                f = 0;
                isDigit = 1;
            }
            i++;
        }
    }
}