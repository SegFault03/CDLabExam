//WORKS??!! NOT FULLY
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    NODE_TYPE_DECLARATION,
    NODE_TYPE_IDENTIFIER,
    NODE_TYPE_TYPE_SPECIFIER,
    NODE_TYPE_FUNCTION_CALL,
    NODE_TYPE_STRING_LITERAL,
    NODE_TYPE_FORMAT_STRING,
    NODE_TYPE_ARGUMENT_LIST,
} node_type_t;

typedef struct ast_node {
    node_type_t type;
    char* value;
    struct ast_node* left;
    struct ast_node* right;
} ast_node_t;

ast_node_t* create_ast_node(node_type_t type, char* value, ast_node_t* left, ast_node_t* right) {
    ast_node_t* node = malloc(sizeof(ast_node_t));
    node->type = type;
    node->value = strdup(value);
    node->left = left;
    node->right = right;
    return node;
}

void free_ast_node(ast_node_t* node) {
    if (node->left) {
        free_ast_node(node->left);
    }
    if (node->right) {
        free_ast_node(node->right);
    }
    free(node->value);
    free(node);
}

ast_node_t* parse_declaration(char* declaration) {
    // parse declaration string and return syntax tree
    // (not implemented here for brevity)
    // the following is an example syntax tree for a declaration:
    ast_node_t* identifier_node = create_ast_node(NODE_TYPE_IDENTIFIER, "x", NULL, NULL);
    ast_node_t* type_node = create_ast_node(NODE_TYPE_TYPE_SPECIFIER, "int", NULL, NULL);
    return create_ast_node(NODE_TYPE_DECLARATION, NULL, type_node, identifier_node);
}

ast_node_t* parse_function_call(char* function_name, ast_node_t* argument_list) {
    return create_ast_node(NODE_TYPE_FUNCTION_CALL, function_name, argument_list, NULL);
}

ast_node_t* parse_string_literal(char* value) {
    return create_ast_node(NODE_TYPE_STRING_LITERAL, value, NULL, NULL);
}

ast_node_t* parse_format_string(char* format_string, ast_node_t* argument_list) {
    return create_ast_node(NODE_TYPE_FORMAT_STRING, format_string, argument_list, NULL);
}

ast_node_t* parse_argument_list(ast_node_t* argument, ast_node_t* next_argument) {
    return create_ast_node(NODE_TYPE_ARGUMENT_LIST, NULL, argument, next_argument);
}

void print_ast_node(ast_node_t* node, int indent) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
    switch (node->type) {
        case NODE_TYPE_DECLARATION:
            printf("Declaration:\n");
            print_ast_node(node->left, indent+1);
            print_ast_node(node->right, indent+1);
            break;
        case NODE_TYPE_IDENTIFIER:
            printf("Identifier: %s\n", node->value);
            break;
        case NODE_TYPE_TYPE_SPECIFIER:
            printf("Type Specifier: %s\n", node->value);
            break;
        case NODE_TYPE_FUNCTION_CALL:
            printf("Function Call: %s\n", node->value);
            print_ast_node(node->left, indent+1);
            break;
        case NODE_TYPE_STRING_LITERAL:
            printf("String Literal: \"%s\"\n", node->value);
            break;
        case NODE_TYPE_FORMAT_STRING:
            printf("Format String: \"%s");
            print_ast_node(node->left, indent+1);
            break;
        case NODE_TYPE_ARGUMENT_LIST:
            printf("Argument List:\n");
            print_ast_node(node->left, indent+1);
            print_ast_node(node->right, indent+1);
            break;
        default:
            printf("Unknown node type\n");
    }
}

int main() {
    // example program with printf and scanf statements
    ast_node_t* format_string_node = parse_string_literal("Hello, %s!\n");
    ast_node_t* string_argument_node = parse_string_literal("world");
    ast_node_t* argument_list_node = parse_argument_list(string_argument_node, NULL);
    ast_node_t* printf_call_node = parse_function_call("printf", argument_list_node);
    ast_node_t* printf_statement_node = create_ast_node(NODE_TYPE_FORMAT_STRING, NULL, format_string_node, printf_call_node);

    ast_node_t* scanf_format_node = parse_string_literal("%d");
    ast_node_t* scanf_argument_node = parse_declaration("int x;");
    ast_node_t* scanf_call_node = parse_function_call("scanf", parse_argument_list(scanf_format_node, scanf_argument_node));
    ast_node_t* scanf_statement_node = create_ast_node(NODE_TYPE_FUNCTION_CALL, NULL, scanf_call_node, NULL);

    ast_node_t* program_node = create_ast_node(NODE_TYPE_ARGUMENT_LIST, NULL, printf_statement_node, scanf_statement_node);
    print_ast_node(program_node, 0);
    free_ast_node(program_node);
    return 0;
}
