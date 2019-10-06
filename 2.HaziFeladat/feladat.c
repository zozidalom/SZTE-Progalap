/***********************************************************************
* A PROGRAMBAN NEM SZEREPELHETNEK AZ ALÁBBI SOROK:
* #include <string.h>
* #include <math.h>
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************
************************************************************************
**		ETTŐL A PONTTÓL DOLGOZHATSZ A FELADATOKON
************************************************************************
***********************************************************************/

/*
1. feladat (5 pont)

A hupikek torpikek kirandulni mentek, es Dulifuli beleesett egy godorbe.
Termeszetesen nem kialtott segitsegert, hanem egyedul akart kimaszni.
Elso lendulettel felmaszott 10 torparaszt, majd lenezett, es lecsuszott,
meghozza az eddig elert magassaganak 10%-t. (tehat 9 torparasz magassagban sikerult megkapaszkodnia)
Ekkor masodszor is lenduletet vett, 20 araszt maszott, majd megint lenezett,
es megint visszacsuszta az addig elert osszmagassaganak a 10%-at.
Es igy tovabb, minden lenulettel 10 arasszal tobbet maszott felfele,
de minden megallasnal az addigi osszmagassaganak 10%-at elvesztette.

Irj fuggvenyt, melynek parametere a godor melysege (torparaszban),
es egy egesz ertekkel ter vissza: azzal, hogy Dulifuli hanyadik lendulettel maszott ki a godorbol.
*/

int hanyadiklendulet(int cel) {
    if(cel <= 10) {
        return 1;
    }
    int lendulet = 1;
    int maszas = 0;
    while(1) {
        maszas += lendulet*10;
        maszas -= maszas*0.1;
        ++lendulet;
        if(maszas >= cel) {
            break;
        }
    }
    return --lendulet;
}


/***********************************************************************
************************************************************************
**
**	EZEN A PONTON TÚL NE VÁLTOZTASS SEMMIT SEM A FÁJLON!
**
************************************************************************
***********************************************************************/

void call_1()
{
    int n, eredmeny;
    if (fscanf(stdin, "%d", &n) != 1) {
        fprintf(stderr, "HIBA: Nem olvasható adat!\n");
        return;
    }
    eredmeny = hanyadiklendulet(n);
    fprintf(stdout, "%d\n", eredmeny);
}
void test_1()
{
    struct { int cel; int lendulet; } testlist[] = {
        {  5, 1 },
        { 12, 2 },
        { 58, 4 },
        {  0, 0 }
    };
    for (int i = 0; testlist[i].cel; ++i) {
        int r = hanyadiklendulet(testlist[i].cel);
        if (r != testlist[i].lendulet) {
            fprintf(stderr, "HIBA: hanyadiklendulet(%d) = %d\n"
                            "\telvárt eredmény: %d",
                            testlist[i].cel, r, testlist[i].lendulet);
        }
    }
}

typedef void (*call_function)();

call_function call_table[] = {
	call_1,
	NULL
};


call_function test_table[] = {
	test_1,
	NULL
};

static int __arg_check_helper(const char * exp, const char * arg) {
	while (*exp && *arg && *exp == *arg) {
		++exp;
		++arg;
	}
	return *exp == *arg;
}

int main(int argc, char *argv[])
{
	int feladat, calltabsize;
	if ((argc > 1) && !(__arg_check_helper("-t", argv[1]) && __arg_check_helper("--test", argv[1]))) {
		if (argc > 2) {
			feladat = atoi(argv[2]);
			for (calltabsize=0; test_table[calltabsize]; calltabsize++);
			if (feladat <= 0 || calltabsize < feladat) {
				fprintf(stderr, "HIBA: rossz feladat sorszám: %d!\n", feladat);
				return 1;
			}
			(*test_table[feladat-1])();
		} else {
			for (feladat=0; test_table[feladat]; ++feladat) {
				(*test_table[feladat])();
			}
		}
		return 0;
	}
	if (!freopen("be.txt", "r", stdin)) {
		fprintf(stderr, "HIBA: Hiányzik a `be.txt'!\n");
		return 1;
	}
	if (!freopen("ki.txt", "w", stdout)) {
		fprintf(stderr, "HIBA: A `ki.txt' nem írható!\n");
		return 1;
	}
	for (calltabsize=0; call_table[calltabsize]; calltabsize++);
	if (fscanf(stdin, "%d%*[^\n]", &feladat)!=1) {
		fprintf(stderr, "HIBA: Nem olvasható a feladat sorszám!\n");
		return 1;
	}
	fgetc(stdin);
	if (0<feladat && feladat<=calltabsize) {
		(*call_table[feladat-1])();
	} else {
		fprintf(stderr, "HIBA: Rossz feladat sorszám: %d!\n", feladat);
		return 1;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
