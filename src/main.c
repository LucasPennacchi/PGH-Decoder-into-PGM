#include "include/imagelib.h"
#include "include/huffman.h"
#include "include/node.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s arquivo.pgh\n", argv[0]);
        return 1;
    }

    // Descompactando
    PGHHeader header;
    int huffmanDataSize = 0;
    unsigned char* huffmanData = readPGH(argv[1], &header, &huffmanDataSize);
    if (!huffmanData) {
        fprintf(stderr, "Erro ao ler arquivo PGH.\n");
        return 1;
    }

    unsigned char* imageData; // dados da imagem
    int imageSize = header.width * header.height;

    // Criando histograma
    int histogram[256];
    generateHistogram(imageData, imageSize, histogram);
    // Criando arvore de huffman
    Node* root = buildHuffmanTree(histogram);
    // Descompactando a arvore em dados
    unsigned char* decompressed = decompressData(huffmanData, huffmanDataSize, root, header.width * header.height);

    if (!decompressed) {
        fprintf(stderr, "Erro na descompressão\n");
        return 1;
    }

    // Salvar arquivo PGM com os dados
    if (!savePGM("saida.pgm", decompressed, &header)) {
        fprintf(stderr, "Erro ao salvar arquivo PGM\n");
    } else {
        printf("Arquivo PGM salvo com sucesso!\n");
    }

    // Liberando memoria
    free(decompressed);
    freeTree(root);
    free(huffmanData);
    free(imageData);

    return 0;
}
