#ifndef IMAGELIB_H
#define IMAGELIB_H

typedef struct {
    char magic[4];  // "PGH" + null terminator
    int width;
    int height;
    int maxGray;
    int* histogram;
    unsigned char* huffmanData;
} image;

void img_name(argv[1], char* nameIn, char* nameOut, PGH, GRAY);
image readpgh(char* nameIn);
image img_put(image In,char* nameOut, GRAY);
void imgfree(image In);

#endif
