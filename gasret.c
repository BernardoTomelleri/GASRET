/** \file gasret.c
     \author Bernardo Tomelleri **/
	 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/* siti per lato della matrice */
#define L 10
/* Numero di dimensioni del reticolo (array bidimensionale) */
#define D 2
/* matrice globale in cui ogni elemento rappresenta un sito del reticolo */
int s[L][L];

/* numero particelle della simulazione */
int nparticelle;

/*  vettori globali che raccolgono gli spostamenti di ogni particella per le coordinate x1 e x2 (solo i primi nparticelle valori sono significativi)*/
int X1[L*L];
int X2[L*L];

/* valore di un sito vuoto */
#define EMPTY (-1)


void inizializza(int seed, int n) {
 srand(seed);
 nparticelle = n;
 for (int i = 0; i < L; i++) {
  for (int j = 0; j < L; j++) { 
    s[i][j] = EMPTY;
  }
 }
 for (int i=0; i<L*L; i++) {
   X1[i] = 0;
   X2[i] = 0;
  }
 /*Inizializzato il Reticolo Vuoto,
 procede a popolare siti scelti pseudocasualmente con n particelle*/
 int p=0;
 while (p < nparticelle) {
   int pseudo_1 = rand() % L;
   int pseudo_2 = rand() % L;
  if (s[pseudo_1][pseudo_2] == EMPTY) 
   s[pseudo_1][pseudo_2] = p++;  
 }
}

/*stampa il contenuto del reticolo*/
void stampa_reticolo(void){
  int i, j;
  for (i = 0; i < L; i++) {
    for(j = 0; j < L; j++) {
      if (s[i][j] == EMPTY)
        printf("(EMPTY) ");
      else
        printf ("(%5d) ", s[i][j]);
    }
    printf("\n");
  } 
}

/* Funzione che ritorna 1 se la posizione i, j del reticolo è vuota */
int vuota (int i, int j) {
	if (s[i][j] == EMPTY)
		return 1;
	else
		return 0;
}

int sposta (int i, int j, int direzione) {
	/*
	sposta si aspetta che s[i][j] contenga una particella,
	prova a spostarla nella direzione indicata, se ci riesce
	ritorna 1.
	*/
	//  direzione assume valori a partire da 1 (= spostamento a destra) fino a 4 (in su) 
	// in senso orario.
	int nuovo_i = i;	//                            					   ^
	int nuovo_j = j;	//							  					   4		
	int incX1 = 0;		//	misurano incremento ( o decremento)	  < 3 [particella] 1 >
	int incX2 = 0;		//  di X1 e X2 della particella                    2
	int particella;		//                            					   v
	switch(direzione) {
		case 1:
		nuovo_j++; //aumenta la colonna
		incX1++; //va a destra
		break;
		case 2:
		nuovo_i++; //aumenta la riga
		incX2--; //va in basso
		break;
		case 3:
		nuovo_j--; //diminuisce la colonna
		incX1--; //va a sinistra
		break;
		case 4:
		nuovo_i--; //diminuisce la riga
		incX2++; //va in alto
	} /* Eccezioni se la particella si trova al bordo del reticolo */
	if (nuovo_j > L-1) nuovo_j = 0; //bordo destro => bordo sinistro
	if (nuovo_i > L-1) nuovo_i = 0; //bordo in fondo => bordo in cima
	if (nuovo_j < 0) nuovo_j = L-1; //bordo sinistro => bordo destro
	if (nuovo_i < 0) nuovo_i = L-1; //bordo in cima => bordo in fondo
	if (vuota(nuovo_i, nuovo_j)) { 	//Lo spostamento avviene se il sito prossimo scelto è vuoto
		particella = s[nuovo_i][nuovo_j] = s[i][j];
		s[i][j] = EMPTY; //si svuota il sito originale della particella
		X1[particella] += incX1; // X1 e X2 della particella aumentano dell'incremento corrispondente
		X2[particella] += incX2; // alla direzione scelta 
		return 1;
	}
	return 0; //caso non vuoto non entra in if..
}

//stampa solo la porzione significativa (da 0 a nparticelle -1) dei valori negli array X1 e X2 su standard output

void stampa_X1X2(void){
	printf("%s", "X1 = ");
	for (int i=0; i<nparticelle; i++) {
		printf("%2d ", X1[i]);
	}
	printf("\n%s", "X2 = ");
	for (int i=0; i<nparticelle; i++) {
		printf("%2d ", X2[i]);
	}
	printf("\n");
}
/* La funzione step sceglie casualmente una particella e genera una direzione tra 1 e 4, 
   chiama sposta per la manipolazione degli Array globali,  
   ritorna 1 se sposta ha cambiato la matrice, 0 altrimenti.  */
int step(void) {
  int i = rand()%L;
  int j = rand()%L;
  int dir = 1 + (rand() % 4);
 if(! vuota(i, j)){
	return sposta(i, j, dir);
  } 
  return 0;
}

/* delta calcola la distanza quadratica percorsa da una particella 
    a partire dai vettori X1 e X2 (eq. 1 nel documento PDF). 
   ritorna la distanza calcolata
*/ 
double delta(int n) { //n è la particella di cui vogliamo calcolare la distanza quadratica media
	int sommatoria;
	if(n < nparticelle) {
	sommatoria = (X1[n] * X1[n]) + (X2[n] * X2[n]);
	return sommatoria;
	}
	return 0;
}
/* calcola lo spostamento quadratico medio 
    a partire dai vettori X1 e X2 (eq. 2 nel documento PDF)
    X1 e X2 sono il frutto di una precedente simulazione
   \retval x lo spostamento quadratico medio
*/ 
double spostamento_quadratico_medio (void) {
	int n, sigma = 0;
	for (n = 0; n < nparticelle; n++) {
		sigma += delta(n);
	}
	return (sigma / nparticelle);
}
/* calcola la simulazione per n particelle fino al tempo t e ritorna
il coefficente di diffusione approssimato fino a t (eq. 3 nel documento PDF)
*/ 
double approssima_diffusione (int seed, int t, int n) {
	inizializza (seed, n); //n è il numero delle particelle da inserire nel reticolo
	int i;
	double diff;
	/*esegue step per ogni incremento dell'unità di tempo, sino al tempo t in cui termina la simulazione*/
	for (i = 0; i < t; i++) { 
		step();
	}
	diff = spostamento_quadratico_medio() / (2 * D * t);
	return diff;
}


  