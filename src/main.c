#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imagelib.h"
#include "huffman.h"

#define PGH "pgh"
#define GRAY "pgm"

void msg(char *s) {
    printf("\nDecoding files in PGH format");
    printf("\n-------------------------------------");
    printf("\nUsage: %s image-name[.pgh]\n\n", s);
    printf("       image-name[.pgh] is image file in pgh format\n\n");
    exit(1);
}

void img_name(const char* original, char* nameIn, char* nameOut, const char* extIn, const char* extOut) {
    strncpy(nameIn, original, 100);
    nameIn[99] = '\0';

    char base[100];
    strncpy(base, original, 100);
    base[99] = '\0';
    char* dot = strrchr(base, '.');
    if (dot) {
        *dot = '\0';
    }

    snprintf(nameOut, 100, "%s.%s", base, extOut);
}

int main(int argc, char *argv[]) {
    
    char nameIn[100], nameOut[100], cmd[110];

    if (argc < 2)
        msg(argv[0]);

    img_name(argv[1], nameIn, nameOut, PGH, GRAY);

    PghImage* img = readPghFile(nameIn);
    if (!img) {
        fprintf(stderr, "Erro ao decodificar imagem.\n");
        return 1;
    }

    int *histogram = makeHistogram(img);
    if (!histogram) {
        freePghImage(img);
        return 1;
    }

    printf("Histograma:\n");
    for (int i = 0; i <= img->maxVal; i++) {
        printf("Nível %d: %d\n", i, histogram[i]);
    }

    hufTree(histogram, img->maxVal + 1, 1);

    writePgmFile(nameOut, img);

    snprintf(cmd, sizeof(cmd), "eog %s &", nameOut);
    puts(cmd);
    system(cmd);

    free(histogram);
    freePghImage(img);
    return 0;
}
