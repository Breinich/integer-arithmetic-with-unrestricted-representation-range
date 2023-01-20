#include "file_muvelet.h"

/* ez a fuggveny olvassa be a felhasznalo altal megadott kifejezeseket
 *
 */
char *beolvasas(void) {
    printf("\n\n1) Nyomjon egy \"e\" gombot, majd irja be a kifejezeseket, vagy egy \"f\" gombot, majd adja meg a beolvasando file (peldaul:\"C:/Users/admin/Desktop/vmi.txt\") eleresi utjat!\n"
           "\n2) A kiszamitando kifejezest forditott lengyel jelolessel irja be!\n"
           "Ha Euklideszi algoritmust szeretne vegrehajtani, akkor a 2 szam utan egy szokozzel elvalasztva ezt irja be: \"e.a.\"!\n"
           "Ha egy linearis kongruenciat szeretne megoldani, akkor eloszor az x egyutthatojat adja meg, majd szokozzel elvalasztva azt, hogy mivel legyen kongruens, majd szokozzel elvalasztva azt, hogy mi a modulo-ja az egyenletnek, majd szokozzel elvalasztva irjon be egy \"m\" betut!\n"
           "\n3) Ha befejezte a kifejezesek beirasat a programablakba, akkor nyomjon egy \"x\" gombot!\n"
           "(file-bol csak egyszer lehet beolvasni, de abba barmyennyi kefejezest beirhat)\n\n");

    char s = getchar();
    char *szoveg = malloc1(sizeof(char) * 1);
    switch (s) {
        case 'f': //beolvasas file-bol
        {
            char *hely; //az eleresi ut lesz ebben a tombben
            int i;
            hely = (char *) malloc1(sizeof(char) * 1);
            for (i = 2; (s = getchar()) != '\n'; i++) {
                hely = realloc1(hely, sizeof(char) * i);
                hely[i - 2] = s;
            }
            hely[i - 2] = '\0';
            FILE *fp;
            fp = fopen(hely, "r");
            if (fp != NULL) {
                free(hely);
                int k;
                for (k = 1; (s = fgetc(fp)) != EOF; k++) {
                    szoveg = realloc1(szoveg, sizeof(char) * (k + 2));
                    szoveg[k - 1] = s;
                }
                szoveg[k - 1] = '\n';
                szoveg[k] = '\0';
                //printf("%s", szoveg);
                fclose(fp);
                return szoveg;
            }
            else {
                free(szoveg);
                printf("Ezt az eleresi utvonalat adta meg: %s\n", hely);
                free(hely);
                perror("Nem sikerult beolvasni a file-t.\n");
                return "";
            }
        }

        case 'e':  //beolvasas a programablakbol
        {
            int k;
            for (k = 1; (s = getchar()) != 'x'; k++) {
                szoveg = realloc1(szoveg, sizeof(char) * (k + 2));
                szoveg[k - 1] = s;
            }
            szoveg[k - 1] = '\n';   //ez azert kell, hogy majd a strukturaba pakolas soran kilepjen a program a belso while ciklusbol is
            szoveg[k] = '\0';
            return szoveg;
        }
    }
    return "";
}

szam megforditas(szam szam1) //azert, hogy a 0-as indexen a pl 10^0 helyierteku szamjegy legyen
{
    szam szam2;
    int h = szam1.hossz;
    szam2.szjegyek = (int*) malloc1(sizeof(int) * h);
    szam2.hossz = h;
    for(int i = 0; i < h; i++)
    {
        szam2.szjegyek[i] = szam1.szjegyek[h-i-1];
    }
    free(szam1.szjegyek);
    return szam2;
}

typedef enum elozo
{
    digit,
    muvelet
}elozo;

kifejezes *kiftomb(void) {
    kifejezes *kiftomb;
    kiftomb = (kifejezes*) malloc1(sizeof(struct kifejezes) * 1);

    int k = 0;

    char *szoveg = beolvasas();

    if (strcmp(szoveg, "") == 0)
    {
        free(kiftomb);
        return NULL;
    }
    else
    {
        int szamdb = 0;
        int muvdb = 0;
        int i = 0;
        int j = 0;
        char s;

        while ((s = szoveg[i]) != '\0')
        {
            kifejezes kifejezes1;
            kifejezes1.szamok = (szam *) malloc1(sizeof(szam) * 1);

            char *muveletek;
            muveletek = (char *) malloc1(sizeof(char) * 2);

            elozo elozo1;
            while ((s = szoveg[i]) != '\n') {
                int *szamtomb;
                szamtomb = (int *) malloc1(sizeof(int) * 1);

                while ( 47 < (s = szoveg[i]) && (s = szoveg[i]) < 58 )
                {
                    szamtomb = realloc1(szamtomb, sizeof(int) * (j + 1));       //minden egyes szam szamjegyeit fel kell majd szabaditani
                    szamtomb[j] = atoi(&s);
                    j++;
                    i++;
                    elozo1 = digit;
                }
                if (s ==' ') // ha vege egy van egy szamnak, akkor azt berakja a kifejezest tarolo strukturaba
                {
                    if(elozo1 == digit) {
                        szam szam1;
                        szam1.szjegyek = szamtomb;
                        szam1.hossz = j;
                        j = 0;
                        kifejezes1.szamok = realloc1(kifejezes1.szamok, sizeof(szam) * (szamdb + 1));       //szamokat kell felszabaditani
                        kifejezes1.szamok[szamdb] = megforditas(szam1);
                        szamdb++;
                    }
                    else
                        free(szamtomb);
                    i++;
                } else if (s == '+' || s == '-' || s == '/' || s == '*' || s == 'm' || s == 'e' || s == 'a' || s == '.')   //muveleti operatorok tarolodnak itt el
                {
                    if(elozo1 == muvelet)
                    {
                        muveletek = realloc1(muveletek, sizeof(char) * (muvdb + 2));
                        muveletek[muvdb] = s;
                        muvdb++;
                        i++;
                        elozo1 = muvelet;
                        free(szamtomb);
                    }
                    else
                    {
                        muveletek = realloc1(muveletek, sizeof(char) * (muvdb + 3));        //muveleteket majd fel kell szabaditani
                        muveletek[muvdb] = szamdb + '0';        //azt jeloli, hogy hanyadik szam utan van az adott muvelet
                        muveletek[muvdb + 1] = s;
                        muvdb +=2;
                        i++;
                        elozo1 = muvelet;
                        free(szamtomb);
                    }
                }
                else
                {
                    free(szamtomb);
                    break;
                }
            }

            muveletek[muvdb] = '\0';
            kifejezes1.muveletek = muveletek;
            kifejezes1.szamdb = szamdb;
            kiftomb = realloc1(kiftomb, sizeof(kifejezes) * (k + 1));
            kiftomb[k] = kifejezes1;
            k++;
            i++;
            muvdb = 0;
            szamdb = 0;
        }
        kifejezes kifejezes1;   //hozzaad a program egy ures kifejezest, vegjelnek a kifejezes tombbe
        kifejezes1.szamdb = 0;
        kifejezes1.muveletek = "";
        kifejezes1.szamok = NULL;
        kiftomb = realloc1(kiftomb, sizeof(kifejezes) * (k + 1));           //kiftombot fel kell majd szabaditani
        kiftomb[k] = kifejezes1;

        free(szoveg);
        return kiftomb;
    }
}

void eredmeny_fkiir(int sorszam, char szoveg[], szam szam1)
{
    FILE *fp;
    fp = fopen("./eredmenyek.txt", "a");
    if (fp != NULL)
    {
        if (szam1.hossz != 0)
        {
            fprintf(fp, "------------------------------\n");
            fprintf(fp, "%d%s\n", sorszam, szoveg);
            for (int i = szam1.hossz - 1; i > -1; i--) {
                fprintf(fp, "%d", szam1.szjegyek[i]);
            }
            fprintf(fp, "\n");
        }
        else
        {
            fprintf(fp, "------------------------------\n");
            fprintf(fp, "%d%snincs megoladsa.\n", sorszam, szoveg);
        }
        fclose(fp);
    }
    else {
        perror("Nem sikerült megnyitni a fájlt");
    }
}
