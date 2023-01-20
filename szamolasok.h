#ifndef PROGRAM_SZAMOLASOK_H
#define PROGRAM_SZAMOLASOK_H

#include "seged.h"

typedef struct marszam
{
    szam eredmeny;
    szam maradek;
}marszam;

szam osszeadas(szam szam1, szam szam2);
szam kivonas(szam szam1, szam szam2);
szam szorzas(szam szam1, szam szam2);
marszam osztas (szam osztando, szam oszto);
szam ea (szam szam1, szam szam2);

#endif //PROGRAM_SZAMOLASOK_H
