#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "node.h"

static int compare(const void* a, const void* b) {
    Node* n1 = *(Node**)a;
    Node* n2 = *(Node**)b;
    return n1->freq - n2->freq;
}

static void printTree(Node* root, int depth) {
    if (!root) return;

    if (!root->left && !root->right)
        printf("%*s[%d]\n", depth * 2, "", root->value);
    else
        printf("%*s*\n", depth * 2, "");

    printTree(root->left, depth + 1);
    printTree(root->right, depth + 1);
}

void hufTree(int *histogram, int size, int print) {
    Node** nodes = (Node**)malloc(size * sizeof(Node*));
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (histogram[i] > 0) {
            nodes[count++] = createNode(i, histogram[i], NULL, NULL);
        }
    }

    while (count > 1) {
        qsort(nodes, count, sizeof(Node*), compare);
        Node* left = nodes[0];
        Node* right = nodes[1];

        Node* parent = createNode(-1, left->freq + right->freq, left, right);

        nodes[0] = parent;
        for (int i = 2; i < count; i++)
            nodes[i - 1] = nodes[i];
        count--;
    }

    if (print && count == 1)
        printTree(nodes[0], 0);

    if (count == 1)
        freeTree(nodes[0]);
    free(nodes);
}
