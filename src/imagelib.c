#include "include/imagelib.h"
#include <stdlib.h>
#include <string.h>

unsigned char* readPGH(const char* filename, PGHHeader* header, int* huffmanDataSize) {
    FILE* f = fopen(filename, "rb");
    if (!f) {
        perror("Erro ao abrir arquivo PGH");
        return NULL;
    }

    // Lê magic number
    fread(header->magic, sizeof(char), 3, f);
    header->magic[3] = '\0';

    // Verifica se é PGH
    if (strcmp(header->magic, "PGH") != 0) {
        fprintf(stderr, "Formato inválido: esperado 'PGH', encontrado '%s'\n", header->magic);
        fclose(f);
        return NULL;
    }

    // Lê demais campos
    fread(&header->width, sizeof(int), 1, f);
    fread(&header->height, sizeof(int), 1, f);
    fread(&header->maxGray, sizeof(int), 1, f);

    // Lê tamanho dos dados Huffman
    fread(huffmanDataSize, sizeof(int), 1, f);

    // Aloca buffer e lê os dados
    unsigned char* huffmanData = malloc(*huffmanDataSize);
    if (!huffmanData) {
        perror("Erro ao alocar memória para dados Huffman");
        fclose(f);
        return NULL;
    }

    fread(huffmanData, sizeof(unsigned char), *huffmanDataSize, f);
    fclose(f);

    return huffmanData;
}

int savePGM(const char* filename, const unsigned char* imageData, const PGHHeader* header) {
    FILE* f = fopen(filename, "wb");
    if (!f) return 0;

    // Cabeçalho PGM
    fprintf(f, "P5\n%u %u\n%u\n", header->width, header->height, header->maxGray);

    // Dados da imagem
    size_t dataSize = header->width * header->height;
    if (fwrite(imageData, 1, dataSize, f) != dataSize) {
        fclose(f);
        return 0;
    }

    fclose(f);
    return 1;
}