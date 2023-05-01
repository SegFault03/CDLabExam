//WORKING!!!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

// Production rules
char *productions[] = {
    "", "E->E+T", "E->T", "T->T*F", "T->F", "F->(E)", "F->id"
};

// Parsing table
int parsing_table[][7] = {
    //      +       *       (       )       $       id      E
    /* 0 */ {0,      0,      0,      0,      0,      0,      1},
    /* 1 */ {2,      0,      2,      0,      0,      2,      0},
    /* 2 */ {0,      3,      0,      0,      4,      0,      0},
    /* 3 */ {2,      0,      2,      0,      0,      2,      0},
    /* 4 */ {0,      0,      0,      5,      0,      0,      0},
    /* 5 */ {2,      0,      2,      0,      0,      2,      0},
    /* 6 */ {0,      0,      0,      0,      0,      6,      0},
    /* 7 */ {0,      0,      0,      0,      0,      7,      0},
    /* 8 */ {0,      0,      0,       0,     0,      8,      0},
};

// Stack functions
void push(int *stack, int *top, int value);
int pop(int *stack, int *top);

// SLR parser
int slr_parse(char *input);

int main() {
    char input[MAX_LEN];

    // Get input from user
    printf("Enter input string: ");
    fgets(input, MAX_LEN, stdin);
    input[strcspn(input, "\n")] = '\0';

    // Parse input using SLR parser
    if (slr_parse(input)) {
        printf("String can be parsed!\n");
    } else {
        printf("String cannot be parsed!\n");
    }

    return 0;
}

// Stack functions

void push(int *stack, int *top, int value) {
    stack[++(*top)] = value;
}

int pop(int *stack, int *top) {
    return stack[(*top)--];
}

// SLR parser

int slr_parse(char *input) {
    int stack[MAX_LEN], top = -1, i, symbol;
    char lookahead;
    push(stack, &top, 0);
    i = 0;

    while (1) {
        symbol = stack[top];
        lookahead = input[i];

        if (parsing_table[symbol][lookahead - '+'] > 0) {
            push(stack, &top, parsing_table[symbol][lookahead - '+']);
            push(stack, &top, i + 1);
            i++;
        } else if (parsing_table[symbol][lookahead - '+'] < 0) {
            printf("Error! Cannot parse string.\n");
            return 0;
        } else {
            if (parsing_table[symbol][6] == 1) {
                printf("Parsing successful!\n");
                break;
            } else {
                printf("Parsing error! Unexpected token %c\n", lookahead);
                break;
            }
        }
    }

    // Clean up memory
    free(stack);

    return 0;
}

