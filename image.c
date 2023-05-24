#include "image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char **alocamatriz(struct PGMstructure *imginfo) 
{
  unsigned char **mat;
  int i;
  mat = malloc(imginfo->height * sizeof(unsigned char *));

  for (i = 0; i < imginfo->height; i++)
    mat[i] = malloc(imginfo->width * sizeof(unsigned char));

  return mat;
}

void copyPixels(FILE *imagein, struct PGMstructure *imginfo, unsigned char **mat, int format) {
  int i, j;
  if (format == 5)
  {
    for (i = 0; i < imginfo->height; i++)
    {
      for (j = 0; j < imginfo->width; j++)
      {
        mat[i][j] = getc(imagein);
      }
    }
  }

  if (format == 2)
  {
    int value;
    for (i = 0; i < imginfo->height; i++)
    {
      for (j = 0; j < imginfo->width; j++)
      {
        fscanf(imagein, "%d", &value);
        mat[i][j] = (unsigned char)value;
      }
    }
  }
}

void printMenu(int *mode) {
  printf("Choose mode:\n1. Negativo\n2. Limiar\n3. Ruido\n4. Mediana\n5. LBP\n6. Rota90\n");
  scanf("%i", mode);
	
}


int getImageFormat(FILE *imagein) {
	int format = getc(imagein);
	fscanf(imagein, "%d", &format);	

	return format;
}

void processComment(FILE *imagein){
  // Ignore the first line in the input file
  while (getc(imagein) != '\n');

  if (getc(imagein) == '#') // If it is the case, ignore the second line in the input file
    while (getc(imagein) != '\n');
  else
    fseek(imagein, -1, SEEK_CUR);
}

void getImageValues(FILE *imagein, struct PGMstructure *imginfo) {
  fscanf(imagein, "%d", &imginfo->width);
  fscanf(imagein, "%d", &imginfo->height);
  fscanf(imagein, "%d", &imginfo->maxVal);
  while (getc(imagein) != '\n');
}

void printImageHeader(FILE *imageout, struct PGMstructure *imginfo, int format, int mode) {
  if (mode == 6)
    fprintf(imageout, "%s%i%s%i %i%s%i%s", "P", format, "\n# CREATOR: Image Processor Version 1.1\n", imginfo->height, imginfo->width, "\n", imginfo->maxVal, "\n");
  else
    fprintf(imageout, "%s%i%s%i %i%s%i%s", "P", format, "\n# CREATOR: Image Processor Version 1.1\n", imginfo->width, imginfo->height, "\n", imginfo->maxVal, "\n");
}
