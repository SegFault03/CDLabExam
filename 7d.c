//DOES NOT WORK!!!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    NODE_TYPE_IF,
    NODE_TYPE_WHILE,
    NODE_TYPE_CONDITION,
    NODE_TYPE_BLOCK
} ast_node_type_t;

typedef struct ast_node {
    ast_node_type_t type;
    char* name;
    struct ast_node* left;
    struct ast_node* right;
} ast_node_t;

ast_node_t* create_if_node(ast_node_t* condition, ast_node_t* if_branch, ast_node_t* else_branch) {
    ast_node_t* node = (ast_node_t*) malloc(sizeof(ast_node_t));
    node->type = NODE_TYPE_IF;
    node->name = NULL;
    node->left = condition;
    node->right = NULL;

    if (else_branch == NULL) {
        node->right = if_branch;
    } else {
        ast_node_t* block1 = (ast_node_t*) malloc(sizeof(ast_node_t));
        block1->type = NODE_TYPE_BLOCK;
        block1->name = NULL;
        block1->left = if_branch;
        block1->right = NULL;

        ast_node_t* block2 = (ast_node_t*) malloc(sizeof(ast_node_t));
        block2->type = NODE_TYPE_BLOCK;
        block2->name = NULL;
        block2->left = else_branch;
        block2->right = NULL;

        node->left = condition;
        node->right = (ast_node_t*) malloc(sizeof(ast_node_t));
        node->right->type = NODE_TYPE_CONDITION;
        node->right->name = NULL;
        node->right->left = block1;
        node->right->right = block2;
    }

    return node;
}

ast_node_t* create_while_node(ast_node_t* condition, ast_node_t* loop_body) {
    ast_node_t* node = (ast_node_t*) malloc(sizeof(ast_node_t));
    node->type = NODE_TYPE_WHILE;
    node->name = NULL;
    node->left = condition;
    node->right = loop_body;
    return node;
}

ast_node_t* create_block_node(ast_node_t* statement_list) {
    ast_node_t* node = (ast_node_t*) malloc(sizeof(ast_node_t));
    node->type = NODE_TYPE_BLOCK;
    node->name = NULL;
    node->left = statement_list;
    node->right = NULL;
    return node;
}

ast_node_t* create_condition_node(ast_node_t* condition) {
    ast_node_t* node = (ast_node_t*) malloc(sizeof(ast_node_t));
    node->type = NODE_TYPE_CONDITION;
    node->name = NULL;
    node->left = condition;
    node->right = NULL;
    return node;
}

void print_ast_node(ast_node_t* node, int level) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    switch (node->type) {
        case NODE_TYPE_IF:
            printf("if\n");
            print_ast_node(node->left, level + 1);
            if (node->right != NULL) {
                for (int i = 0; i < level; i++) {
                    printf("  ");
                }
                printf("else\n");
                print_ast_node(node->right, level + 1);
            }
            break;
        case NODE_TYPE_WHILE:
            printf("while\n");
            print_ast_node(node->left, level + 1);
            print_ast_node(node->right, level + 1);
            break;
        case NODE_TYPE_BLOCK:
            printf("block\n");
            print_ast_node(node->left, level + 1);
            break;
        case NODE_TYPE_CONDITION:
            printf("condition\n");
            print_ast_node(node->left, level + 1);
            print_ast_node(node->right->left, level + 1);
            print_ast_node(node->right->right, level + 1);
            break;
        default:
            printf("Unknown node type\n");
            break;
    }
}

int main() {
    // Example usage:
    ast_node_t* condition1 = create_condition_node((ast_node_t*) malloc(sizeof(ast_node_t)));
    condition1->type = NODE_TYPE_CONDITION;
    condition1->left = (ast_node_t*) malloc(sizeof(ast_node_t));
    condition1->left->name = strdup("x");
    condition1->left->type = NODE_TYPE_CONDITION;
    condition1->left->left = (ast_node_t*) malloc(sizeof(ast_node_t));
    condition1->left->left->name = strdup("10");
    condition1->left->left->type = NODE_TYPE_CONDITION;
    condition1->left->right = (ast_node_t*) malloc(sizeof(ast_node_t));
    condition1->left->right->name = strdup("20");
    condition1->left->right->type = NODE_TYPE_CONDITION;
    condition1->right = NULL;

    ast_node_t* if_branch = create_block_node((ast_node_t*) malloc(sizeof(ast_node_t)));
    if_branch->type = NODE_TYPE_BLOCK;
    if_branch->left = create_condition_node((ast_node_t*) malloc(sizeof(ast_node_t)));
    if_branch->left->type = NODE_TYPE_CONDITION;
    if_branch->left->left = (ast_node_t*) malloc(sizeof(ast_node_t));
    if_branch->left->left->name = strdup("y");
    if_branch->left->left->type = NODE_TYPE_CONDITION;
    if_branch->left->right = (ast_node_t*) malloc(sizeof(ast_node_t));
    if_branch->left->right->name = strdup("30");
    if_branch->left->right->type = NODE_TYPE_CONDITION;
    if_branch->right = NULL;

    ast_node_t* else_branch = create_block_node((ast_node_t*) malloc(sizeof(ast_node_t)));
    else_branch->type = NODE_TYPE_BLOCK;
    else_branch->left = create_condition_node((ast_node_t*) malloc(sizeof(ast_node_t)));
    else_branch->left->type = NODE_TYPE_CONDITION;
    else_branch->left->left = (ast_node_t*) malloc(sizeof(ast_node_t));
    else_branch->left->left->name = strdup("z");
    else_branch->left->left->type = NODE_TYPE_CONDITION;
    else_branch->left->right = (ast_node_t*) malloc(sizeof(ast_node_t));
    else_branch->left->right->name = strdup("40");
    else_branch->left->right->type = NODE_TYPE_CONDITION;
    else_branch->right = NULL;

    ast_node_t* if_node = create_if_node(condition1, if_branch, else_branch);

    ast_node_t* condition2 = create_condition_node((ast_node_t*) malloc(sizeof(ast_node_t)));
    condition2->type = NODE_TYPE_CONDITION;
    condition2->left = (ast_node_t*) malloc(sizeof(ast_node_t));
    condition2->left->name = strdup("y");
    condition2->left->type = NODE_TYPE_CONDITION;
    condition2->right = NULL;

    ast_node_t* loop_body = create_block_node((ast_node_t*) malloc(sizeof(ast_node_t)));
    loop_body->type = NODE_TYPE_BLOCK;
    loop_body->left = create_declaration_node("int", "i");
    loop_body->right = create_assignment_node(create_variable_node("i"), create_literal_node("0"));
    ast_node_t* loop_node = create_while_node(condition2, loop_body);

    ast_node_t* root = create_block_node((ast_node_t*) malloc(sizeof(ast_node_t)));
    root->type = NODE_TYPE_BLOCK;
    root->left = if_node;
    root->right = loop_node;

    print_ast_node(root, 0);

    // Clean up
    free_ast_node(root);
    free(condition1->left->left);
    free(condition1->left->right);
    free(condition1->left);
    free(condition1);
    free(if_branch->left->left);
    free(if_branch->left->right);
    free(if_branch->left);
    free(if_branch);
    free(else_branch->left->left);
    free(else_branch->left->right);
    free(else_branch->left);
    free(else_branch);
    free(condition2->left);
    free(condition2);
    free(loop_body);
    free(loop_node);

    return 0;
}
