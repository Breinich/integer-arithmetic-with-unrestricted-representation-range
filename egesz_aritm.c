#include "file_muvelet.h"
#include "szamolasok.h"
#include "debugmalloc.h"

/* a feladata, hogy kiirja ez eppen elvegzett muveletet:
 * a fuggveny kap 3 szamot, es egy karaktert
 * ezek kozul 2 szam, amikkel dolgozott es a 3. az eredmeny, a karakter pedig a muveleti operator kozejuk */
void er_kiir(szam szam1, szam szam2, szam eredmeny, char c)
{
    kiiras(szam1);
    printf(" %c ", c);
    kiiras(szam2);
    printf(" = ");
    kiiras(eredmeny);
    printf("\n");
}

/* a main vezerli a programot
 * eloszor meghivja a kiftomb fuggvenyt, ami visszater egy matematikai kifejezesek tombjevel:
 * egy kifejezes tartalmazza a szamok tombjet, muveletek tombjet es a szamok darabszamat
 * ezutan kiszamittatja a kifejezeseket a muveleti jelek megadott sorrendjeben, ebben a segitsegere van, hogy a muveleti jelek elott mindg van egy szam, ami azt jelzi, hogy hanyadik szammal kell elvegezni a muveletet
 * eloszor megvizsgalja, hogy euklideszi algoritmust kell-e majd csinalnia, mert ebben az esetben felesleges lenne a kovetkezo lepeseket is megtennie, rogton fel is szbaditja a dinamikusan lefoglalt tomboket a kifejezesen belulrol
 * ezutan ha nem e.a. volt, vegrehajtja a megfelelo muveltetet, mindig meghivja az adott muvelet szamolo fuggvenyet, majd kiiratja az adott muveletet es az eredmenyet, majd felszabaditja a mar nem hasznalando szamokat (szamjegyek dinamikus tombjei), illetve atallitja a "szamvan" tombnek olyan indexu elemet hamisra, amilyen indexu elemet szabaditott fel korabban
 * a "szamvan" tombnek az a funkcioja, hogy megmondja, hogy ebben a kifejezesben az adott indexen van-e a "szamok" tombben dinamikusan lefoglalt memoriara mutato pointer, vagy mar fel lett szabaditva
 * ha az osszes muvelet vegre lett hajtva, tehat elert a program a "muvtomb" vegehez, akkor felszabaditja a maradek lefoglalt memmoria teruletet
 * */
int main() {
    kifejezes *tomb = kiftomb();
    if (tomb != NULL)
    {
        for (int j = 0; tomb[j].szamok != 0; j++)
        {
            printf("\n-----------------------------------\n%d. kifejezes:\n", j+1);
            if (strcmp(tomb[j].muveletek, "2e.a.") == 0)
            {
                if (tomb[j].szamdb == 2) {
                    szam eredmeny = ea(tomb[j].szamok[0], tomb[j].szamok[1]);
                    eredmeny_fkiir(j+1, ". kifejezes:\nA ket megadott szam legnagyob kozos osztoja: ", eredmeny);
                    free(eredmeny.szjegyek);
                    free(tomb[j].muveletek);
                    free(tomb[j].szamok);
                }
                else
                    printf("e.a.: Hibas kifejezest irt be.");
            }
            else {
                bool *szamvan = (bool*) malloc1(sizeof(bool) * tomb[j].szamdb);
                for (int i = 0; i < tomb[j].szamdb; i++)
                    szamvan[i] = true;

                int i = 0;
                int k = tomb[j].szamdb-1;
                int l;

                szam eredmeny;
                eredmeny.hossz = 0;
                eredmeny.szjegyek = NULL;
                while ( tomb[j].muveletek[i] != '\0') {

                    char s = tomb[j].muveletek[i];
                    if (47<s && s<58)
                    {
                        k = atoi(&s)-1;

                        i++;
                    }
                    else {
                        switch (s) {
                            case '+': {
                                if (k > 0) {
                                    szam szam1;
                                    for(l = k-1; l > -1; l--)
                                    {
                                        if(szamvan[l])
                                        {
                                            szam1 = tomb[j].szamok[l];
                                            break;
                                        }
                                    }
                                    if (l == -1)
                                    {
                                        printf("Nincs eleg szam.");
                                        break;
                                    }
                                    szam szam2 = tomb[j].szamok[k];
                                    eredmeny = osszeadas(szam1, szam2);
                                    tomb[j].szamok[k] = eredmeny;
                                    er_kiir(szam1, szam2, eredmeny, s);

                                    free(szam2.szjegyek);
                                    free(szam1.szjegyek);
                                    szamvan[l] = false;
                                    szamvan[k] = true;
                                    break;
                                }
                                else {
                                    printf("+: Nincs eleg osszeadando szam.\n");
                                    break;
                                }
                            }

                            case '-':
                                {
                                szam szam1;
                                for(l = k-1; l > -1; l--)
                                {
                                    if(szamvan[l])
                                    {
                                        szam1 = tomb[j].szamok[l];
                                        break;
                                    }
                                }
                                if (l == -1)
                                {
                                    printf("Nincs eleg szam.\n");
                                    break;
                                }
                                if(k > 0 && nagyobb(tomb[j].szamok[l], tomb[j].szamok[k]))
                                {
                                    szam szam2 = tomb[j].szamok[k];
                                    eredmeny = kivonas(tomb[j].szamok[l], tomb[j].szamok[k]);
                                    tomb[j].szamok[k] = eredmeny;
                                    er_kiir(szam1, szam2, eredmeny, s);

                                    free(szam2.szjegyek);
                                    free(szam1.szjegyek);
                                    szamvan[l] = false;
                                    szamvan[k] = true;

                                    break;
                                }
                                else if (egyenlo(tomb[j].szamok[l], tomb[j].szamok[k]))
                                {

                                    kiiras(szam1);
                                    printf(" - ");
                                    szam szam2 = tomb[j].szamok[k];
                                    kiiras(szam2);
                                    printf(" = 0\n");
                                    tomb[j].szamok[k].hossz = 1;
                                    tomb[j].szamok[k].szjegyek = (int*) malloc1(sizeof(int));
                                    tomb[j].szamok[k].szjegyek[0] = 0;
                                    eredmeny = tomb[j].szamok[k];

                                    free(szam2.szjegyek);
                                    free(szam1.szjegyek);
                                    szamvan[l]=false;
                                    szamvan[k] = true;
                                    break;
                                }
                                else{
                                    printf("-: A kulonbseg negativ lenne. Vagy rossz sorrendben adta meg a szamokat, vagy rossz szamokat adott meg.\n");
                                    break;
                                }
                            }

                            case '*': {
                                if (k > 0) {
                                    szam szam1;
                                    for(l = k-1; l > -1; l--)
                                    {
                                        if(szamvan[l])
                                        {
                                            szam1 = tomb[j].szamok[l];
                                            break;
                                        }
                                    }
                                    if (l == -1)
                                    {
                                        printf("Nincs eleg szam.\n");
                                        break;
                                    }
                                    szam szam2 = tomb[j].szamok[k];
                                    eredmeny = szorzas(szam1, szam2);
                                    tomb[j].szamok[k] = eredmeny;
                                    er_kiir(szam1, szam2, eredmeny, s);

                                    free(szam2.szjegyek);
                                    free(szam1.szjegyek);
                                    szamvan[l] = false;
                                    szamvan[k] = true;
                                    break;
                                }
                                else{
                                    printf("*: Nincs eleg szorzo tenyezo a szorzas elvegzesehez.\n");
                                    break;
                                }
                            }

                            case '/': {
                                szam szam1;
                                for(l = k-1; l > -1; l--)
                                {
                                    if(szamvan[l])
                                    {
                                        szam1 = tomb[j].szamok[l];
                                        break;
                                    }
                                }
                                if (l == -1)
                                {
                                    printf("Nincs eleg szam.\n");
                                    break;
                                }
                                if (k > 0 && (tomb[j].szamok[k].hossz!=1 || tomb[j].szamok[k].szjegyek[0]!=0)) {

                                    kiiras(szam1);
                                    printf(" / ");
                                    szam szam2 = tomb[j].szamok[k];
                                    kiiras(szam2);
                                    printf(" = ");

                                    marszam marszam1 = osztas(szam1, szam2);
                                    tomb[j].szamok[k] = marszam1.eredmeny;
                                    eredmeny = marszam1.eredmeny;
                                    tomb[j].szamok[l] = marszam1.maradek;   //osztas eseten a k. helyen a maradek fog tarolodni
                                    kiiras(tomb[j].szamok[k]);
                                    printf(" maradek: ");
                                    kiiras(tomb[j].szamok[l]);
                                    printf("\n");

                                    free(szam2.szjegyek);
                                    szamvan[k]=true;
                                    szamvan[l]=true;
                                    break;
                                }
                                else {
                                    printf("/: Az oszto 0, igy nem szabad osztani vele, vagy nincs 2 darab szam az osztashoz.\n");
                                    break;
                                }
                            }

                        }

                        i++;
                    }
                }

                eredmeny_fkiir(j+1,". kifejezes eredmenye: ", eredmeny);

                for(l = 0; l < tomb[j].szamdb; l++)
                {
                    if(szamvan[l])
                    {
                        free(tomb[j].szamok[l].szjegyek);
                    }
                }
                free(tomb[j].muveletek);
                free(tomb[j].szamok);
                free(szamvan);
            }
        }
        free(tomb);
        return 0;
    }
    else
        exit(1);
}
