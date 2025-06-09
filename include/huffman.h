#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "node.h"

void generateHistogram(const unsigned char* data, int dataSize, int* histogram);
Node* buildHuffmanTree(int* histogram);
unsigned char* decompressData(const unsigned char* compressedData, int compressedSize, Node* root, int outputSize);

#endif
