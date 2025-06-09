#ifndef NODE_H
#define NODE_H

typedef struct
{
    int freq;
    int father;
    int left;
    int right;
} nodetype;

nodetype* createNode(unsigned char symbol, int freq);
void freeTree(nodetype* root);

#endif
