#ifndef NODE_H
#define NODE_H

typedef struct Node {
    unsigned char symbol;
    int freq;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(unsigned char symbol, int freq);
void freeTree(Node* root);

#endif
