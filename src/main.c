/*=============================================================
*           UNIFAL - Universidade Federal de Alfenas.
*             BACHARELADO EM CIENCIA DA COMPUTACAO.
* Trabalho .  : Decodificador do formato PGH
* Professor . : Luiz Eduardo da Silva
* Aluno . . . : Lucas Hideki Okido
* Data . . .  : 11/06/2025
*=============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int width;
    int height;
    int maxVal;
    unsigned char* data;
} PghImage;

PghImage* readPghFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    char header[256];
    if (!fgets(header, sizeof(header), file)) {
        perror("Erro ao ler cabeçalho");
        fclose(file);
        return NULL;
    }

    if (strncmp(header, "PH#", 3) != 0) {
        fprintf(stderr, "Formato inválido\n");
        fclose(file);
        return NULL;
    }

    // Ignorar a próxima linha (criador)
    fgets(header, sizeof(header), file);

    int width, height, maxVal;
    fscanf(file, "%d %d\n%d\n", &width, &height, &maxVal);

    // Pular os zeros (padding)
    fseek(file, 256, SEEK_SET);

    size_t dataSize = width * height;
    unsigned char* data = malloc(dataSize);
    if (!data) {
        perror("Erro ao alocar memória");
        fclose(file);
        return NULL;
    }

    if (fread(data, 1, dataSize, file) != dataSize) {
        perror("Erro ao ler dados da imagem");
        free(data);
        fclose(file);
        return NULL;
    }

    fclose(file);

    PghImage* image = malloc(sizeof(PghImage));
    image->width = width;
    image->height = height;
    image->maxVal = maxVal;
    image->data = data;

    return image;
}

void freePghImage(PghImage* img) {
    if (img) {
        free(img->data);
        free(img);
    }
}


/*
 * Image Processing using C-Ansi
 * Program: decoding files in PGH format
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/imagelib.h"
#include "../include/huffman.h"
#include "../include/node.h"

void msg(char *s) {
    printf("\nDecoding files in PGH format");
    printf("\n-------------------------------------");
    printf("\nUsage: %s image-name[.pgh]\n\n", s);
    printf("       image-name[.pgh] is image file in pgh format\n\n");
    exit(1);
}

/*
 * Main function
 */
int main(int argc, char *argv[]) {
    char nameIn[100], nameOut[100], cmd[110];
    image In;

    if (argc < 2)
        msg(argv[0]);

    // Define input/output file name
    img.name(argv[1], nameIn, nameOut, PGH, GRAY);

    // Read image in PGH format
    In = read.pgh(nameIn);

    // Save image as PGM
    img.put(In, nameOut, GRAY);

    // Show image using external viewer
    sprintf(cmd, "eog %s &", nameOut);
    puts(cmd);
    system(cmd);

    // Free image memory
    img.free(In);

    return 0;
}
