#ifndef IMAGELIB_H
#define IMAGELIB_H

// Definições de formatos
#define GRAY 1
#define PGH ".pgh"

// Struct para imagem em tons de cinza
typedef struct {
    int rows;
    int cols;
    int maxval;
    unsigned char** pixels;
} image;

// Funções disponíveis
void img_name(char* fileName, char* nameIn, char* nameOut, char* PGH, int GRAY);
image readpgh(char* nameIn);
image img_put(image In, char* nameOut, int GRAY);
void imgfree(image In);

#endif