#ifndef IMAGE_HEADER
#define IMAGE_HEADER

#include <stdio.h>

struct PGMstructure
{
  int maxVal;
  int width;
  int height;
};


unsigned char **alocamatriz(struct PGMstructure *imginfo);

void copyPixels(FILE *imagein, struct PGMstructure *imginfo, unsigned char **mat, int format);

void printMenu();

int getImageFormat(FILE *imagein);

void processComment(FILE *imagein);

void getImageValues(FILE *imagein, struct PGMstructure *imginfo);

void printImageHeader(FILE *imageout, struct PGMstructure *imginfo, int format, int mode);

#endif
