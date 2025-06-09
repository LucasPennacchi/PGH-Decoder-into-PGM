#ifndef IMAGELIB_H
#define IMAGELIB_H

typedef struct {
    char magic[4];  // "PGH" + null terminator
    int width;
    int height;
    int maxGray;
} PGHHeader;

/**
 * Lê o cabeçalho e os dados comprimidos de um arquivo .pgh.
 * - `filename`: caminho para o arquivo.
 * - `header`: struct onde será salvo o cabeçalho.
 * - `huffmanDataSize`: recebe o tamanho em bytes dos dados de Huffman.
 * Retorna um ponteiro para os dados comprimidos.
 */
unsigned char* readPGH(const char* filename, PGHHeader* header, int* huffmanDataSize);
int savePGM(const char* filename, const unsigned char* imageData, const PGHHeader* header);

#endif
