#include "include/huffman.h"
// #include "include/node.h" ja incluso no huffman.h
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 256

typedef struct {
    Node* nodes[MAX_SYMBOLS];
    int size;
} MinHeap;

static void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->nodes[left]->freq < heap->nodes[smallest]->freq)
        smallest = left;
    if (right < heap->size && heap->nodes[right]->freq < heap->nodes[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        Node* temp = heap->nodes[smallest];
        heap->nodes[smallest] = heap->nodes[idx];
        heap->nodes[idx] = temp;
        minHeapify(heap, smallest);
    }
}

static Node* extractMin(MinHeap* heap) {
    if (heap->size == 0) return NULL;
    Node* root = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return root;
}

static void insertHeap(MinHeap* heap, Node* node) {
    heap->size++;
    int i = heap->size - 1;

    while (i && node->freq < heap->nodes[(i - 1) / 2]->freq) {
        heap->nodes[i] = heap->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->nodes[i] = node;
}

static MinHeap* createAndBuildMinHeap(int* histogram) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = 0;

    for (int i = 0; i < MAX_SYMBOLS; i++) {
        if (histogram[i] > 0) {
            heap->nodes[heap->size++] = createNode((unsigned char)i, histogram[i]);
        }
    }

    for (int i = (heap->size - 1) / 2; i >= 0; i--) {
        minHeapify(heap, i);
    }

    return heap;
}

void generateHistogram(const unsigned char* data, int dataSize, int* histogram) {
    memset(histogram, 0, sizeof(int) * MAX_SYMBOLS);
    for (int i = 0; i < dataSize; i++) {
        histogram[data[i]]++;
    }
}

Node* buildHuffmanTree(int* histogram) {
    MinHeap* heap = createAndBuildMinHeap(histogram);
    if (!heap) return NULL;

    while (heap->size > 1) {
        Node* left = extractMin(heap);
        Node* right = extractMin(heap);

        Node* parent = createNode(0, left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        insertHeap(heap, parent);
    }

    Node* root = NULL;
    if (heap->size == 1) {
        root = extractMin(heap);
    }
    free(heap);
    return root;
}


// Função para ler um bit do buffer (bits da esquerda para a direita, por exemplo)
static int getBit(const unsigned char* data, int bitIndex) {
    int byteIndex = bitIndex / 8;
    int bitOffset = 7 - (bitIndex % 8); // Lendo do bit mais significativo para o menos
    return (data[byteIndex] >> bitOffset) & 1;
}

// Descompacta dados Huffman
unsigned char* decompressData(const unsigned char* compressedData, int compressedSize, Node* root, int outputSize) {
    unsigned char* output = (unsigned char*)malloc(outputSize);
    if (!output) return NULL;

    int bitIndex = 0;
    int outIndex = 0;
    Node* current = root;

    while (outIndex < outputSize) {
        int bit = getBit(compressedData, bitIndex++);
        if (bit == 0) {
            current = current->left;
        } else {
            current = current->right;
        }

        // Se chegou em uma folha
        if (current->left == NULL && current->right == NULL) {
            output[outIndex++] = current->symbol;
            current = root;
        }

        // Segurança: se passar do fim dos bits antes de completar a saída, quebra o loop
        if (bitIndex > compressedSize * 8) break;
    }

    return output;
}