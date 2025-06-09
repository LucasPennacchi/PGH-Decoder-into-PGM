#include "include/node.h"
#include <stdlib.h>

Node* createNode(unsigned char symbol, int freq) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) return NULL;
    node->symbol = symbol;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
