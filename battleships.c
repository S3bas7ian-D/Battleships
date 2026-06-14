#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Dinu Andrei Sebastian 311CB

// struct pentru caracteristicile navei
// struct pentru statisticile unui meci
typedef struct {
	int numar_lovituri_totale;
	int numar_lovituri_nimerite;
	double acuratete_meci;
	int numar_nave_meci;
	int numar_meci;
} statistici_meci;

// am adaugat indice meci
// functie alocare vector meciuri
statistici_meci *alocare_vector_statistici(int J)
{
	statistici_meci *vector_statistici = (statistici_meci *)
		calloc(J, sizeof(statistici_meci));
	if (!vector_statistici) {
		perror("Eroare la alocarea vectorului de structuri nava");
	}

	return vector_statistici;
}

// struct pentru nave
typedef struct {
	char tip;
	char orientare;
	int x;
	int y;
} nava;

// functie alocare vector de struct de nave
nava *alocare_vector_nave(int N)
{
	nava *vector_nave = (nava *)calloc(N, sizeof(nava));
	if (!vector_nave) {
		perror("Eroare la alocarea vectorului de structuri nava");
	}

	return vector_nave;
}

// functie eliberare tabla
void elibereaza_tabla(char **tabla, int N)
{
	if (!tabla) {
		return;
	}
	for (int i = 0; i < N; i++) {
		if (tabla[i])
			free(tabla[i]);
	}
	free(tabla);
}

// functie formatare float-uri la doua zecimale
void trunchiaza_la_doua_zecimale(double *numar)
{
	*numar = floor(*numar * 100.0) / 100.0;
}

// bubble sort pentru meciuri in functie de acuratete si numarul de nave
void bubble_sort_statistici(statistici_meci *vector_meciuri, int J)
{
	statistici_meci temp;
	int ok = 0;
	while (ok == 0) {
		ok = 1;
		for (int i = 1; i < J; i++) {
			if (vector_meciuri[i].acuratete_meci >
			    vector_meciuri[i + 1].acuratete_meci) {
				temp = vector_meciuri[i];
				vector_meciuri[i] = vector_meciuri[i + 1];
				vector_meciuri[i + 1] = temp;
				ok = 0;
			}
		}
	}
}

// functie calcul acuratete per meci
double ac_totala(int J, statistici_meci *vector_statistici_jucator)
{
	double numarator = 0;
	double numitor = 0;
	double acuratete_totala = 0;
	for (int i = 1; i <= J; i++) {
		numarator += vector_statistici_jucator[i].acuratete_meci *
			     vector_statistici_jucator[i].numar_nave_meci;
		numitor += vector_statistici_jucator[i].numar_nave_meci;
	}
	acuratete_totala = numarator / numitor * 100;
	return acuratete_totala;
}

// functie pentru qsort de comparare, tot pentru acuratete totala
int compara_acuratete(const void *a, const void *b)
{
	const statistici_meci *stat_a = (const statistici_meci *)a;
	const statistici_meci *stat_b = (const statistici_meci *)b;

	double val_a = (double)stat_a->numar_nave_meci * stat_a->acuratete_meci;
	double val_b = (double)stat_b->numar_nave_meci * stat_b->acuratete_meci;

	if (val_a < val_b)
		return -1;
	if (val_a > val_b)
		return 1;
	return 0;
}

// alocare tabla
char **alocare_tabla(int N, int M)
{
	char **tabla = (char **)calloc(N, sizeof(char *));
	if (!tabla) {
		perror("Eroare la alocarea tabloului de pointeri (randuri)");
		return NULL;
	}
	for (int i = 0; i < N; i++) {
		tabla[i] = (char *)calloc(M, sizeof(char));
		if (!tabla[i]) {
			perror("Eroare la alocarea memoriei pentru un rand");
			for (int j = 0; j < i; j++) {
				free(tabla[j]);
			}
			free(tabla);
			return NULL;
		}
	}

	return tabla;
}

// functie plasare nava
int plaseaza_nava(char **tabla, char t, char o, int x, int y, int N, int M)
{
	int i;
	// -------------------------caz vertical-----------------------------
	if (o == 'V') {
		if (t == 'S' && x - 4 >= 1 && x <= N) {
			for (i = x; i >= x - 4; i--) {
				if (tabla[i][y] == 0)
					tabla[i][y] = '5';
				else {
					for (int j = x; j > i; j--) {
						tabla[j][y] = 0;
					}
					return 1;
				}
			}
			return 0;
		} else if (t == 'Y' && x - 3 >= 1 && x <= N) {
			for (i = x; i >= x - 3; i--) {
				if (tabla[i][y] == 0)
					tabla[i][y] = '4';
				else {
					for (int j = x; j > i; j--) {
						tabla[j][y] = 0;
					}
					return 1;
				}
			}
			return 0;
		} else if (t == 'B' && x - 2 >= 1 && x <= N) {
			for (i = x; i >= x - 2; i--) {
				if (tabla[i][y] == 0)
					tabla[i][y] = '3';
				else {
					for (int j = x; j > i; j--) {
						tabla[j][y] = 0;
					}
					return 1;
				}
			}
			return 0;
		} else if (t == 'L' && x - 1 >= 1 && x <= N) {
			for (i = x; i >= x - 1; i--) {
				if (tabla[i][y] == 0)
					tabla[i][y] = '2';
				else {
					for (int j = x; j > i; j--) {
						tabla[j][y] = 0;
					}
					return 1;
				}
			}
			return 0;
		} else if (t == 'A' && x >= 1 && x <= N) {
			if (tabla[x][y] == 0) {
				tabla[x][y] = '1';
				return 0;
			} else
				return 1;
		}
	}
	// -------------------caz orizontal---------------------
	else if (o == 'H') {
		if (t == 'S' && y + 4 <= M && y >= 1) {
			for (i = y; i <= y + 4; i++) {
				if (tabla[x][i] == 0)
					tabla[x][i] = '5';
				else {
					for (int j = y; j < i; j++) {
						tabla[x][j] = 0;
					}
					return 1;
				}
			}
			return 0;
		} else if (t == 'Y' && y + 3 <= M && y >= 1) {
			for (i = y; i <= y + 3; i++) {
				if (tabla[x][i] == 0)
					tabla[x][i] = '4';
				else {
					for (int j = y; j < i; j++) {
						tabla[x][j] = 0;
					}
					return 1;
				}
			}
			return 0;
		} else if (t == 'B' && y + 2 <= M && y >= 1) {
			for (i = y; i <= y + 2; i++) {
				if (tabla[x][i] == 0)
					tabla[x][i] = '3';
				else {
					for (int j = y; j < i; j++) {
						tabla[x][j] = 0;
					}
					return 1;
				}
			}
			return 0;
		} else if (t == 'L' && y + 1 <= M && y >= 1) {
			for (i = y; i <= y + 1; i++) {
				if (tabla[x][i] == 0)
					tabla[x][i] = '2';
				else {
					for (int j = y; j < i; j++) {
						tabla[x][j] = 0;
					}
					return 1;
				}
			}
			return 0;
		} else if (t == 'A' && y <= M && y >= 1) {
			if (tabla[x][y] == 0) {
				tabla[x][y] = '1';
				return 0;
			} else
				return 1;
		}
	}
	return 1;
}

// main
int main(void)
{
	int J, N, M;
	short ok_distrus = 0;
	char **tabla_A, **tabla_B;
	if (scanf("%d", &J) != 1)
		return 1;
	char *cheie = calloc(120, sizeof(char));
	char comanda[15] = "";

	// alocam spatiu pentru meciuri si copiile lor.
	statistici_meci *vector_statistici_A = alocare_vector_statistici(J + 1);
	statistici_meci *vector_statistici_B = alocare_vector_statistici(J + 1);
	statistici_meci *vector_statistici_CA = alocare_vector_statistici(J + 1);
	statistici_meci *vector_statistici_CB = alocare_vector_statistici(J + 1);
	int CJ = J;
	int meciul_nr = 1;

	// intram in etapa de joc
	while (CJ) {
		char tip, orientare;
		if (scanf("%d %d", &N, &M) != 2)
			return 1;
		int nr_S = 0, nr_Y = 0, nr_B = 0, nr_L = 0, nr_A = 0;
		nr_S = N * M / 70;
		nr_Y = N * M / 55;
		nr_B = N * M / 40;
		nr_L = N * M / 30;
		nr_A = N * M / 20;

		// punem un id la meciuri pentru a putea sa le accesam dupa
		vector_statistici_A[meciul_nr].numar_meci = meciul_nr;
		vector_statistici_B[meciul_nr].numar_meci = meciul_nr;
		int total_pe_jucator = nr_S + nr_Y + nr_B + nr_L + nr_A;
		tabla_A = alocare_tabla(N + 1, M + 1);
		tabla_B = alocare_tabla(N + 1, M + 1);
		nava *v_nave_A = alocare_vector_nave(total_pe_jucator + 1);
		nava *v_nave_B = alocare_vector_nave(total_pe_jucator + 1);
		int x, y, ok;
		char turn = 'A';
		int a = 1, b = 1;
		vector_statistici_A[meciul_nr].numar_nave_meci = total_pe_jucator;
		vector_statistici_B[meciul_nr].numar_nave_meci = total_pe_jucator;

		// Etapa de plasare nave in meciul respectiv
		while (a <= total_pe_jucator || b <= total_pe_jucator) {
			if (turn == 'A' && a > total_pe_jucator) {
				turn = 'B';
			} else if (turn == 'B' && b > total_pe_jucator) {
				turn = 'A';
			}
			scanf(" %c %c", &tip, &orientare);
			scanf(" %d %d", &x, &y);

			// randul jucatorului A
			if (turn == 'A') {
				ok = plaseaza_nava(tabla_A, tip, orientare, x, y, N, M);
				if (ok == 0) {
					turn = 'B';
					v_nave_A[a].tip = tip;
					v_nave_A[a].orientare = orientare;
					v_nave_A[a].x = x;
					v_nave_A[a++].y = y;
				} else if (ok == 1) {
					// cazurile de esuare cand plasam
					if (orientare == 'H') {
						if (tip == 'S')
							printf("Nava Shinano nu poate fi amplasata orizontal la coordonatele (%d, %d).\n", x, y);
						if (tip == 'Y')
							printf("Nava Yamato nu poate fi amplasata orizontal la coordonatele (%d, %d).\n", x, y);
						if (tip == 'B')
							printf("Nava Belfast nu poate fi amplasata orizontal la coordonatele (%d, %d).\n", x, y);
						if (tip == 'L')
							printf("Nava Laffey nu poate fi amplasata orizontal la coordonatele (%d, %d).\n", x, y);
						if (tip == 'A')
							printf("Nava Albacore nu poate fi amplasata orizontal la coordonatele (%d, %d).\n", x, y);
					}
					if (orientare == 'V') {
						if (tip == 'S')
							printf("Nava Shinano nu poate fi amplasata vertical la coordonatele (%d, %d).\n", x, y);
						if (tip == 'Y')
							printf("Nava Yamato nu poate fi amplasata vertical la coordonatele (%d, %d).\n", x, y);
						if (tip == 'B')
							printf("Nava Belfast nu poate fi amplasata vertical la coordonatele (%d, %d).\n", x, y);
						if (tip == 'L')
							printf("Nava Laffey nu poate fi amplasata vertical la coordonatele (%d, %d).\n", x, y);
						if (tip == 'A')
							printf("Nava Albacore nu poate fi amplasata vertical la coordonatele (%d, %d).\n", x, y);
					}
				}
			}
			// randul jucatorului B
			else if (turn == 'B') {
				ok = plaseaza_nava(tabla_B, tip, orientare, x, y, N, M);
				if (ok == 0) {
					turn = 'A';
					v_nave_B[b].tip = tip;
					v_nave_B[b].orientare = orientare;
					v_nave_B[b].x = x;
					v_nave_B[b++].y = y;
				} else if (ok == 1) {
					if (orientare == 'H') {
						if (tip == 'S')
							printf("Nava Shinano nu poate fi amplasata orizontal la coordonatele (%d, %d).\n", x, y);
						if (tip == 'Y')
							printf("Nava Yamato nu poate fi amplasata orizontal la coordonatele (%d, %d).\n", x, y);
						if (tip == 'B')
							printf("Nava Belfast nu poate fi amplasata orizontal la coordonatele (%d, %d).\n", x, y);
						if (tip == 'L')
							printf("Nava Laffey nu poate fi amplasata orizontal la coordonatele (%d, %d).\n", x, y);
						if (tip == 'A')
							printf("Nava Albacore nu poate fi amplasata orizontal la coordonatele (%d, %d).\n", x, y);
					}
					if (orientare == 'V') {
						if (tip == 'S')
							printf("Nava Shinano nu poate fi amplasata vertical la coordonatele (%d, %d).\n", x, y);
						if (tip == 'Y')
							printf("Nava Yamato nu poate fi amplasata vertical la coordonatele (%d, %d).\n", x, y);
						if (tip == 'B')
							printf("Nava Belfast nu poate fi amplasata vertical la coordonatele (%d, %d).\n", x, y);
						if (tip == 'L')
							printf("Nava Laffey nu poate fi amplasata vertical la coordonatele (%d, %d).\n", x, y);
						if (tip == 'A')
							printf("Nava Albacore nu poate fi amplasata vertical la coordonatele (%d, %d).\n", x, y);
					}
				}
			}
		}

		// afisare tabla jucatorului 1
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (tabla_A[i][j] != 0)
					printf("%c ", tabla_A[i][j]);
				else
					printf("%d ", tabla_A[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		// afisare tabla jucatorului 2
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (tabla_B[i][j] != 0)
					printf("%c ", tabla_B[i][j]);
				else
					printf("%d ", tabla_B[i][j]);
			}
			printf("\n");
		}
		a--;
		b--;
		char turn_lupta = 'A';

		// etapa de lupta
		while (a != 0 && b != 0) {
			scanf("%d %d", &x, &y);
			if (x < 1 || x > N || y < 1 || y > M) {
				continue;
			}

			ok_distrus = 0;
			// randul jucatorului A
			if (turn_lupta == 'A') {
				// verificam daca este ratata lovitura
				if (tabla_B[x][y] == 0 || tabla_B[x][y] == '#') {
					vector_statistici_A[meciul_nr].numar_lovituri_totale++;
					printf("Jucatorul 1 a ratat o lovitura la coordonatele (%d, %d).\n", x, y);
					tabla_B[x][y] = 'x';
				}
				// verificam daca este repetata lovitura
				else if (tabla_B[x][y] == 'x') {
					printf("Coordonatele (%d, %d) au fost deja atacate de jucatorul 1.\n", x, y);
					vector_statistici_A[meciul_nr].numar_lovituri_totale++;
				}
				// ramura de lovitura valida
				else if (tabla_B[x][y] >= '1' && tabla_B[x][y] <= '5') {
					vector_statistici_A[meciul_nr].numar_lovituri_nimerite++;
					vector_statistici_A[meciul_nr].numar_lovituri_totale++;
					short lungime = tabla_B[x][y] - '0';
					// verificam in vectorul de nave daca am nimerit o radacina sau nu
					for (int i = 1; i <= total_pe_jucator; i++) {
						if (v_nave_B[i].x == x && v_nave_B[i].y == y) {
							ok_distrus = 1;
							if (v_nave_B[i].orientare == 'V') {
								// daca a fost lovita o radacina,
								// scufundam nava cu caractere '#',
								// pastram locurile marcate ca lovite
								for (int j = x; j > x - lungime; j--) {
									if (tabla_B[j][y] != 'x')
										tabla_B[j][y] = '#';
								}
								// mesaje de scufundare pentru orientarea verticala
								if (lungime == 5)
									printf("Jucatorul 1 a distrus o nava Shinano plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x - 4, y);
								else if (lungime == 4)
									printf("Jucatorul 1 a distrus o nava Yamato plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x - 3, y);
								else if (lungime == 3)
									printf("Jucatorul 1 a distrus o nava Belfast plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x - 2, y);
								else if (lungime == 2)
									printf("Jucatorul 1 a distrus o nava Laffey plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x - 1, y);
								else if (lungime == 1)
									printf("Jucatorul 1 a distrus o nava Albacore plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x, y);
							}
							// scufundare daca nava e pe orizontala
							else if (v_nave_B[i].orientare == 'H') {
								for (int j = y; j < y + lungime; j++) {
									if (tabla_B[x][j] != 'x')
										tabla_B[x][j] = '#';
								}
								// mesaje scufundare orizontala
								if (lungime == 5)
									printf("Jucatorul 1 a distrus o nava Shinano plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x, y + 4);
								else if (lungime == 4)
									printf("Jucatorul 1 a distrus o nava Yamato plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x, y + 3);
								else if (lungime == 3)
									printf("Jucatorul 1 a distrus o nava Belfast plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x, y + 2);
								else if (lungime == 2)
									printf("Jucatorul 1 a distrus o nava Laffey plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x, y + 1);
								else if (lungime == 1)
									printf("Jucatorul 1 a distrus o nava Albacore plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x, y);
							}
							// scadem numarul de nave ale jucatorului B
							b--;
							break;
						}
					}
					if (ok_distrus == 0) {
						// cazul in care doar am lovit, fara sa scufundam
						if (tabla_B[x][y] == '5')
							printf("Jucatorul 1 a lovit o nava Shinano la coordonatele (%d, %d).\n", x, y);
						if (tabla_B[x][y] == '4')
							printf("Jucatorul 1 a lovit o nava Yamato la coordonatele (%d, %d).\n", x, y);
						if (tabla_B[x][y] == '3')
							printf("Jucatorul 1 a lovit o nava Belfast la coordonatele (%d, %d).\n", x, y);
						if (tabla_B[x][y] == '2')
							printf("Jucatorul 1 a lovit o nava Laffey la coordonatele (%d, %d).\n", x, y);
						if (tabla_B[x][y] == '1')
							printf("Jucatorul 1 a lovit o nava Albacore la coordonatele (%d, %d).\n", x, y);
					}
					// marcare lovitura
					tabla_B[x][y] = 'x';
				}
				turn_lupta = 'B';
			}
			// final turn A

			// acelasi principiu si algoritm ca la turn-ul lui A
			// doar ca oglindit pentru a-l afecta pe jucatorul A
			else if (turn_lupta == 'B') {
				if (tabla_A[x][y] == 0 || tabla_A[x][y] == '#') {
					vector_statistici_B[meciul_nr].numar_lovituri_totale++;
					printf("Jucatorul 2 a ratat o lovitura la coordonatele (%d, %d).\n", x, y);
					tabla_A[x][y] = 'x';
				} else if (tabla_A[x][y] == 'x') {
					vector_statistici_B[meciul_nr].numar_lovituri_totale++;
					printf("Coordonatele (%d, %d) au fost deja atacate de jucatorul 2.\n", x, y);
				} else if (tabla_A[x][y] >= '1' && tabla_A[x][y] <= '5') {
					vector_statistici_B[meciul_nr].numar_lovituri_totale++;
					vector_statistici_B[meciul_nr].numar_lovituri_nimerite++;
					short lungime = tabla_A[x][y] - '0';
					for (int i = 1; i <= total_pe_jucator; i++) {
						if (v_nave_A[i].x == x && v_nave_A[i].y == y) {
							ok_distrus = 1;
							if (v_nave_A[i].orientare == 'V') {
								for (int j = x; j > x - lungime; j--) {
									if (tabla_A[j][y] != 'x')
										tabla_A[j][y] = '#';
								}
								if (lungime == 5)
									printf("Jucatorul 2 a distrus o nava Shinano plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x - 4, y);
								else if (lungime == 4)
									printf("Jucatorul 2 a distrus o nava Yamato plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x - 3, y);
								else if (lungime == 3)
									printf("Jucatorul 2 a distrus o nava Belfast plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x - 2, y);
								else if (lungime == 2)
									printf("Jucatorul 2 a distrus o nava Laffey plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x - 1, y);
								else if (lungime == 1)
									printf("Jucatorul 2 a distrus o nava Albacore plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x, y);
							} else if (v_nave_A[i].orientare == 'H') {
								for (int j = y; j < y + lungime; j++) {
									if (tabla_A[x][j] != 'x')
										tabla_A[x][j] = '#';
								}
								if (lungime == 5)
									printf("Jucatorul 2 a distrus o nava Shinano plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x, y + 4);
								else if (lungime == 4)
									printf("Jucatorul 2 a distrus o nava Yamato plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x, y + 3);
								else if (lungime == 3)
									printf("Jucatorul 2 a distrus o nava Belfast plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x, y + 2);
								else if (lungime == 2)
									printf("Jucatorul 2 a distrus o nava Laffey plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x, y + 1);
								else if (lungime == 1)
									printf("Jucatorul 2 a distrus o nava Albacore plasata intre coordonatele (%d, %d) si (%d, %d).\n", x, y, x, y);
							}
							a--;
							break;
						}
					}
					if (ok_distrus == 0) {
						if (tabla_A[x][y] == '5')
							printf("Jucatorul 2 a lovit o nava Shinano la coordonatele (%d, %d).\n", x, y);
						if (tabla_A[x][y] == '4')
							printf("Jucatorul 2 a lovit o nava Yamato la coordonatele (%d, %d).\n", x, y);
						if (tabla_A[x][y] == '3')
							printf("Jucatorul 2 a lovit o nava Belfast la coordonatele (%d, %d).\n", x, y);
						if (tabla_A[x][y] == '2')
							printf("Jucatorul 2 a lovit o nava Laffey la coordonatele (%d, %d).\n", x, y);
						if (tabla_A[x][y] == '1')
							printf("Jucatorul 2 a lovit o nava Albacore la coordonatele (%d, %d).\n", x, y);
					}
					tabla_A[x][y] = 'x';
				}
				turn_lupta = 'A';
			}
		}
		if (a)
			printf("Jucatorul 1 a castigat.\n");
		else
			printf("Jucatorul 2 a castigat.\n");
		CJ--;
		// trecem in vectorii de statistici statisticile meciului
		vector_statistici_A[meciul_nr].acuratete_meci =
			(double)vector_statistici_A[meciul_nr].numar_lovituri_nimerite /
			vector_statistici_A[meciul_nr].numar_lovituri_totale;
		vector_statistici_B[meciul_nr].acuratete_meci =
			(double)vector_statistici_B[meciul_nr].numar_lovituri_nimerite /
			vector_statistici_B[meciul_nr].numar_lovituri_totale;
		// meciul urmator
		meciul_nr++;
		// eliberam spatiul
		if (v_nave_A)
			free(v_nave_A);
		if (v_nave_B)
			free(v_nave_B);
		elibereaza_tabla(tabla_A, N + 1);
		elibereaza_tabla(tabla_B, N + 1);
		v_nave_A = NULL;
		v_nave_B = NULL;
		tabla_A = NULL;
		tabla_B = NULL;
	}
	int gaseste_meciul;
	// sortam meciurile dupa acuratete*numarul de nave
	bubble_sort_statistici(vector_statistici_A, J);
	bubble_sort_statistici(vector_statistici_B, J);

	// copiem statisticile pentru a nu le pierde cand lucram cu toate
	// meciurile
	for (int i = 1; i <= J; i++) {
		vector_statistici_CA[i] = vector_statistici_A[i];
		vector_statistici_CB[i] = vector_statistici_B[i];
	}
	scanf(" %s[^\n]", cheie);
	if (cheie[0] == '-')
		scanf(" %s[^\n]", comanda);

	// loop-ul pentru lantul de comenzi
	while (comanda[0] != 'Q' && comanda[1] != '\0') {
		char jucator = comanda[0];
		char tip_statistica = comanda[1];
		char index_meci_s[4];
		// spargerea comenzii in parametri
		strncpy(index_meci_s, comanda + 2, 3);
		index_meci_s[3] = '\0';
		char acuratete_s[7];
		strncpy(acuratete_s, comanda + 5, 6);
		acuratete_s[6] = '\0';
		char min_sau_max[4];
		strncpy(min_sau_max, comanda + 11, 3);
		min_sau_max[3] = '\0';
		int index_meci_numar = atoi(index_meci_s);
		double acuratete_cautata = atof(acuratete_s);
		trunchiaza_la_doua_zecimale(&acuratete_cautata);

		// comanda pentru jucatorul 1
		if (jucator == 'O') {
			// verificare meci valid
			if (J < index_meci_numar)
				printf("Nu exista date despre meciul cerut.\n");
			// acuratete pe un meci
			else if (tip_statistica == 'U' && index_meci_numar <= J) {
				// gasim meciul in vectorul sortat
				for (gaseste_meciul = 1;
				     gaseste_meciul <= J &&
				     index_meci_numar != vector_statistici_A[gaseste_meciul].numar_meci;
				     gaseste_meciul++)
					;
				int l_totale = vector_statistici_A[gaseste_meciul].numar_lovituri_totale;
				int l_nimerite = vector_statistici_A[gaseste_meciul].numar_lovituri_nimerite;
				int cnt;
				// ramura MIN
				if (strcmp("MIN", min_sau_max) == 0) {
					double acuratete_curenta = (double)l_nimerite / l_totale * 100;
					trunchiaza_la_doua_zecimale(&acuratete_curenta);
					// adaugam lovituri pana cand conditia este indeplinita
					while (acuratete_curenta < acuratete_cautata) {
						l_nimerite++;
						acuratete_curenta = (double)l_nimerite / l_totale * 100;
						trunchiaza_la_doua_zecimale(&acuratete_curenta);
					}
					// calculam numarul de lovituri extra.
					cnt = l_nimerite - vector_statistici_A[gaseste_meciul].numar_lovituri_nimerite;
				}
				// ramura MAX
				else if (strcmp("MAX", min_sau_max) == 0) {
					double acuratete_curenta = (double)l_nimerite / l_totale * 100;
					trunchiaza_la_doua_zecimale(&acuratete_curenta);
					// scadem din loviturile nimerite pana cand conditia este indeplinita
					while (acuratete_curenta >= acuratete_cautata) {
						l_nimerite--;
						acuratete_curenta = (double)l_nimerite / l_totale * 100;
						trunchiaza_la_doua_zecimale(&acuratete_curenta);
					}
					cnt = vector_statistici_A[gaseste_meciul].numar_lovituri_nimerite - l_nimerite - 1;
					if (cnt == -1)
						cnt++;
				}
				// afisam ceea ce se cere.
				double procent = vector_statistici_A[gaseste_meciul].acuratete_meci * 100;
				procent = floor(procent * 100) / 100.0;
				printf("0%0.2lf.%d\n", procent, cnt);
			}
			// statistica pentru toate meciurile, MAX
			else if (tip_statistica == 'T' && strcmp("MAX", min_sau_max) == 0) {
				// calculam acuratetea totala
				double acc_totala_A = ac_totala(J, vector_statistici_CA);
				trunchiaza_la_doua_zecimale(&acc_totala_A);
				int cnt = 0;
				int K = 1;
				// calculam cate meciuri pot avea acuratetea 0
				while (acc_totala_A >= acuratete_cautata && K <= J) {
					if (vector_statistici_CA[K].acuratete_meci != 0) {
						vector_statistici_CA[K].acuratete_meci = 0;
						cnt++;
					}
					K++;
					acc_totala_A = ac_totala(J, vector_statistici_CA);
					trunchiaza_la_doua_zecimale(&acc_totala_A);
				}
				if (cnt > 0)
					cnt--;
				acc_totala_A = ac_totala(J, vector_statistici_A);
				trunchiaza_la_doua_zecimale(&acc_totala_A);
				printf("0%0.2lf.%d\n", acc_totala_A, cnt);
				// resetam vectorul de statistici
				for (int i = 1; i <= J; i++)
					vector_statistici_CA[i] = vector_statistici_A[i];
			}
			// ramura toate meciurile, MIN
			else if (tip_statistica == 'T' && strcmp("MIN", min_sau_max) == 0) {
				// acuratete totala
				double acc_totala_A = ac_totala(J, vector_statistici_CA);
				trunchiaza_la_doua_zecimale(&acc_totala_A);
				int cnt = 0;
				int K = 1;
				// while pentru determinarea a cate meciuri de 100% e nevoie
				while (acc_totala_A < acuratete_cautata && K <= J) {
					if (vector_statistici_CA[K].acuratete_meci < 1) { 
						vector_statistici_CA[K].acuratete_meci = 1;
						cnt++;
					}
					K++;
					acc_totala_A = ac_totala(J, vector_statistici_CA);
					trunchiaza_la_doua_zecimale(&acc_totala_A);
				}
				acc_totala_A = ac_totala(J, vector_statistici_A);
				printf("0%0.2lf.%d\n", acc_totala_A, cnt);
				for (int i = 1; i <= J; i++)
					vector_statistici_CA[i] = vector_statistici_A[i];
			}
		}
		// ramura jucator 2, identic ca logica si algoritmica dar oglindita
		else if (jucator == 'T') {
			if (J < index_meci_numar)
				printf("Nu exista date despre meciul cerut.\n");
			else if (tip_statistica == 'U' && index_meci_numar <= J) {
				for (gaseste_meciul = 1;
				     gaseste_meciul <= J &&
				     index_meci_numar != vector_statistici_B[gaseste_meciul].numar_meci;
				     gaseste_meciul++)
					;
				int l_totale = vector_statistici_B[gaseste_meciul].numar_lovituri_totale;
				int l_nimerite = vector_statistici_B[gaseste_meciul].numar_lovituri_nimerite;
				int cnt;
				if (strcmp("MIN", min_sau_max) == 0) {
					double acuratete_curenta = (double)l_nimerite / l_totale * 100;
					trunchiaza_la_doua_zecimale(&acuratete_curenta);
					while (acuratete_curenta < acuratete_cautata) {
						l_nimerite++;
						acuratete_curenta = (double)l_nimerite / l_totale * 100;
						trunchiaza_la_doua_zecimale(&acuratete_curenta);
					}
					cnt = l_nimerite - vector_statistici_B[gaseste_meciul].numar_lovituri_nimerite;
				} else if (strcmp("MAX", min_sau_max) == 0) {
					double acuratete_curenta = (double)l_nimerite / l_totale * 100;
					trunchiaza_la_doua_zecimale(&acuratete_curenta);
					while (acuratete_curenta >= acuratete_cautata) {
						l_nimerite--;
						acuratete_curenta = (double)l_nimerite / l_totale * 100;
						trunchiaza_la_doua_zecimale(&acuratete_curenta);
					}
					cnt = vector_statistici_B[gaseste_meciul].numar_lovituri_nimerite - l_nimerite - 1;
					if (cnt == -1)
						cnt++;
				}
				double procent = vector_statistici_B[gaseste_meciul].acuratete_meci * 100;
				procent = floor(procent * 100) / 100.0;
				printf("0%0.2lf.%d\n", procent, cnt);
			} else if (tip_statistica == 'T' && strcmp("MAX", min_sau_max) == 0) {
				double acc_totala_B = ac_totala(J, vector_statistici_CB);
				trunchiaza_la_doua_zecimale(&acc_totala_B);
				int cnt = 0;
				int K = 1;
				while (acc_totala_B >= acuratete_cautata && K <= J) {
					if (vector_statistici_CB[K].acuratete_meci == 0) {
						vector_statistici_CB[K].acuratete_meci = 0;
						cnt++;
					}
					K++;
					acc_totala_B = ac_totala(J, vector_statistici_CB);
					trunchiaza_la_doua_zecimale(&acc_totala_B);
				}
				if (cnt > 0)
					cnt--;
				acc_totala_B = ac_totala(J, vector_statistici_B);
				trunchiaza_la_doua_zecimale(&acc_totala_B);
				printf("0%0.2lf.%d\n", acc_totala_B, cnt);
				for (int i = 1; i <= J; i++)
					vector_statistici_CB[i] = vector_statistici_B[i];
			} else if (tip_statistica == 'T' && strcmp("MIN", min_sau_max) == 0) {
				double acc_totala_B = ac_totala(J, vector_statistici_CB);
				trunchiaza_la_doua_zecimale(&acc_totala_B);
				int cnt = 0;
				int K = 1;
				while (acc_totala_B < acuratete_cautata && K <= J) {
					if (vector_statistici_CB[K].acuratete_meci < 1) { 
						vector_statistici_CB[K].acuratete_meci = 1;
						cnt++;
					}
					K++;
					acc_totala_B = ac_totala(J, vector_statistici_CB);
					trunchiaza_la_doua_zecimale(&acc_totala_B);
				}
				acc_totala_B = ac_totala(J, vector_statistici_B);
				trunchiaza_la_doua_zecimale(&acc_totala_B);
				printf("0%0.2lf.%d\n", acc_totala_B, cnt);
				for (int i = 1; i <= J; i++)
					vector_statistici_CB[i] = vector_statistici_B[i];
			}
		}
		scanf(" %s[^\n]", comanda);
	}

	// eliberare spatiu alocat
	if (vector_statistici_A)
		free(vector_statistici_A);
	if (vector_statistici_B)
		free(vector_statistici_B);
	if (vector_statistici_CA)
		free(vector_statistici_CA);
	if (vector_statistici_CB)
		free(vector_statistici_CB);
	free(cheie);
	vector_statistici_A = NULL;
	vector_statistici_CA = NULL;
	vector_statistici_B = NULL;
	vector_statistici_CB = NULL;
	cheie = NULL;
	return 0;
}
