#ifndef IMAGELIB_H
#define IMAGELIB_H

// Definições de formatos
#define GRAY 2
#define PGH 1

// Struct para imagem em tons de cinza
typedef struct {
    int rows;
    int cols;
    int maxval;
    unsigned char** pixels;
} image;

// Funções disponíveis
void img_name(const char *name, char *in, char *out, int tpIn, int tpOut);
image readpgh(char* nameIn);
void img_put(image In, char* nameOut, int tpOut);
void imgfree(image In);

#endif