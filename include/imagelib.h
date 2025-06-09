#ifndef IMAGELIB_H
#define IMAGELIB_H

typedef struct {
    int width;
    int height;
    int maxVal;
    unsigned char* data;
} PghImage;

PghImage* readPghFile(const char* filename);
void writePgmFile(const char* filename, PghImage* img);
void freePghImage(PghImage* img);
int* makeHistogram(PghImage* img);

#endif // IMAGELIB_H
