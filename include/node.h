#ifndef NODE_H
#define NODE_H

typedef struct node {
    int value;
    int freq;
    struct node *left, *right;
} Node;

Node* createNode(int value, int freq, Node* left, Node* right);
void freeTree(Node* root);

#endif
