#ifndef PROGRAM_FILE_MUVELET_H
#define PROGRAM_FILE_MUVELET_H

#include <string.h>
#include "seged.h"



typedef struct kifejezes
{
    szam *szamok;
    char *muveletek;
    int szamdb;
}kifejezes;

kifejezes* kiftomb(void);
void eredmeny_fkiir(int sorszam, char szoveg[], szam szam1);

#endif //PROGRAM_FILE_MUVELET_H
