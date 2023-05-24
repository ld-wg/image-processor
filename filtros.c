#include <stdlib.h>

#include "filtros.h"

#define P5 5
#define P2 2

void Negativo(FILE **imageout, struct PGMstructure *imginfo, unsigned char **mat, int format) {
  int i, j;

  if (format == P5)
    {
      for (i = 0; i < imginfo->height; i++)
      {
        for (j = 0; j < imginfo->width; j++)
        {
          fprintf(*imageout, "%c", 255 - mat[i][j]);
        }
      }
    }
    if (format == P2)
    {
      for (i = 0; i < imginfo->height; i++)
      {
        for (j = 0; j < imginfo->width; j++)
        {
          fprintf(*imageout, "%hhu ", 255 - mat[i][j]);
        }
      }
    }
  
}

void Limiar(FILE **imageout, struct PGMstructure *imginfo, unsigned char **mat, int format, int limiar) {
	int i, j;
    if (format == P5)
    {
      for (i = 0; i < imginfo->height; i++)
      {
        for (j = 0; j < imginfo->width; j++)
        {
          if (mat[i][j] >= (limiar * imginfo->maxVal))
          {
            fprintf(*imageout, "%c", imginfo->maxVal);
          }
          else
          {
            fprintf(*imageout, "%c", 0);
          }
        }
      }
    }
    
    if (format == P2)
    {
      for (i = 0; i < imginfo->height; i++)
      {
        for (j = 0; j < imginfo->width; j++)
        {
          if (mat[i][j] >= (limiar * imginfo->maxVal))
          {
            fprintf(*imageout, "%hhu ", imginfo->maxVal);
          }
          else
          {
            fprintf(*imageout, "%hhu ", 0);
          }
        }
      }
    }
}

void Ruido(FILE **imageout, struct PGMstructure *imginfo, unsigned char **mat, int format) {
	int i, j;

    if (format == P5)
    {
      for (i = 0; i < imginfo->height; i++)
      {
        for (j = 0; j < imginfo->width; j++)
        {
          int k, l;
          int counter = 0;
          int media = 0;
          for (k = i - 1; k <= i + 1; k++)
          {
            for (l = j - 1; l <= j + 1; l++)
            {
              if ((k >= 0 && k < imginfo->height) && (l >= 0 && l < imginfo->width))
              {
                counter++;
                media += mat[k][l];
              }
            }
          }
          fprintf(*imageout, "%c", media / counter);
        }
      }
    }
    
    if (format == P2)
    {
      for (i = 0; i < imginfo->height; i++)
      {
        for (j = 0; j < imginfo->width; j++)
        {
          int k, l;
          int counter = 0;
          int media = 0;
          for (k = i - 1; k <= i + 1; k++)
          {
            for (l = j - 1; l <= j + 1; l++)
            {
              if ((k >= 0 && k < imginfo->height) && (l >= 0 && l < imginfo->width))
              {
                counter++;
                media += mat[k][l];
              }
            }
          }
          fprintf(*imageout, "%hhu ", media / counter);
        }
      }
    }
	
}

// Função ṕara usar com a Mediana
int cmpfunc(const void *a, const void *b)
{
  return (*(int *)a - *(int *)b);
}

void Mediana(FILE **imageout, struct PGMstructure *imginfo, unsigned char **mat, int format, int mediana) {


	int i, j;
    if (format == P5)
    {
      unsigned char *string = malloc(mediana * mediana * sizeof(unsigned char));
      for (i = 0; i < imginfo->height; i++)
      {
        for (j = 0; j < imginfo->width; j++)
        {
          int k, l;
          int counter = 0;
          if ((i < (mediana / 2)) || (i >= imginfo->height - (mediana / 2)) || (j < (mediana / 2)) || (j >= imginfo->width - (mediana / 2)))
          {
            fprintf(*imageout, "%c", mat[i][j]);
          }
          else
          {
            for (k = i - (mediana / 2); k <= i + (mediana / 2); k++)
            {
              for (l = j - (mediana / 2); l <= j + (mediana / 2); l++)
              {
                string[counter] = mat[k][l];
                counter++;
              }
            }
            qsort(string, mediana * mediana, sizeof(unsigned char), cmpfunc);
            fprintf(*imageout, "%c", string[(mediana * mediana) / 2]);
          }
        }
      }
      free(string);
    }
    
    if (format == P2)
    {
      unsigned char *string = malloc(mediana * mediana * sizeof(unsigned char));
      for (i = 0; i < imginfo->height; i++)
      {
        for (j = 0; j < imginfo->width; j++)
        {
          int k, l;
          int counter = 0;
          if ((i < (mediana / 2)) || (i >= imginfo->height - (mediana / 2)) || (j < (mediana / 2)) || (j >= imginfo->width - (mediana / 2)))
          {
            fprintf(*imageout, "%hhu ", mat[i][j]);
          }
          else
          {
            for (k = i - (mediana / 2); k <= i + (mediana / 2); k++)
            {
              for (l = j - (mediana / 2); l <= j + (mediana / 2); l++)
              {
                string[counter] = mat[k][l];
                counter++;
              }
            }
            qsort(string, mediana * mediana, sizeof(unsigned char), cmpfunc);
            fprintf(*imageout, "%hhu ", string[(mediana * mediana) / 2]);
          }
        }
      }
      free(string);
    }
}

void Lbp(FILE **imageout, struct PGMstructure *imginfo, unsigned char **mat, int format) {
	int i, j;
  unsigned char mask[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    if (format == P5)
    {
      for (i = 0; i < imginfo->height; i++)
      {
        for (j = 0; j < imginfo->width; j++)
        {
          if ((i > 0 && i < imginfo->height - 1) && (j > 0 && j < imginfo->width - 1))
          {
            int value = 0;
            int k, l;
            int counter = 0;
            int v_values[8];
            for (k = i - 1; k <= i + 1; k++)
            {
              for (l = j - 1; l <= j + 1; l++)
              {
                if ((k != i) && (l != j))
                {
                  if (mat[k][l] >= mat[i][j])
                  {
                    v_values[counter] = 1;
                    counter++;
                  }
                  else
                  {
                    v_values[counter] = 0;
                    counter++;
                  }
                }
              }
            }
            for (counter = 0; counter < 8; counter++)
            {
              v_values[counter] *= mask[counter];
              value += v_values[counter];
            }
            fprintf(*imageout, "%c", value + 20);
          }
          else
          {
            fprintf(*imageout, "%c", mat[i][j]);
          }
        }
      }
    }
    if (format == P2)
    {
      for (i = 0; i < imginfo->height; i++)
      {
        for (j = 0; j < imginfo->width; j++)
        {
          if ((i > 0 && i < imginfo->height - 1) && (j > 0 && j < imginfo->width - 1))
          {
            int value = 0;
            int k, l;
            int counter = 0;
            unsigned char v_values[8];
            for (k = i - 1; k <= i + 1; k++)
            {
              for (l = j - 1; l <= j + 1; l++)
              {
                if ((k != i) && (l != j))
                {
                  if ((int)mat[k][l] >= (int)mat[i][j])
                  {
                    v_values[counter] = 1;
                    counter++;
                  }
                  else
                  {
                    v_values[counter] = 0;
                    counter++;
                  }
                }
              }
            }
            for (counter = 0; counter < 8; counter++)
            {
              if (v_values[counter] == 1) {
              value += (int)(v_values[counter] * mask[counter]);
              }
            }
            fprintf(*imageout, "%hhu ", value + 20);
          }
          else
          {
            fprintf(*imageout, "%hhu ", mat[i][j]);
          }
        }
      }
    }
}

void Rota90(FILE **imageout, struct PGMstructure *imginfo, unsigned char **mat, int format) {
	int i, j;
	if (format == P5)
    {
      for (i = 0; i < imginfo->width; i++)
      {
        for (j = imginfo->height - 1; j >= 0; j--)
        {
          fprintf(*imageout, "%c", mat[j][i]);
        }
      }
    }
    if (format == P2) {
   	  for (i = 0; i < imginfo->width; i++)
      {
        for (j = imginfo->height - 1; j >= 0; j--)
        {
          fprintf(*imageout, "%hhu ", mat[j][i]);
        }
      }
    }

}
