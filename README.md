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
