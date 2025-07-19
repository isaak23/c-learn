# Corso c

Per questo corso userò linux e vi come IDE, in maniera molto old school 

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
