/* 
\file
  \authors informatica (CDS Fisica) 2017/18
  \brief intestazione delle funzioni da implementare
 */

/* protezione inclusioni multiple */
#ifndef __GASRET__H
#define __GASRET__H


/* siti per lato della matrice */
#define L 10

/* matrice globale in cui ogni elemento rappresenta un sito del reticolo */
int s[L][L];

/* numero particelle della simulazione */
int nparticelle;

/*  vettori globali che raccolgono gli spostamenti di ogni particella per le coordinate x1 e x2 (solo i primi nparticelle valori sono significativi)*/
int X1[L*L];
int X2[L*L];

/* valore di un sito vuoto */
#define EMPTY (-1)




/* inizializza la simulazione:
   la matrice s globale con n particelle distribuite in modo uniforme e i vettori X1 ed X2 a 0

   \param seed il seme della generazione casuale
   \param n numero delle particelle da inserire

   \SPECIFICA
   1) la matrice s[][] che rappresenta il reticolo viene inizializzata assegnando EMPTY ad ogni elemento
   2) il generatore psudocasuale viene inizializzato fissando il seme a seed 
   3) le particelle identificate da 0...n-1 vengono assegnate a n siti la cui posizione e' generata casualmente con distribuzione uniforme
*/
void inizializza (int seed, int n);

/* stampa il reticolo s sullo standard output utilizzando il carattere spazio (EMPTY) per le posizioni vuote e l'intero corrispondente per le posizioni piene
*/
void stampa_reticolo (void);
	
/* stampa i valori negli array X1 e X2 su standard output con formato
X1 = 3 -2 8 -9.....
X2 = ....
  NOTA: stampa solo la porzione significativa (da 0 a nparticelle -1)
*/
void stampa_X1X2 (void);

/** calcola un singolo passo della simulazione
 
   1. sceglie casualmente una delle particelle
   2. sceglie casualmente uno dei 4 siti primi vicini tenendo conto delle 
   condizioni periodiche di bordo
   3. se il sito scelto è vuoto la particella si sposta liberando il 
   sito occupato precedentemente
   4. se il sito scelto è pieno non modifica la matrice globale s

  Se effettua lo spostamento aggiorna i vettori X1 e X2 sommando +1 o -1 
  a seconda degli spostamento sui due assi come spiegato nel documento PDF

   \retval 1 se lo spostamento e' stato effettuato
   \retval 0 altrimenti
*/ 
int step (void);

/** calcola la distanza quadratica percorsa da una particella 
    a partire dai vettori X1 e X2 (eq. 1 nel documento PDF). 
    X1 e X2 sono il frutto di una precedente simulazione
   \param n la particella di cui vogliamo calcolare la distanza quadratica media

   \retval x la distanza calcolata
*/ 
double delta (int n);

/** calcola lo spostamento quadratico medio 
    a partire dai vettori X1 e X2 (eq. 2 nel documento PDF)
    X1 e X2 sono il frutto di una precedente simulazione
   \retval x lo spostamento quadratico medio
*/ 
double spostamento_quadratico_medio (void);

/** calcola la simulazione per n particelle fino al tempo t e restituisce il coefficente di diffusione approssimato fino a t (eq. 3 nel documento PDF)
   \param seed seme per la generazione casuale
   \param n il numero delle particelle da inserire nel reticolo 
   \param t il tempo a cui termina la simulazione 

   \retval x il coefficiente di diffusione approssimato al tempo t
*/ 
double approssima_diffusione (int seed, int t, int n);



#endif
