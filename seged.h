#ifndef PROGRAM_SEGED_H
#define PROGRAM_SEGED_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct szam
{
    int *szjegyek;  //igy barhany szamjegyes szamot el fog tudni tarolni a program, a tomb kesobb a szamjegyenkenti szamolasnal lesz hasznos
    int hossz;
}szam;

void *malloc1(int size_t);
void *realloc1(void *p, int size_t);

bool egyenlo(szam szam1, szam szam2);
bool nagyobb (szam szam1, szam szam2);
void kiiras(szam szam1);
szam tizhatvany (szam szam1, int kitevo);

#endif //PROGRAM_SEGED_H
