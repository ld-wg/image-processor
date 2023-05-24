#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "filtros.h"

int main(int argc, char *argv[])
{
   FILE *imagein, *imageout;

  // Aloca estrutura imginfo
  struct PGMstructure *imginfo = malloc(sizeof(struct PGMstructure));
  unsigned char **mat; // matrix 

  char *infpath, *outfpath;
  infpath = malloc(sizeof(char) * 500); // input file name
  outfpath = malloc(sizeof(char) * 500); // output file name

  // control variables
  int format;
  int i;
  int mode;
  int mediana;
  float limiar;
  
  //read command line
  if (argc > 1) {
      int c = 0;
      while(++c < argc) {
          if (strcmp(argv[c], "-i") == 0) {
          	  infpath = argv[c+1];
              c++;
          }
          else if (strcmp(argv[c], "-o") == 0) {
              outfpath = argv[c+1];		  	 
              c++;
          }
          else {
            printf("ERROR");
            exit(1);
          }
      }
  }

  // Abre arquivo de entrada e armazena em imagein
  imagein = fopen(infpath, "r+");
  
  if (imagein == NULL)
  {
    printf("Error opening file");
    exit(8);
  }

  format = getImageFormat(imagein); // read format p5 or p2
  processComment(imagein); // ignore comments
  printMenu(&mode); // print menu
  getImageValues(imagein, imginfo); // read image dimensions
  mat = alocamatriz(imginfo); // alloc matrix
  copyPixels(imagein, imginfo, mat, format); // copy image to matrix
  imageout = fopen(outfpath, "w+"); // open output file
  printImageHeader(imageout, imginfo, format, mode); // print image header

// FILTROS

  switch(mode) {
  	case 1:
  		Negativo(&imageout, imginfo, mat, format);
  		break;
	case 2:
    	printf("\nLimiar: ");
    	scanf("%f", &limiar);
    	
		  Limiar(&imageout, imginfo, mat, format, limiar);
		  break;
	case 3:
		  Ruido(&imageout, imginfo, mat, format);
		  break;
	case 4:
		  printf("\nMediana: ");
    	scanf("%i", &mediana);
    	Mediana(&imageout, imginfo, mat, format, mediana);
    	break;
    case 5:
    	Lbp(&imageout, imginfo, mat, format);
    	break;
    case 6:
    	Rota90(&imageout, imginfo, mat, format);
		break;
  }

  // free

  fclose(imagein);
  fclose(imageout);
  free(imginfo);
  for (i = 0; i < imginfo->width; i++)
    free(mat[i]);
  free(mat);

  return 0;
}