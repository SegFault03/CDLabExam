//DOES NOT WORK!!!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Predefined grammar
char *grammar[] = {
    "S -> E",
    "E -> E + T",
    "E -> T",
    "T -> T * F",
    "T -> F",
    "F -> ( E )",
    "F -> id"
};
int num_rules = 7;

// Parsing table
int table[][6] = {
    //    id   +    *    (    )    $
    {   2,  -1,  -1,   2,  -1,  -1 },  // S
    {   4,   3,  -1,   4,  -1,  -1 },  // E
    {  -1,   5,  -1,  -1,  -1,   0 },  // T
    {  -1,  -1,   6,  -1,  -1,   0 },  // F
    {   7,  -1,  -1,   7,  -1,  -1 },  // (E)
    {   8,  -1,  -1,   9,  -1,  -1 }   // id
};

// Stack structure
typedef struct {
    int *arr;
    int top;
    int size;
} stack_t;

// Initialize stack
stack_t *init_stack(int size) {
    stack_t *stack = (stack_t *) malloc(sizeof(stack_t));
    stack->arr = (int *) malloc(size * sizeof(int));
    stack->top = -1;
    stack->size = size;
    return stack;
}

// Push to stack
void push(stack_t *stack, int item) {
    if (stack->top == stack->size - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->top++;
    stack->arr[stack->top] = item;
}

// Pop from stack
int pop(stack_t *stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    int item = stack->arr[stack->top];
    stack->top--;
    return item;
}

// Peek at top of stack
int peek(stack_t *stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->arr[stack->top];
}

// Parse input string using CLR(1) parser
void parse(char *input) {
    // Initialize stack and add start symbol
    stack_t *stack = init_stack(strlen(input));
    push(stack, 0);

    // Initialize index and lookahead
    int index = 0;
    char lookahead = input[index];

    while (1) {
        int state = peek(stack);
        int symbol = -1;

        if (lookahead >= 'a' && lookahead <= 'z') {
            symbol = 0;
        } else if (lookahead == '+') {
            symbol = 1;
        } else if (lookahead == '*') {
            symbol = 2;
        } else if (lookahead == '(') {
            symbol = 3;
        } else if (lookahead == ')') {
            symbol = 4;
       
        } else {
            /* Lookup the action to take */
            int row = state - 1;
            int col = symbol - 1;
            int action = table[row][col];

            /* Determine the type of the action */
            if (action > 0) {
                /* Shift the symbol onto the stack */
                stack[++top] = symbol;
                stack[++top] = action;
                symbol = input[++index];
            } else if (action < 0) {
                /* Reduce by production */
                int production = -action;
                int length = grammar[production - 1].length;

                /* Pop the stack based on the length of the production */
                while (length-- > 0) {
                    top -= 2;
                }

                /* Determine the non-terminal to push onto the stack */
                int non_terminal = productions[production - 1].non_terminal;
                int next_state = parsing_table[stack[top - 1] - 1][non_terminal - 1];

                /* Push the non-terminal onto the stack */
                stack[++top] = non_terminal;
                stack[++top] = next_state;
            } else {
                /* Error occurred */
                printf("Error: Invalid input string\n");
                break;
            }
        }
    }

    if (stack_t[1] == 1 && index == len) {
        printf("Input string successfully parsed!\n");
    } else {
        printf("Error: Invalid input string\n");
    }

    return 0;
}
