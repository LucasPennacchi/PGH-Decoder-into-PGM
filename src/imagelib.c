#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/imagelib.h"

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

    fgets(header, sizeof(header), file);

    int width, height, maxVal;
    if (fscanf(file, "%d %d\n%d\n", &width, &height, &maxVal) != 3) {
        fprintf(stderr, "Erro na leitura das dimensões ou valor máximo\n");
        fclose(file);
        return NULL;
    }

    if (fseek(file, 256, SEEK_SET) != 0) {
        perror("Erro ao posicionar cursor no arquivo");
        fclose(file);
        return NULL;
    }

    size_t dataSize = (size_t)width * height;
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
    if (!image) {
        perror("Erro ao alocar memória para estrutura de imagem");
        free(data);
        return NULL;
    }
    image->width = width;
    image->height = height;
    image->maxVal = maxVal;
    image->data = data;

    return image;
}

void writePgmFile(const char* filename, PghImage* img) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Erro ao salvar arquivo PGM");
        return;
    }

    fprintf(file, "P5\n%d %d\n%d\n", img->width, img->height, img->maxVal);
    fwrite(img->data, 1, (size_t)img->width * img->height, file);
    fclose(file);
}

void freePghImage(PghImage* img) {
    if (img) {
        free(img->data);
        free(img);
    }
}

int* makeHistogram(PghImage* img) {
    int size = img->maxVal + 1;
    
    int *histogram = (int*) calloc(size, sizeof(int));
    if (!histogram) {
        fprintf(stderr, "Erro ao alocar memória para histograma\n");
        return NULL;
    }
    int totalPixels = img->width * img->height;
    for (int i = 0; i < totalPixels; i++) {
        unsigned char gray = img->data[i];
        histogram[gray]++;
    }

    return histogram;
}
