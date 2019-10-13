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

Az alabbi fuggveny elso parametere egy sztring. A feladat a sztring
megforditasa. A feladat megoldhato egy ciklus es ket szamlalo hasznalataval.
Az elso szamlalo a sztring elejerol, a masodik a vegerol indul. Minden
lepesben a ket szamlalo altal mutatott elemet kell kicserelni.
Az eredmenyt az eredeti str nevu sztringben kell elkesziteni.
Kodold le a fuggvenyt C nyelven. A fuggveny fejlecen ne valtoztass!
*/
void strmegforditas(char str[]) {
    int begin, end, count = 0;
    gets(str);
    while (str[count] != '\0')
        count++;
    end = count - 1;
    char reverse[count];
    for (begin = 0; begin < count; begin++) {
        reverse[begin] = str[end];
        end--;
    }
    reverse[begin] = '\0';
    for(int i =0; i < count; ++i) {
        str[i] = reverse[i];
    }
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
	char x=0, str[128]="#####", *p;
	int  N=-1;
	int i;
	for(i=0;i<128;++i) str[i]='#';
	if(fscanf(stdin, "%c", &x)!=1) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	if(x=='E' || x=='R') {
		if(fscanf(stdin, ":%d", &N)!=1) {
			fprintf(stderr, "HIBA: Nem olvasható adat!\n");
			return;
		}
	}
	if(!(fscanf(stdin, "%*[^\n]") || (fgetc(stdin) != EOF))) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	if(fgets(str, 128, stdin)==NULL) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	for(p=str;*p&&*p!=10;p++);
	*p=0;
	strmegforditas(str);
	if(x=='R') {
		fprintf(stdout, "%d\n", str[N]);
	} else if(x=='E') {
		int i;
		for(i=0; i<N; i++) {
			fprintf(stdout, "%c", str[i]);
		}
		fputc('\n', stdout);
	} else {
		fprintf(stdout, "%s\n", str);
	}
}

void test_1()
{
    int i, j;
    char str[] = "####################";
    struct {char str[20]; char eredmeny[20];} testlist[2] = {
        {"progalap",          "palagorp"         },
        {"indulagorogaludni", "indulagorogaludni"},
    };
    for (i = 0; i < 2; ++i) {
        for(j = 0; testlist[i].str[j] != 0; str[j] = testlist[i].str[j], ++j);
        str[j] = 0;
        strmegforditas(str);
        for(j = 0; str[j] != 0 && testlist[i].eredmeny[j] != 0 && str[j] == testlist[i].eredmeny[j]; ++j);
        if (str[j] != testlist[i].eredmeny[j]) {
            fprintf(stderr, "HIBA: strmegforditas(\"%s\")\n", testlist[i].str);
            fprintf(stderr, "\telvárt eredmény: \"%s\"\n", testlist[i].eredmeny);
            fprintf(stderr, "\tkapott eredmény: \"%s\"\n", str);
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
