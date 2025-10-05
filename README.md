# Corso c

Per questo corso userò linux e vi come IDE, in maniera molto old school 

## Appunti VIM
### Comandi base
:w	Salva il file (Write).
:q	Esci da Vim (Quit). Fallisce se ci sono modifiche non salvate.
:wq	Salva ed Esci (Write and Quit). Equivalente a :x.
:q!	Esci senza salvare (Quit forcefully). Ignora le modifiche non salvate.
:set nu	Attiva la numerazione delle righe.
:set nonu	Disattiva la numerazione delle righe.
:help parola_chiave	Apre il manuale di Vim per la parola chiave specificata.

### Modalità inserimento
i	Entra in Modalità Inserimento prima del cursore.
a	Entra in Modalità Inserimento dopo il cursore (Append).
o	Apre una nuova riga sotto quella corrente e va in Modalità Inserimento.
I	Entra in Modalità Inserimento all'inizio della riga.
A	Entra in Modalità Inserimento alla fine della riga.
O	Apre una nuova riga sopra quella corrente e va in Modalità Inserimento.

### Movimento del cursore
h	Sposta il cursore a sinistra.
j	Sposta il cursore in basso (riga successiva).
k	Sposta il cursore in alto (riga precedente).
l	Sposta il cursore a destra.
w	Salta all'inizio della prossima parola.
b	Salta all'inizio della parola precedente (Back).
e	Salta alla fine della parola corrente.
0 (zero)	Sposta il cursore all'inizio della riga.
$	Sposta il cursore alla fine della riga.
gg	Sposta il cursore alla prima riga del file.
G	Sposta il cursore all'ultima riga del file.
:n	Salta alla riga con il numero n (es. :50 per la riga 50).

### Modifica e cancellazione
u	Annulla l'ultima azione (Undo).
Ctrl + r	Ripristina l'azione annullata (Redo).
x	Cancella il carattere sotto il cursore.
dd	Cancella (taglia) l'intera riga.
dw	Cancella la parola (Delete Word).
D	Cancella dal cursore fino alla fine della riga.
yy	Copia (yank) l'intera riga.
yw	Copia la parola (Yank Word).
p	Incolla il testo dopo il cursore o la riga (Paste).
P	Incolla il testo prima del cursore o la riga.
r	Sostituisce un singolo carattere.
J	Unisci la riga corrente con quella successiva.

### Ricerca e sostituzione
/pattern	Cerca la stringa "pattern" in avanti.
?pattern	Cerca la stringa "pattern" all'indietro.
n	Ripete la ricerca nella stessa direzione.
N	Ripete la ricerca nella direzione opposta.
:%s/vecchio/nuovo/g	Sostituisce tutte le occorrenze di "vecchio" con "nuovo" in tutto il file (Globalmente).
:s/vecchio/nuovo/g	Sostituisce tutte le occorrenze solo sulla riga corrente.
:%s/vecchio/nuovo/gc	Sostituisce in tutto il file, ma chiede conferma per ogni occorrenza.

## Lesson 1

Per prima cosa devo installare il compilatore sulla macchina, per farlo eseguo il comando:

```bash
sudo apt install gcc
```

Poi per compilare il mio programma faccio:

```bash
cc hello world.c
```

Se non ci sono errori nel programma verrà creato il file `a.out`

```bash
clearn$ ls -la
total 28
drwxr-xr-x 2 dansolo dansolo  4096 May 18 09:44 .
drwxr-x--- 4 dansolo dansolo  4096 May 18 09:44 ..
-rwxr-xr-x 1 dansolo dansolo 15968 May 18 09:44 a.out
-rw-r--r-- 1 dansolo dansolo    83 May 18 09:44 hello_world.c
```

A questo punto posso avviare il mio programma con:


```bash
./a.out
```

Se voglio vedere il file binario generato posso fare il comando:


```bash
hexdump -C a.out
```

Se invece voglio vedere il file assembly generato dal mio programma posso fare:

```bash
cc -S hello_world.c
```

Verrà generato il file `hello_world.s` che contiene l'assembly che poi posso vedere con il classico `cat hello_world.s`

### Ottimizzazione

Se voglio che il mio programma venga compilato in maniera più efficiente posso inserire il paramentro -02 durante la compilazione, ad esempio al posto di una `printf` il compilatore potrebbe inserire una `puts` che è molto più efficiente

```bash
cc -02 hello world.c
```

Per controllare il manuale del c (ad esempio la puts) per le varie funzioni posso invocare tramite terminale

```bash
man 03 puts
```


## Lesson 2

Per chiedere al compilatore di mostrare warning eplicitamente posso fare 

```bash
cc -02 -W -wall hello world.c
```

## Lesson 3

Niente di rilevante

## Lesson 4

### I Tipi
Il tipo int potrebbe avere dimensioni diverse a seconda della macchina su cui sto eseguendo il C

```bash
int x =5;
sizeof(x)
```
Se ottengo 4 byte ho 2^32

posso usare anche:

```bash
#include <limits.h>
int x = 5;
printf("int min %d, int max %d\n",INT_MIN, INT_MAX);
```

```bash
Char c = 1; //intero di 8 bit
short // 2 byte
int // 4 byte
long // il long può contenere un indirizzo di memoria di un sistema a 64 bit
long 
```

ci sono anche altri tipi inclusdi nella libreria

```bash
#include <stdint.h>
```

posso vedere l'hexdump di un comando unix (esempio il comando clear che pulisce lo schermo)con il comando

```bash
clear | hexdump -C
```

posso visualizzare la tabella ASCII con:

```bash
man ascii
```

## Lesson 9
In questa lezione iniziamo i puntatori

un esempio di puntatore a intero 

```bash
int x = 5;
int *p = &x
```

in questo modo metto l'indirizzo assegnato alla variabile x dentro il puntatore p

se faccio una funzione del tipo 

```bash
void func(int *p) {
  *p = *p + 1;
}
```

praticamente sto passando l'argomento come puntatore e ne sto modicando il contenuto, ovviamente l'indirizzo puntato sarà sempre lo stesso.
Potrei anche passare alla funzione direttamennte &x anzichè creare il puntatore e poi assegnargli il valore dell'indirizzo di x,

Esempio:

```bash
int x = 5;

void func(int *p) {
  *p = *p + 1;
}

int main(void) {
 func(&x);
 return 0;
}
```
Alla fine se ci pensi hai solo saltato un passaggio ma il risultato è lo stesso.

posso scrivere un puntatore sia come
p[0] che *p, non cambia nulla

Ogni puntatore è un numero di lunghezza pari al bus indirizzi del processore.

In C ogni array è già un puntatore, il nome dell'array è un puntatore a quella struttura, infatti se io faccio:
```bash
char mystr[] = "Hello world";
char *p = mystr;
```
Si vede che non ho usato &mystr per associare l'indirizzo al puntatore, questo perché mystr è già un puntatore.
Ricordiamo che un puntatore punta solo al primo elemento, nel caso della stringa posso accedere ai vari elementi trattando il puntatore come un array, alla fine di ogni array ricordiamo che c'è sempre uno 0 che indica la fine della stringa
