#include <stdlib.h>
#include "include/node.h"

Node* createNode(int value, int freq, Node* left, Node* right) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->freq = freq;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
