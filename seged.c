#include "seged.h"

char *error = "Nem sikerult letrehozni a dinamikus tombot.\n";

/*egy alternativ malloc1, realloc1 fuggveny:
 * ha nem sikerulne letrehoznia a dinamikus tombot, akkor azt megmondja a felhasznalonak
 * */
void *malloc1(int size_t)
{
    void *p = malloc(size_t);
    if (p == NULL) {
        printf("%s", error);
        return NULL;
    } else
        return p;
}

void *realloc1(void *p, int size_t) {
    p = realloc(p, size_t);
    if (p == NULL) {
        printf("%s", error);
        return NULL;
    } else
        return p;
}

void kiiras(szam szam1) {
    for(int i = szam1.hossz-1; i >-1; i--)
    {
        printf("%d", szam1.szjegyek[i]);
    }
}

bool nagyobb (szam szam1, szam szam2)                               //megmondja, hogy a szam1 nagyobb-e a szam2-nel
{
    if (szam1.hossz > szam2.hossz)
        return true;
    else if (szam2.hossz > szam1.hossz)
        return false;
    else
    {
        for (int i = szam1.hossz; i>-1; i--)
        {
            if(szam1.szjegyek[i]>szam2.szjegyek[i])
                return true;

            else if (szam1.szjegyek[i]<szam2.szjegyek[i])
                return false;
        }
        return false;
    }
}

bool egyenlo(szam szam1 ,szam szam2)
{
    if (szam1.hossz == szam2.hossz)
    {
        for (int i = 0; i < szam1.hossz; i++)
        {
            if (szam1.szjegyek[i] != szam2.szjegyek[i])
                return false;
        }
        return true;
    }
    else return false;
}

szam tizhatvany (szam szam1, int kitevo)
{
    szam eredmeny;
    eredmeny.hossz = kitevo + szam1.hossz;
    eredmeny.szjegyek = calloc(kitevo+szam1.hossz, sizeof(int));
    int j = 0;
    for (int i = kitevo; i<eredmeny.hossz;i++)
    {
        eredmeny.szjegyek[i] = szam1.szjegyek[j];
        j++;
    }

    return eredmeny;
}