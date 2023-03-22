#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define M 2147483648
#define C 1103515245
#define A 12345

long long seed;
int broj_runde;
int na_dole;
int na_gore;
int rucna;

int	*baci_kocke();
int	*biraj_kocke(int *kocke);
int 	*biraj_potez(int **tabela, int *c, int *r, int *v, int *kocke, int bacanje);
void	brisi_matricu(int **tabela);
void 	igra();
int 	lkg();
void 	nova_igra();
int 	**nova_tabela(int *c, int *r, int *v);
void 	pisi_tabelu(int **tabela, int *c, int *r, int *v);
int	*pomoc_prijatelja(int **tabela, int *c, int *r, int *v, int *kocke);
void 	runda(int **tabela, int *c, int *r, int *v);
void 	sortiraj(int *kocke);
void 	upisi(int **tabela, int *c, int *r, int *v, int *kocke, int bacanje);
void	upisi_bodove(int **tabela, int *c, int *r, int *v, int kolona, int vrsta, int *kocke, int bacanje);
void 	upisi_rucnu(int **tabela, int *c, int *r, int *v, int *kocke);
int	verovatnoca(int *kocke, int vrsta);

int lkg(){
	seed = (A * seed + C) % M;
	return (int)(seed % 6 + 1);
}

int *baci_kocke(){
	static int kocke[5];
	for ( int i = 0; i < 10; i++ ) {
		kocke[i] = lkg();
	}
	return kocke;
}

int *biraj_kocke(int *kocke){
	int polje;
	printf("Unesite brojeve kockica koje zelite ponovo da bacite (1 - 5)\n");
	do{
		scanf("%d", &polje);
		if (polje >= 1 && polje <= 5)
			kocke[polje-1] = lkg();
	}while(getchar() != '\n');
	return kocke;
}

int *biraj_potez(int **tabela, int *c, int *r, int *v, int *kocke, int bacanje){
	char x;
	printf("\nUnesite 0 za pocetni meni\n");
	if(na_dole < 11 || na_gore > 0)
		printf("Unesite 1 da ponovo bacite kocke\n");
	printf("Unesite 2 da upisete u tabelu\n");
	if(bacanje == 1)
		printf("Unesite 3 za pomoc prijatelja\n");
	while(1){
		scanf("\n%c", &x);
		switch(x){
			case '1': 
				if(na_dole < 11 || na_gore > 0){
					return biraj_kocke(kocke);
				}
				else
					printf("Uneta opcija ne postoji...marko\n");
                		break;
			case '2':
				*kocke = 20;
				return kocke;
			case '3':
				if(bacanje == 1){
					return pomoc_prijatelja(tabela, c, r, v, kocke);
				}
				else
					printf("Uneta opcija ne postoji...\n");
                		break;
			case '0':
				if(broj_runde < 14){
					free(c);
					free(r);
					free(v);
				}
				else
					brisi_matricu(tabela);
				broj_runde = 40;
                		*kocke = 10;
				return kocke;
			default:
				printf("Uneta opcija ne postoji...\n");
				break;
		}
	}
}

void brisi_matricu(int **tabela){
	for (int i = 0; i < 11; i++)
		free(tabela[i]);
	free(tabela);
}

void pisi_tabelu(int **tabela, int *c, int *r, int *v){
	int **tmp;
	printf("\n");
	printf("             na dole   na gore    rucna   \n");
	printf("           ┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓\n"); //printf("           -------------------------------\n");
	if (broj_runde < 14)
		tmp = nova_tabela(c, r, v);
	else 
		tmp = tabela;
	for (int i = 0; i < 11; i++){
		for (int j = 0; j < 3; j++){
			if(j == 0) {
                if (i < 6)
                    	printf("         %d ", i + 1);
                else if (i == 6)
                    	printf(" kenta - 7 ");
                else if (i == 7)
                    	printf("   ful - 8 ");
                else if (i == 8)
                    	printf(" poker - 9 ");
                else if (i == 9)
                    	printf(" jamb - 10 ");
                else if (i == 10)
                    	printf("      suma ");
            }
			if (tmp[i][j] == -1)
				printf("┃         "); //printf("|         ");
			else if (tmp[i][j] == 0 && i != 10)
				printf("┃    x    "); //printf("|    x    ");
			else if (tmp[i][j] < 10)
				printf("┃    %d    ", tmp[i][j]); //printf("|    %d    ", tmp[i][j]);
			else if (tmp[i][j] < 100)
				printf("┃    %d   ", tmp[i][j]); //printf("|    %d   ", tmp[i][j]);
			else 
				printf("┃   %d   ", tmp[i][j]); //printf("|   %d   ", tmp[i][j]);
		}
		if (i < 10)
			printf("┃\n           ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫\n"); //printf("|\n           -------------------------------\n");
	}
	printf("┃\n           ┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛\n\n");  //printf("|\n           -------------------------------\n\n");
	if (broj_runde < 14)
		brisi_matricu(tmp);
}

int *pomoc_prijatelja(int **tabela, int *c, int *r, int *v, int *kocke){
	int **tmp, *k = malloc(sizeof(int));
	*k = 10;
	if(broj_runde < 14)
		tmp = nova_tabela(c, r, v);
	else
		tmp = tabela;
	sortiraj(kocke);

	if((tmp[9][2] == -1) && (kocke[0] == kocke[1] && kocke[0] == kocke[2] && kocke[0] == kocke[3] && kocke[0] == kocke[4])){
		upisi_bodove(tabela, c, r, v, 2, 10, kocke, 1);
        	rucna --;
		if(broj_runde < 14)
			brisi_matricu(tmp);
		return k;
	}
	if((tmp[8][2] == -1) && (kocke[1] == kocke[2] && kocke[2] == kocke[3] && (kocke[0] == kocke[1] || kocke[0] == kocke[4]))){
		upisi_bodove(tabela, c, r, v, 2, 9, kocke, 1);
		rucna --;
		if(broj_runde < 14)
			brisi_matricu(tmp);
		return k;
	}
	if((tmp[7][2] == -1) && ((kocke[0] == kocke[1] && kocke[1] == kocke[2] && kocke[3] == kocke[4]) || (kocke[0] == kocke[1] && kocke[2] == kocke[3] && kocke[3] == kocke[4]))){
		upisi_bodove(tabela, c, r, v, 2, 8, kocke, 1);
		rucna --;
		if(broj_runde < 14)
			brisi_matricu(tmp);
		return k;
	}
	if((tmp[6][2] == -1) && (kocke[0] + 1 == kocke[1] && kocke[1] + 1 == kocke[2] && kocke[2] + 1 == kocke[3] && kocke[3] + 1 == kocke[4])){
		upisi_bodove(tabela, c, r, v, 2, 7, kocke, 1);
		rucna --;
		if(broj_runde < 14)
			brisi_matricu(tmp);
		return k;
	}
	for(int i = 6; i > 0; i--){
		int br = 0;
		for (int j = 0; j < 5; j++)
			if (i == kocke[j])
				br++;
		if(tmp[i - 1][2] == -1 && br > 0){
			upisi_bodove(tabela, c, r, v, 2, i, kocke, 1);
			rucna --;
			if(broj_runde < 14)
				brisi_matricu(tmp);
			return k;
		}
	}
	if (na_dole == 11 && na_gore == 0){
		upisi_rucnu(tabela, c, r, v, kocke);
		return k;
	}
	for(int z = 0; z < 2; z++){
		int ponovo[5] = {-1, -1, -1, -1, -1};
		if(na_dole <= 6 && na_gore <= 6){
			int broj_d = 0, broj_g = 0;
			for(int i = 0; i < 5; i++){
				if(na_dole == kocke[i])
					broj_d ++;
				if(na_gore == kocke[i])
					broj_g++;
			}
			int j = 0;
			for(int i = 0; i < 5; i++){
				if(broj_d >= broj_g && kocke[i] != na_dole){
					ponovo[j] = i;
					j ++;
				}
				if(broj_d < broj_g && kocke[i] != na_gore){
					ponovo[j] = i;
					j ++;
				}
			}
		}
		if(na_dole > 6 && na_gore <= 6){
			int x = verovatnoca(kocke, na_dole);
			if(x == 20){
				upisi_bodove(tabela, c, r, v, 0, na_dole, kocke, 1 + z);
				na_dole ++;
				if(broj_runde < 14)
					brisi_matricu(tmp);
				return k;
			}
			if(x == -1){
				int j = 0;
				for(int i = 0; i < 5; i++)
					if(kocke[i] != na_gore){
						ponovo[j] = i;
						j ++;
					}
			}	
			else
				ponovo[0] = x;
		}
		if(na_dole <= 6 && na_gore > 6){
			int x = verovatnoca(kocke, na_gore);
			if(x == 20){
				upisi_bodove(tabela, c, r, v, 1, na_gore, kocke, 1 + z);
				na_gore --;
				if(broj_runde < 14)
					brisi_matricu(tmp);
				return k;
			}
			if(x == -1){
				int j = 0;
				for(int i = 0; i < 5; i++)
					if(kocke[i] != na_dole){
						ponovo[j] = i;
						j ++;
					}
			}
			else
				ponovo[0] = x;
		}
		if(na_dole > 6 && na_gore > 6){
			int d = verovatnoca(kocke, na_dole);
			int g = verovatnoca(kocke, na_gore);
			if(g == 20){
				upisi_bodove(tabela, c, r, v, 1, na_gore, kocke, 1 + z);
				na_gore --;
				if(broj_runde < 14)
					brisi_matricu(tmp);
				return k;
			}
			if(d == 20){
				upisi_bodove(tabela, c, r, v, 0, na_dole, kocke, 1 + z);
				na_dole ++;
				if(broj_runde < 14)
					brisi_matricu(tmp);
				return k;
			}
			if(g != -1)
				ponovo[0] = g;
			else if(d != -1)
				ponovo[0] = d;
			else{
				for(int i = 0; i < 5; i++)
					ponovo[i] = i;
			}
		}
		printf("\nVase kocke su ");
		for(int i = 0; i < 5; i++)
			printf("%d ", kocke[i]);
		printf("\nPonovo bacam kocke ");
		int i = 0;
		while(ponovo[i] != -1 && i < 5){
			printf("%d ", ponovo[i] + 1);
			i++;
		}
		printf("\nPritisnite enter da nastavite...\n");
		if (z == 0) 
			getchar();
		while(getchar()!='\n'){}
		i = 0;
		while(ponovo[i] != -1 && i < 5){
			kocke[ponovo[i]] = lkg();
			i++;
		}
	}
	if(na_gore <= 6 && na_dole <= 6){
		upisi_bodove(tabela, c, r, v, 0, na_dole, kocke, 3);
		na_dole ++;
	}
	else if(na_gore > 6 && na_dole > 6){
		upisi_bodove(tabela, c, r, v, 1, na_gore, kocke, 3);
		na_gore --;
	}
	else if(na_gore > 0 && na_dole > 6){
		upisi_bodove(tabela, c, r, v, 1, na_gore, kocke, 3);
		na_gore --;
	}
	else{
		upisi_bodove(tabela, c, r, v, 0, na_dole, kocke, 3);
		na_dole ++;
	}
	if(broj_runde < 14)
		brisi_matricu(tmp);
	return k;
}

int verovatnoca(int kocke[], int vrsta){
	int br = 0, vrv = 0;
	sortiraj(kocke);
	if (vrsta == 10){
		for(int i = 0; i < 4; i++){
			if(kocke[i] == kocke[i + 1])
				br++;
			else{
				if(br > vrv)
					vrv = br;
				br = 0;
			}
		}
		if(vrv == 3){
			for (int i = 0; i < 5; i++)
				if(kocke[i] != kocke[2])
					return i;
		}
		else if(vrv == 4)
			return 20;
	}
	if(vrsta == 9){
		for(int i = 0; i < 4; i++){
			if(kocke[i] == kocke[i+1])
				br++;
			else{
				if(br > vrv)
					vrv = br;
				br = 0;
			}
		}
		if(vrv == 2){
			for (int i = 0; i < 5; i++)
				if(kocke[i] != kocke[2])
					return i;
		}
		else if(vrv == 3)
			return 20;
	}
	if(vrsta == 8){
		if((kocke[0] == kocke[1] && kocke[1] == kocke[2] && kocke[3] == kocke[4]) || (kocke[0] == kocke[1] && kocke[2] == kocke[3] && kocke[3] == kocke[4]))
			return 20;
		else if(kocke[0] == kocke[1] && kocke[2] == kocke[3])
			return 4;
		else if(kocke[0] == kocke[1] && kocke[3] == kocke[4])
			return 2;
		else if(kocke[1] == kocke[2] && kocke[3] == kocke[4])
			return 0;
	}
	if(vrsta == 7){
		if(kocke[0] + 1 == kocke[1] && kocke[1] + 1 == kocke[2] && kocke[2] + 1 == kocke[3] && kocke[3] + 1 == kocke[4])
			return 20;
		else if(kocke[1] + 1 == kocke[2] && kocke[2] + 1 == kocke[3] && kocke[3] + 1 == kocke[4])
			return 0;
		else if(kocke[0] + 2 == kocke[2] && kocke[2] + 1 == kocke[3] && kocke[3] + 1 == kocke[4])
			return 1;
		else if(kocke[0] + 1 == kocke[1] && kocke[1] + 2 == kocke[3] && kocke[3] + 1 == kocke[4])
			return 2;
		else if(kocke[0] + 1 == kocke[1] && kocke[1] + 1 == kocke[2] && kocke[2] + 2 == kocke[4])
			return 3;
		else if(kocke[0] + 1 == kocke[1] && kocke[1] + 1 == kocke[2] && kocke[2] + 1 == kocke[3])
			return 4;
	}
	return -1;
}

void sortiraj(int *kocke){
	for(int i = 0; i < 4; i++)
		for (int j = i + 1; j < 5; j++)
			if (kocke[i] > kocke[j]){
				int a = kocke[i];
				kocke[i] = kocke[j];
				kocke[j] = a;
			}
}

void upisi_csc(int *c, int *r, int *v, int kolona, int vrsta, int vrednost){
	for(int i = kolona + 1; i < 4; i++)
		c[i] ++;
	for(int i = broj_runde; i > c[kolona] - 1; i--){
		r[i] = r[i - 1];
		v[i] = v[i - 1];
	}
	*(r + *(c + kolona)) = vrsta;
	*(v + *(c + kolona)) = vrednost;
}

void upisi_bodove(int **tabela, int *c, int *r, int *v, int kolona, int vrsta, int kocke[], int bacanje){
	int br_bodova, br = 0;
	if (vrsta <= 6){
		for (int i = 0; i < 5; i++)
			if (vrsta == kocke[i])
				br ++;
		br_bodova = br * vrsta;
	}
	else if (vrsta == 7){
		if (kocke[0] + 1 == kocke[1] && kocke[1] + 1 == kocke[2] && kocke[2] + 1 == kocke[3] && kocke[3] + 1 == kocke[4])
			br_bodova = 46 + (3 - bacanje) * 10;
		else 
			br_bodova = 0;
	}
	else if (vrsta == 8){
		if (kocke[0] == kocke[1] && kocke[1] == kocke[2] && kocke[3] == kocke[4])
			br_bodova = 30 + 3 * kocke[0] + 2 * kocke[3];

		else if (kocke[0] == kocke[1] && kocke[2] == kocke[3] && kocke[3] == kocke[4])
			br_bodova = 30 + 2 * kocke[0] + 3 * kocke[2];
		else
			br_bodova = 0;
	}
	else if (vrsta == 9){
		for(int i = 1; i < 5; i++){
			if (kocke[i] == kocke[i-1]){
				br ++;
				if (br == 3){
					br_bodova = 40 + kocke[i] * 4;
					break;
				}
			}
			else
				br = 0;
		}
		if (br < 3)
			br_bodova = 0;
	}
	else if (vrsta == 10){
		for(int i = 1; i < 5; i++){
			if (kocke[i] != kocke[0])
				break;
			br ++;
		}
		if (br == 4)
			br_bodova = 50 + kocke[0] * 5;
		else 
			br_bodova = 0;
	}
	if(broj_runde < 14)
		upisi_csc(c, r, v, kolona, vrsta - 1, br_bodova);
	else{
		tabela[vrsta - 1][kolona] = br_bodova;
		tabela[10][kolona] += tabela[vrsta - 1][kolona];
	}
}

void upisi_rucnu(int **tabela, int *c, int *r, int *v, int kocke[]){
	int x, j = 0, **tmp;
	int opcije[rucna];
	if (broj_runde < 14)
		tmp = nova_tabela(c, r, v);
	else
		tmp = tabela;
	printf("Izaberite jedno od praznih polja u koloni rucna ( ");
	for (int i = 0; i < 10; i++)
		if (tmp[i][2] == -1){
			opcije[j] = i + 1;
			printf ("%d ", i + 1);
			j ++;
		}
	if (broj_runde < 14)
		brisi_matricu(tmp);
	printf(")\n");
	while(1){
		scanf("\n%d", &x);
		j = 0;
		for(int i = 0; i < rucna; i++)
			if (opcije[i] == x && x != -1){
				j = 1;
				break;
			}
		if (j == 0)
			printf("Uneta opcija ne postoji...\n");
		else{
			upisi_bodove(tabela, c, r, v, 2, x, kocke, 1);
			rucna --;
			break;
		}
	}
}

void upisi(int **tabela, int *c, int *r, int *v, int kocke[], int bacanje){
	char x;
	int j = 0;
	if (na_dole < 11)
		printf("\nZa upis u kolonu 'na dole' unesite 1");
	if (na_gore > 0)
		printf("\nZa upis u kolonu 'na gore' unesite 2");
	if (rucna > 0 && bacanje == 1)
		printf("\nZa upis u kolonu 'rucna' unesite 3");
	printf("\n");
	while(j == 0){
		scanf("\n%c", &x);
		switch(x) {
			case '1':
                		if (na_dole < 11){
					upisi_bodove(tabela, c, r, v, 0, na_dole, kocke, bacanje);
					na_dole ++;
					j = 1;
				}
                		else
					printf("Uneta opcija ne postoji...\n");
				break;
			case '2':
				if (na_gore > 0){
					upisi_bodove(tabela, c, r, v, 1, na_gore, kocke, bacanje);
					na_gore --;
					j = 1;
				}
				else
					printf("Uneta opcija ne postoji...\n");
				break;
			case '3':
				if ( rucna > 0 && bacanje == 1){
					upisi_rucnu(tabela, c, r, v, kocke);
					j = 1;
				}
				else
					printf("Uneta opcija ne postoji...\n");
				break;
			default :
				printf("Uneta opcija ne postoji...\n");
				break;
		}
	}
}

void runda(int **tabela, int *c, int *r, int *v){
	int bacanje = 1, *t, *kocke = (int *)malloc(5 * sizeof(int));
	t = baci_kocke();

	while(bacanje < 3 && *t != 20){
		system("clear"); //system("cls");
		pisi_tabelu(tabela, c, r, v);
		printf("\nBacanje: %d \n", bacanje);
		for (int i = 0; i < 5; i++){
			printf("%d\t", t[i]);
			kocke[i] = t[i];
		}
		printf("\n");
		t = biraj_potez(tabela, c, r, v, t, bacanje);
		if(*t == 10){
			free(t);
			free(kocke);
			return;
		}
		bacanje++;
	}
	if(*t == 20)
		bacanje--;
	else 
		kocke = t;
	system("clear"); //system("cls");
	pisi_tabelu(tabela, c, r, v);
	printf("\nBacanje: %d \n", bacanje);
	for (int i = 0; i < 5; i++)
		printf("%d\t", kocke[i]);
	printf("\n");
	sortiraj(kocke);
	upisi(tabela, c, r, v, kocke, bacanje);
}

int **nova_tabela(int *c, int *r, int *v){
	int **tabela = (int **)malloc( 11 * sizeof(int *));
	for (int i = 0; i < 11; i++)
		tabela[i] = (int *)malloc( 3 * sizeof(int));

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 3; j++)
			tabela[i][j] = -1;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < c[i + 1] - c[i]; j++)
			tabela[r[c[i] + j]][i] = v[c[i] + j];
	for (int i = 0; i < 3; i++){
		tabela[10][i] = 0;
		for(int j = 0; j < 10; j++)
			if (tabela[j][i] != -1)
				tabela[10][i] += tabela[j][i];
	}
	return tabela;
}

void igra(){
	int **tabela = NULL;
	int *c = (int *)malloc(4 * sizeof(int));
	int *r = (int *)malloc(0);
	int *v = (int *)malloc(0);
	for (int i = 0; i < 4; i++)
		c[i] = 0;
	na_dole = 1;
	na_gore = 10;
	rucna = 10;
	for (broj_runde = 0; broj_runde < 30; broj_runde ++){
		if(broj_runde < 14){
			r = (int *)realloc(r, (broj_runde + 1) * sizeof(int));
			v = (int *)realloc(v, (broj_runde + 1) * sizeof(int));
		}
		if (broj_runde == 14){
			tabela = nova_tabela(c, r, v);
			free(c);
			free(r);
			free(v);
		}
		runda(tabela, c, r, v);
	}
	if (broj_runde == 30){
		system("clear"); //system("cls");
		pisi_tabelu(tabela, c, r, v);
		printf("Kraj igre\nPritisnite enter za nastavak...\n");
		getchar();
		while(getchar() != '\n') {}
		brisi_matricu(tabela);
	}
}

void nova_igra(){
	char x;
	system("clear"); //system("cls");
	printf("     ##  #####  ###    ### ######\n");
	printf("     ## ##   ## ####  #### ##   ##\n");
	printf("     ## ####### ## #### ## ######\n");
    	printf("##   ## ##   ## ##  ##  ## ##   ##\n");
    	printf(" #####  ##   ## ##      ## ######\n\n");
	printf("Za novu igru unesite 1\nZa izlaz unesite 0\n");
	scanf("\n%c", &x);
	if(x == '0')
		exit(0);
	else if(x == '1')
		igra();
}

int main(){
	seed = time(NULL);
	while(1)
		nova_igra();
	return 0;
}
