#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
//#include "../include/node.h"
#include "../include/imagelib.h"

typedef struct
{
    int freq;
    int father;
    int left;
    int right;
} nodetype;

int pqmindelete(int *rootnodes);
int pqinsert(int *rootnodes, int i);
void shownodes(int root, int n);
int buildTree(int *h, int mn);
void reverse(char *str);
void code(int n, int p, char *str);
void drawLinks(FILE *dot, int root);
void createDot(int root);
void displayCalcs(int *h, int n);
void huf_tree(int *h, int mn, int dot);

void decodeHuffmanImage(FILE *fp, Image *img, HuffmanNode *root, int totalPixels);

#endif
