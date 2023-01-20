#include "szamolasok.h"

/*
 *
 */
szam osszeadas(szam szam1, szam szam2)
{
    szam eredmeny;
    eredmeny.hossz = max(szam1.hossz, szam2.hossz);
    eredmeny.szjegyek = (int*) malloc1(sizeof(int) * eredmeny.hossz);

    int tobblet = 0;
    int i;
    for (i = 0; i < eredmeny.hossz; i++)
    {
        if (i < min(szam1.hossz, szam2.hossz)) {
            eredmeny.szjegyek[i] = (szam1.szjegyek[i] + szam2.szjegyek[i] + tobblet) % 10;
            tobblet = (szam1.szjegyek[i] + szam2.szjegyek[i] + tobblet) / 10;
        }
        else if (szam1.hossz > szam2.hossz)
        {
            eredmeny.szjegyek[i] = (szam1.szjegyek[i] + tobblet) % 10;
            tobblet = (szam1.szjegyek[i] + tobblet) / 10;
        }
        else
        {
            eredmeny.szjegyek[i] = (szam2.szjegyek[i] + tobblet) % 10;
            tobblet = (szam2.szjegyek[i] + tobblet) / 10;
        }
    }
    if (tobblet > 0) {
        eredmeny.szjegyek = realloc1(eredmeny.szjegyek, sizeof(int) * (eredmeny.hossz + 1));
        eredmeny.szjegyek[i] = tobblet;
    }

    return eredmeny;
}
/*
 * szam1 nagyobb, mint szam2, igy kell megadnia a felhasznalonak
 * */
szam kivonas(szam szam1, szam szam2)
{
    szam eredmeny;
    eredmeny.hossz = szam1.hossz;
    eredmeny.szjegyek = (int*) malloc1(sizeof(int) * eredmeny.hossz);

    int tobblet = 0;
    int i;
    for (i = 0; i < eredmeny.hossz; i++)
    {
        if (i <  szam2.hossz) { //eddig az indexelesig mindket tomb tartalmaz szamokat
            eredmeny.szjegyek[i] = (szam1.szjegyek[i] - szam2.szjegyek[i] - tobblet) % 10;
        }
        else    //itt mar csak a nagyobb szamnak maradtak szamjegyei, ezeket siman leirjuk az eredmenybe is
        {
            eredmeny.szjegyek[i] = (szam1.szjegyek[i] - tobblet) % 10;
        }
        tobblet = 0;
        while (eredmeny.szjegyek[i] < 0) {
            eredmeny.szjegyek[i] += 10;
            tobblet += 1;
        }
    }
    i = eredmeny.hossz-1;
    while (eredmeny.szjegyek[i] == 0 && i > 0)
    {
        eredmeny.szjegyek = realloc1(eredmeny.szjegyek, sizeof(int) * i);
        eredmeny.hossz -= 1;
        i--;
    }

    return eredmeny;
}

/* egy integer tipusu szammal valo szorzasa egy elmeletileg barmekkora nagy szamnak
 *
 */
szam konst_szorz(szam szam1, int konst)
{
    int i;
    szam eredmeny;
    eredmeny.hossz = szam1.hossz;
    eredmeny.szjegyek = (int*) malloc1(sizeof(int) * eredmeny.hossz);

    int tobblet = 0;
    for (i = 0; i < szam1.hossz; i++)
    {
        eredmeny.szjegyek[i] = (szam1.szjegyek[i] * konst + tobblet) % 10;
        tobblet = (szam1.szjegyek[i] * konst + tobblet) / 10;
    }
    while (tobblet != 0)
    {
        eredmeny.hossz++;
        eredmeny.szjegyek = realloc1(eredmeny.szjegyek, sizeof(int) * (eredmeny.hossz));
        eredmeny.szjegyek[i] = tobblet % 10;
        tobblet = tobblet / 10;
        i++;
    }

    return eredmeny;
}

/*
 *
 */
szam szorzas (szam szam1, szam szam2)
{
    szam eredmeny;
    eredmeny.hossz = 1;
    eredmeny.szjegyek = (int*) malloc1(sizeof(int) * eredmeny.hossz);
    eredmeny.szjegyek[0] = 0;

    for (int j = 0; j < szam2.hossz;j++)
        if(szam2.szjegyek[j] != 0)
        {
            szam tmp = eredmeny;
            szam tmp1 = konst_szorz(szam1, szam2.szjegyek[j]);
            szam tmp2 = tizhatvany(tmp1,j);
            eredmeny = osszeadas(eredmeny, tmp2);                       //szamjegyenkent szorzom a szamokat a helyiertekukkel
            free(tmp.szjegyek);
            free(tmp1.szjegyek);
            free(tmp2.szjegyek);
        }
    return eredmeny;
}

/*
 *
 */
marszam osztas (szam osztando, szam oszto) //osztot ugy kapja, hogy az != 0
{
    if(nagyobb(oszto, osztando))
    {
        marszam eredmeny;
        eredmeny.maradek = osztando;
        eredmeny.eredmeny.hossz =1;
        eredmeny.eredmeny.szjegyek = malloc1(sizeof(int));
        eredmeny.eredmeny.szjegyek[0] = 0;

        return eredmeny;
    }
    else if (egyenlo(oszto, osztando))
    {
        marszam eredmeny;
        eredmeny.maradek.hossz = 1;
        eredmeny.maradek.szjegyek = malloc1(sizeof(int));
        eredmeny.maradek.szjegyek[0] = 0;
        eredmeny.eredmeny.hossz =1;
        eredmeny.eredmeny.szjegyek = malloc1(sizeof(int));
        eredmeny.eredmeny.szjegyek[0] = 1;

        free(osztando.szjegyek);

        return eredmeny;
    }

    szam egy;
    egy.szjegyek = (int*) malloc1(sizeof(int));
    egy.szjegyek[0]=1;
    egy.hossz = 1;

    szam eredmeny;
    eredmeny.szjegyek = (int*) malloc1(sizeof(int));
    eredmeny.hossz = 1;
    eredmeny.szjegyek[0] = 0;

    while (nagyobb(osztando, oszto))
    {
        int i = osztando.hossz-oszto.hossz;
        szam id = tizhatvany(oszto, i);       //ideiglenes szam, az osztonak a szorzata az oszto es az osztando szam nagysagrendbeli kulonbsegevel

        while(nagyobb(id, osztando))
        {
            free(id.szjegyek);
            i-=1;
            id = tizhatvany(oszto, i);
        }

        int j = 9;
        szam tmp1 = konst_szorz(id, j);
        while (nagyobb(tmp1, osztando))
        {
            j--;
            free(tmp1.szjegyek);
            tmp1 = konst_szorz(id, j);  //az ideiglenes szam leheto legnagyobb szammal vett szorzata, ami meg kisebb lesz az osztandonal
        }
        free(id.szjegyek);

        szam tmp = osztando;
        osztando = kivonas(osztando, tmp1);
        free(tmp.szjegyek);
        free(tmp1.szjegyek);

        tmp = eredmeny;
        tmp1 =tizhatvany(egy, i);
        szam tmp2 = konst_szorz(tmp1, j); //a vegeredmenyhez hozza fogja adni a program az ebben a ciklus lepesben az oszto kivont darabszamat
        eredmeny = osszeadas(eredmeny, tmp2);
        free(tmp.szjegyek);
        free(tmp1.szjegyek);
        free(tmp2.szjegyek);
    }
    free(egy.szjegyek);

    marszam marszam1;
    marszam1.eredmeny = eredmeny;
    marszam1.maradek = osztando;

    return marszam1;
}

/*
 *
 */
szam ea (szam szam1, szam szam2)
{
    printf("Euklideszi algoritmus alapjan:\n\n");
    if (nagyobb(szam2, szam1))
    {
        szam tmp = szam1;
        szam1 = szam2;
        szam2 = tmp;
        free(tmp.szjegyek);
    }
    kiiras(szam1);
    marszam marszam1 = osztas(szam1, szam2);

    if (marszam1.maradek.szjegyek[0] != 0 || marszam1.maradek.hossz != 1) {
        while (true){
            printf(" = ");
            kiiras(marszam1.eredmeny);
            free(marszam1.eredmeny.szjegyek);

            printf("*");
            kiiras(szam2);
            printf(" + ");
            kiiras(marszam1.maradek);
            printf("\n");

            szam1 = szam2;
            szam2 = marszam1.maradek;

            if (szam2.hossz == 1 && szam2.szjegyek[0] == 0)
                break;
            kiiras(szam1);
            marszam1 = osztas(szam1, szam2);
        }
        free(szam2.szjegyek);

        printf("A ket szam legnagyobb kozos osztoja: ");
        kiiras(szam1);
        printf("\n");
        return szam1;
    }
    else
    {
        if(nagyobb(szam2, marszam1.eredmeny))
        {
            free(szam1.szjegyek);
            free(marszam1.maradek.szjegyek);
            free(marszam1.eredmeny.szjegyek);

            printf("A ket szam legnagyobb kozos osztoja: ");
            kiiras(szam2);
            printf("\n");
            return  szam2;
        }
        else
        {
            free(szam1.szjegyek);
            free(szam2.szjegyek);
            free(marszam1.maradek.szjegyek);

            printf("A ket szam legnagyobb kozos osztoja: ");
            kiiras(marszam1.eredmeny);
            printf("\n");
            return marszam1.eredmeny;
        }
    }
}
