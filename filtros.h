#ifndef FILTROS_HEADER
#define FILTROS_HEADER

#include "image.h"

void Negativo(FILE **imageout, struct PGMstructure *imginfo, unsigned char **mat, int format);

void Limiar(FILE **imageout, struct PGMstructure *imginfo, unsigned char **mat, int format, int limiar);

void Ruido(FILE **imageout, struct PGMstructure *imginfo, unsigned char **mat, int format);

void Mediana(FILE **imageout, struct PGMstructure *imginfo, unsigned char **mat, int format, int mediana);

void Lbp(FILE **imageout, struct PGMstructure *imginfo, unsigned char **mat, int format);

void Rota90(FILE **imageout, struct PGMstructure *imginfo, unsigned char **mat, int format);

#endif
