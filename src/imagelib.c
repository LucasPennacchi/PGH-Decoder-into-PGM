/*=============================================================
* UNIFAL = Universidade Federal de Alfenas.
* BACHARELADO EM CIENCIA DA COMPUTACAO.
* Trabalho . . : Decodificador do formato PGH
* Professor . : Luiz Eduardo da Silva
* Aluno . . . . . : Lucas Hideki Okido      2023.1.08.032
* Data . . . . . . : 11/06/2025
*=============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/imagelib.h"
#include "../include/huffman.h"


/**
 * O que foi alterado:
 * rigidez para o nome de entrada mostrar log do erro e não dar core dump
 */
void img_name(const char *name, char *in, char *out, int tpIn, int tpOut)
{
    char temp[256];
    const char *ext[3] = {".pgh", ".pgm", ".ppm"};

    // Safety check
    if (tpIn < 1 || tpIn > 3 || tpOut < 1 || tpOut > 3) {
        fprintf(stderr, "Invalid type index: tpIn=%d tpOut=%d\n", tpIn, tpOut);
        return;
    }

    strncpy(temp, name, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';

    char *p = strstr(temp, ext[tpIn - 1]);
    if (p != NULL) {
        *p = '\0'; // Safely terminate before extension
    }

    snprintf(in, 256, "%s%s", temp, ext[tpIn - 1]);
    snprintf(out, 256, "%s-result%s", temp, ext[tpOut - 1]);
}


// Lê o arquivo .pgh e reconstrói a imagem original decodificando com Huffman
image readpgh(char* nameIn) {
    FILE* fp = fopen(nameIn, "rb");
    if (!fp) {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", nameIn);
        exit(1);
    }

    char buffer[10];
    fgets(buffer, sizeof(buffer), fp);
    if (strncmp(buffer, "PH", 2) != 0) {
        fprintf(stderr, "Arquivo não é do tipo PGH.\n");
        fclose(fp);
        exit(1);
    }

    // Pula comentários
    int c;
    while ((c = fgetc(fp)) == '#') {
        while (fgetc(fp) != '\n'); // descarta a linha inteira
    }
    ungetc(c, fp);

    int cols, rows;
    fscanf(fp, "%d %d", &cols, &rows);
    int maxval;
    fscanf(fp, "%d", &maxval);
    fgetc(fp); // consome '\n' após maxval

    // Lê histograma
    int* hist = (int*)calloc(maxval + 1, sizeof(int));
    if (!hist) {
        fprintf(stderr, "Erro ao alocar memória para histograma.\n");
        exit(1);
    }
    fread(hist, sizeof(int), maxval + 1, fp);

    // Reconstrói árvore de Huffman
    int root = buildTree(hist, maxval);

    // Aloca imagem
    image img;
    img.rows = rows;
    img.cols = cols;
    img.maxval = maxval;
    img.pixels = (unsigned char**)malloc(rows * sizeof(unsigned char*));
    for (int i = 0; i < rows; i++) {
        img.pixels[i] = (unsigned char*)malloc(cols * sizeof(unsigned char));
    }

    // Decodifica imagem
    int totalPixels = rows * cols;

    decodeHuffmanImage(fp, &img, root);

    free(hist);
    fclose(fp);
    return img;
}

// Escreve imagem em formato .pgm
void img_put(image In, char* nameOut, int tpOut) {
    FILE* fp = fopen(nameOut, "w"); // usa "w" pois será texto
    if (!fp) {
        fprintf(stderr, "Erro ao criar arquivo de saída: %s\n", nameOut);
        exit(1);
    }

    fprintf(fp, "P2\n%d %d\n%d\n", In.cols, In.rows, In.maxval);
    for (int i = 0; i < In.rows; i++) {
        for (int j = 0; j < In.cols; j++) {
            fprintf(fp, "%d ", In.pixels[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}


// Libera a memória da imagem
void imgfree(image In) {
    for (int i = 0; i < In.rows; i++) {
        free(In.pixels[i]);
    }
    free(In.pixels);
}
