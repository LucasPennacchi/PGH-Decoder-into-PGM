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

img_name(argv[1], char* nameIn, char* nameOut, PGH, GRAY);
readpgh(char* nameIn);
img_put(image In,char* nameOut, GRAY);
imgfree(image In);

#endif
