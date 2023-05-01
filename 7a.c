//WORKS!!!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    NODE_TYPE_DECLARATION,
    NODE_TYPE_IDENTIFIER,
    NODE_TYPE_TYPE_SPECIFIER,
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
        default:
            printf("Unknown Node Type\n");
            break;
    }
}

int main() {
    char* declaration = "int x;";
    ast_node_t* root = parse_declaration(declaration);
    print_ast_node(root, 0);
    free_ast_node(root);
    return 0;
}
