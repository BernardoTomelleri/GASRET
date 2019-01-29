# GASRET
Studio della diffusione di un gas di particelle libere in un reticolo quadrato di due dimensioni, D = 2: Il reticolo ha un numero totale di siti V dato dal quadrato del numero di siti per dimensione (V = L^2).
I siti del reticolo sono occupati da N particelle che vengono collocate casualmente sul reticolo all’inizio della simulazione. Ogni particella è numerata (da 0 a  N − 1) e mantiene la sua identita. Ad ogni passo della simulazione viene selezionata casualmente una delle particelle, che sceglie ancora casualmente uno dei 4 siti adiacenti su cui spostarsi. Se il sito scelto è vuoto, la particella si sposta nel nuovo sito, liberando quello in cui si trova, altrimenti la situazione rimane invariata. Il reticolo che utilizziamo ha condizioni periodiche di bordo, ovvero una particella che esce dal lato destro rientra dal lato sinistro, e lo stesso accade per il
bordo superiore e inferiore. In particolare, la simulazione inizia all’istante t = 0 e per passare dall’istante t all’istante t + 1 si effettuano i seguenti passi:

1. si sceglie uniformemente a caso una particella α di coordinate (x1(t), x2(t));
2. si sceglie uniformemente a caso uno dei siti primi vicini di α (uno dei 4 siti che si ottengono aggiungendo o sottraendo 1 a x1(t) o a x2(t) tenendo conto delle condizioni periodiche di bordo);
3. se il sito scelto e vuoto spostiamo α nel sito scelto liberando la posizione originaria;
4. incrementiamo il tempo trascorso di una unita (questo accade indipendentemente dal fatto che si sposti o meno al passo precedente).

La distanza quadratica percorsa dalla particella α-esima puo essere rappresentata come il quadrato della somma degli spostamenti da lei compiuti lungo i due assi a partire dal tempo 0, ovvero:

![equation](https://latex.codecogs.com/gif.latex?%5CDelta%20R_%5Calpha%20%5E%7B2%7D%20%28t%29%20%3D%20%5Cleft%28%20%5Csum_%7Bi%3D0%7D%5E%7Bt-1%7Ds_1%28i%29%20%5Cright%29%5E2%20&plus;%5Cleft%28%20%5Csum_%7Bi%3D0%7D%5E%7Bt-1%7Ds_2%28i%29%20%5Cright%29%5E2)  
dove s1(i) e s2(i) sono rispettivamente gli spostamenti (+1 o -1) sull’asse x e y effettuati al tempo i da α.
Definiamo lo spostamento quadratico medio del sistema a partire dalle medie rispetto alle N particelle come:

![equation](https://latex.codecogs.com/gif.latex?%5CDelta%20R%20%5E%7B2%7D%20%28t%29%20%3D%20%5Cfrac%7B1%7D%7BN%7D%20%5Csum_%7B%5Calpha%3D0%7D%5E%7BN-1%7D%5CDelta%20R_%5Calpha%20%5E%7B2%7D%28t%29)

La grandezza che ci interessa stimare, data una certa densita ρ = N/V, e il coefficiente di diffusione, che e definito da:

![equation](https://latex.codecogs.com/gif.latex?%5Cmathcal%20D%20%28%5Crho%29%20%3D%5Clim_%7Bt%20%5Cto%20&plus;%5Cinfty%7D%5Cmathcal%20D%20%28%5Crho%2Ct%29%20%3D%5Clim_%7Bt%20%5Cto%20&plus;%5Cinfty%7D%20%5Cfrac%7B1%7D%7B2Dt%7D%20%5Cleft%28%20%5CDelta%20R%20%5E%7B2%7D%28t%29%20%5Cright%29)

Questo si puo fare simulando l’andamento per un tempo T abbastanza grande da approssimare l’andamento al limite. Al crescere della densità, il coefficiente di diffusione diminuisce poiché per le particelle diventa sempre più difficile muoversi: in particolare, un reticolo pieno risulta completamente bloccato.

