//WORKS!!
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    NODE_TYPE_ADDITION,
    NODE_TYPE_SUBTRACTION,
    NODE_TYPE_MULTIPLICATION,
    NODE_TYPE_DIVISION,
    NODE_TYPE_NUMBER,
    NODE_TYPE_VARIABLE
} ast_node_type_t;

typedef struct ast_node {
    ast_node_type_t type;
    int value;
    char* name;
    struct ast_node* left;
    struct ast_node* right;
} ast_node_t;

ast_node_t* create_number_node(int value);
ast_node_t* create_variable_node(char* name);
ast_node_t* create_addition_node(ast_node_t* left, ast_node_t* right);
ast_node_t* create_subtraction_node(ast_node_t* left, ast_node_t* right);
ast_node_t* create_multiplication_node(ast_node_t* left, ast_node_t* right);
ast_node_t* create_division_node(ast_node_t* left, ast_node_t* right);
void free_ast_node(ast_node_t* node);


ast_node_t* parse_expression(char* expression);
ast_node_t* create_number_node(int value) {
    ast_node_t* node = (ast_node_t*) malloc(sizeof(ast_node_t));
    node->type = NODE_TYPE_NUMBER;
    node->value = value;
    node->name = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

ast_node_t* create_variable_node(char* name) {
    ast_node_t* node = (ast_node_t*) malloc(sizeof(ast_node_t));
    node->type = NODE_TYPE_VARIABLE;
    node->value = 0;
    node->name = strdup(name);
    node->left = NULL;
    node->right = NULL;
    return node;
}

ast_node_t* create_addition_node(ast_node_t* left, ast_node_t* right) {
    ast_node_t* node = (ast_node_t*) malloc(sizeof(ast_node_t));
    node->type = NODE_TYPE_ADDITION;
    node->value = 0;
    node->name = NULL;
    node->left = left;
    node->right = right;
    return node;
}

ast_node_t* create_subtraction_node(ast_node_t* left, ast_node_t* right) {
    ast_node_t* node = (ast_node_t*) malloc(sizeof(ast_node_t));
    node->type = NODE_TYPE_SUBTRACTION;
    node->value = 0;
    node->name = NULL;
    node->left = left;
    node->right = right;
    return node;
}

ast_node_t* create_multiplication_node(ast_node_t* left, ast_node_t* right) {
    ast_node_t* node = (ast_node_t*) malloc(sizeof(ast_node_t));
    node->type = NODE_TYPE_MULTIPLICATION;
    node->value = 0;
    node->name = NULL;
    node->left = left;
    node->right = right;
    return node;
}

ast_node_t* create_division_node(ast_node_t* left, ast_node_t* right) {
    ast_node_t* node = (ast_node_t*) malloc(sizeof(ast_node_t));
    node->type = NODE_TYPE_DIVISION;
    node->value = 0;
    node->name = NULL;
    node->left = left;
    node->right = right;
    return node;
}

void free_ast_node(ast_node_t* node) {
    if (node == NULL) {
        return;
    }
    free(node->name);
    free_ast_node(node->left);
    free_ast_node(node->right);
    free(node);
}

void print_ast_node(ast_node_t* node, int indent) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < indent; i++) {
        printf("  ");
    }

    switch (node->type) {
        case NODE_TYPE_ADDITION:
            printf("Addition:\n");
            print_ast_node(node->left, indent+1);
            print_ast_node(node->right, indent+1);
            break;
        case NODE_TYPE_SUBTRACTION:
            printf("Subtraction:\n");
            print_ast_node(node->left, indent+1);
            print_ast_node(node->right, indent+1);
            break;
        case NODE_TYPE_MULTIPLICATION:
            printf("Multiplication:\n");
            print_ast_node(node->left, indent+1);
            print_ast_node(node->right, indent+1);
            break;
        case NODE_TYPE_DIVISION:
            printf("Division:\n");
            print_ast_node(node->left, indent+1);
            print_ast_node(node->right, indent+1);
            break;
        case NODE_TYPE_NUMBER:
            printf("Number: %d\n", node->value);
            break;
        case NODE_TYPE_VARIABLE:
            printf("Variable: %s\n", node->name);
            break;
        default:
            printf("Unknown node type\n");
            break;
    }
}

int main() {
    ast_node_t* expression_node = parse_expression("3 * x + 5");
    printf("Syntax Tree for expression:\n");
    print_ast_node(expression_node, 0);
    free_ast_node(expression_node);
    return 0;
}

ast_node_t* parse_expression(char* expression) {
    // TODO: Implement expression parsing logic
    // For this example, we'll just hardcode the syntax tree
    ast_node_t* three_node = create_number_node(3);
    ast_node_t* x_node = create_variable_node("x");
    ast_node_t* five_node = create_number_node(5);
    ast_node_t* product_node = create_multiplication_node(three_node, x_node);
    ast_node_t* sum_node = create_addition_node(product_node, five_node);
    return sum_node;
}
