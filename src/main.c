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
#include "include/imagelib.h"
#include "include/huffman.h"
#include "include/node.h"

/*
* Ler PGH
*     -> PH, Largura, Altura, Histograma e Código de Huffman
* 
* Fazer a árvore de huffman com o histograma
*     -> descompactar huffman para dados da imagem
* 
* Com dados da imagem e o cabecalho do PGH, fazer o PGM
*     -> abrir o PGM
* 
* Liberar memória
* 
* Fim
* = = = = = = = = = = = = = = = = = = = = = = = = =
* huffman.h -> possui o arquivo de huffman feito pelo professor
* node.h -> possui a struct da arvore
* imagelib.h -> possui função de ler PGH e escrever PGM
* main.c -> realiza o código de decodificar PGH para PGM
*/

/*=========================================================================
* Image Processing using C=Ansi
* Program : decoding files in PGH format
*=========================================================================*/


void msg (char* s)
{
    printf("Edecoding files in PGH format\n");
    printf("===============================\n");
    printf("Usage : %s image=name [.pgh]\n", s);
    printf("\n\timage=name [.pgh] is image file in pgh format\n\n");
    exit(1);
}
/*=========================================================================
* main function
*=========================================================================*/
int main (int argc, char* argv[])
{
char nameIn[100], nameOut[100], cmd[110];
image In;
if (argc < 2)
    msg (argv[0]);

// define input/output file name
img_name(argv[1], nameIn, nameOut, PGH, GRAY);

// read image PGH
In = readpgh(nameIn);

// save image PGM
img_put(In, nameOut, GRAY);

// show image
sprintf(cmd, "eog %s &", nameOut);
puts(cmd);
system(cmd);
imgfree(In);
return 0;

}
