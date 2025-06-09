#include <stdlib.h>
#include "node.h"

Node* createNode(unsigned char value, int frequency) {
    Node* node = (Node*) malloc(sizeof(Node));
    if (!node) return NULL;
    node->value = value;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* createInternalNode(Node* left, Node* right) {
    if (!left || !right) return NULL;
    Node* node = (Node*) malloc(sizeof(Node));
    if (!node) return NULL;
    node->frequency = left->frequency + right->frequency;
    node->left = left;
    node->right = right;
    node->value = 0; // valor arbitrário para nó interno
    return node;
}

void freeNode(Node* root) {
    if (!root) return;
    freeNode(root->left);
    freeNode(root->right);
    free(root);
}
