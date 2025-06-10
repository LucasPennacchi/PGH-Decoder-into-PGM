#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/imagelib.h"
//#include "../include/node.h"
#include "../include/huffman.h"


/*-------------------------------------------------------------------------
 * Define input and output image name
 * Params:
 *   name = image name file
 *   in = input image name
 *   out = output image name
 *   tpIn, tpOut = image type (BW, GRAY, COLOR)
 *-------------------------------------------------------------------------*/
void img_name(char *name, char *in, char *out, int tpIn, int tpOut)
{
    char *ext[3] = {".pbm", ".pgm", ".ppm"};
    char *p = strstr(name, ext[tpIn - 1]);
    if (p)
        *p = 0;
    sprintf(in, "%s%s", name, ext[tpIn - 1]);
    sprintf(out, "%s-result%s", name, ext[tpOut - 1]);
}

// Define os nomes dos arquivos de entrada (.pgh) e saída (.pgm)
//void img_name(char* fileName, char* nameIn, char* nameOut, char* PGH, int GRAY) {
//    strcpy(nameIn, fileName);
//    if (strstr(nameIn, PGH) == NULL)
//        strcat(nameIn, PGH);
//
//    strcpy(nameOut, fileName);
//    if (strstr(nameOut, PGH) != NULL)
//        *strstr(nameOut, PGH) = '\0';
//    strcat(nameOut, GRAY == 1 ? ".pgm" : ".ppm"); // aqui só tratamos GRAY mesmo
//}

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
    decodeHuffmanImage(fp, &img, node, totalPixels);

    free(hist);
    fclose(fp);
    return img;
}

// Escreve imagem em formato .pgm
image img_put(image In, char* nameOut, int GRAY) {
    FILE* fp = fopen(nameOut, "wb");
    if (!fp) {
        fprintf(stderr, "Erro ao criar arquivo de saída: %s\n", nameOut);
        exit(1);
    }

    fprintf(fp, "P5\n%d %d\n%d\n", In.cols, In.rows, In.maxval);
    for (int i = 0; i < In.rows; i++) {
        fwrite(In.pixels[i], sizeof(unsigned char), In.cols, fp);
    }
    fclose(fp);
    return In;
}

// Libera a memória da imagem
void imgfree(image In) {
    for (int i = 0; i < In.rows; i++) {
        free(In.pixels[i]);
    }
    free(In.pixels);
}
