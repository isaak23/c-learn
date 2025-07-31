# Corso C Microchip

## Tipi di variabili

| Tipo         | Dimensione (byte) | Intervallo di valori                           | Esempio di dichiarazione |
|--------------|-------------------|-----------------------------------------------|--------------------------|
| `char`       | 1                 | -128 a 127 oppure 0 a 255 (se unsigned)       | `char c = 'A';`          |
| `short`      | 2                 | -32,768 a 32,767 oppure 0 a 65,535 (unsigned) | `short s = 1000;`        |
| `int`        | 4                 | -2,147,483,648 a 2,147,483,647                | `int i = -42;`           |
|              |                   | oppure 0 a 4,294,967,295 (unsigned)           | `unsigned int ui = 10;`  |
| `long`       | 4 o 8             | -2,147,483,648 a 2,147,483,647 (32-bit)       | `long l = 123456L;`      |
|              |                   | o -9,223,372,036,854,775,808 a 9,223,372,036,854,775,807 (64-bit) | `unsigned long ul = 123UL;` |
| `long long`  | 8                 | -9,223,372,036,854,775,808 a 9,223,372,036,854,775,807 | `long long ll = 123456789LL;` |
|              |                   | oppure 0 a 18,446,744,073,709,551,615 (unsigned) | `unsigned long long ull = 123ULL;` |
| `float`      | 4                 | ~1.2E-38 a ~3.4E+38 (6-7 cifre decimali)      | `float f = 3.14f;`       |
| `double`     | 8                 | ~2.3E-308 a ~1.7E+308 (15-16 cifre decimali)  | `double d = 3.14159;`    |
| `long double`| 8, 10, 12 o 16    | Intervallo e precisione estesi                 | `long double ld = 3.1415926535L;` |
| `_Bool`      | 1                 | 0 (false) o 1 (true)                           | `_Bool b = 1;`           |


| Tipo               | Dimensione (bit) | Intervallo di valori                                    | Esempio di dichiarazione       |
|---------------------|------------------|--------------------------------------------------------|--------------------------------|
| **Tipi interi esatti** (con segno)                                              |
| `int8_t`            | 8                | -128 a 127                                             | `int8_t x = -42;`              |
| `int16_t`           | 16               | -32,768 a 32,767                                       | `int16_t y = 1024;`            |
| `int32_t`           | 32               | -2,147,483,648 a 2,147,483,647                         | `int32_t z = 1000000;`         |
| `int64_t`           | 64               | -9,223,372,036,854,775,808 a 9,223,372,036,854,775,807 | `int64_t w = 1e18;`            |
| **Tipi interi esatti** (senza segno)                                            |
| `uint8_t`           | 8                | 0 a 255                                                | `uint8_t ux = 0xFF;`           |
| `uint16_t`          | 16               | 0 a 65,535                                             | `uint16_t uy = 65535;`         |
| `uint32_t`          | 32               | 0 a 4,294,967,295                                      | `uint32_t uz = 4000000000U;`   |
| `uint64_t`          | 64               | 0 a 18,446,744,073,709,551,615                         | `uint64_t uw = 1e19U;`         |
| **Tipi interi minimi** (≥ dimensione specificata)                               |
| `int_least8_t`      | ≥8               | Come sopra, ma dimensione minima garantita             | `int_least8_t a = 127;`        |
| `uint_least16_t`    | ≥16              |                                                        | `uint_least16_t b = 65535;`    |
| **Tipi interi più veloci** (≥ dimensione specificata, ottimizzati per velocità) |
| `int_fast8_t`       | ≥8               | Come sopra, ma ottimizzati per prestazioni             | `int_fast8_t c = 100;`         |
| `uint_fast32_t`     | ≥32              |                                                        | `uint_fast32_t d = 1e9;`       |
| **Tipi per puntatori**                                                         |
| `intptr_t`          | ≥16              | Intero con segno in grado di memorizzare un puntatore  | `intptr_t p = (intptr_t)&x;`   |
| `uintptr_t`         | ≥16              | Intero senza segno per puntatori                       | `uintptr_t up = (uintptr_t)&y;`|
| **Tipo massimo**                                                                |
| `intmax_t`          | ≥64              | Il più grande tipo intero con segno supportato         | `intmax_t big = 1e20;`         |
| `uintmax_t`         | ≥64              | Il più grande tipo intero senza segno supportato       | `uintmax_t ubig = 1e20U;`      |

## Operatori logici

```bash
&& AND
|| OR
! NOT
```

## Operazioni bit a bit

Immaginiamo di avere il seguente codice

```bash
char x = 0b00001011;
char y = 0b00000101;
char answer;

void main(void) {
  answer = x & y ; // AND 0b00000001
  answer = x | y ; // OR 0b00001111
  answer = x ^ y ; // XOR 0b00001110
  answer = ~ y ; // NOT 0b11111010
}
```

in embedded spesso si usa la maschera, ovvero una variabile che magari ha solo l'ultimo bit a 1 e se io faccio una & con un'altra variabile ottengo che non modificherò solo l'ultimo bit

```bash
char x = 0b00001011;
char mask = 0b00000001;

void main(void) {
  answer = x & mask ; // AND 0b00000001
}
```
questo mi torna comodo nel caso volessi controllare solo un particolare bit di un registro.

## Shift
sono gli operatori >> e << facciamo qualche esempio

```bash
char x = 0b00001011;
char y ;

void main(void) {
  y = x << 1; // 0b00010110 scorro tutta la sequenza verso sinistra, da un punto di vista matematico ho moltiplicato per 2 (0b00001011 = 0d11 mentre 0b00010110 = 0d22 )
}
```
va da se che lo shift destro divide per 2.

Attenzione allo shift destro perché i numeri con segno potrebbero venire influenzati dallo spostamento.

## Casting
Nel mondo embedded il casting è importante perché non abbiamo molto spazio, quindi fa comodo imporre i tipi di variabili che vogliamo

```bash
newType = (type)variable;
```

## Switch Statement

```bash
switch (expression) {
  const-expr1: statement1
  break;
  .
  .
  .
  const-exprN: statementN
  break;
  default: statementN+1
}
```

## Classi di variabili
Ci sono 4 classi di variabili
- static
- automatic
- external
- register

### 1. Static
le variabili statiche sono 
- permanenti
- lifetime infinito
per le global non c'è bisogno di dichiararlo esplicitamente mentre dentro una funzione devo dichiararlo esplicitamente come

```bash
static int x = 5;
```
Posso dichiarare anche una funzione static, in questo caso la funzione dichiarata static è visibile solo nel file in cui è dichiarata, quella funzione non potrà essere visibile ad altri file se non tramite un'altra funzione

```bash
altroFile.c
int x;

//funzione visibile anche ad altri file
int foo(x) {
  bar(x);
}
//funzione visibile solo a questo file
static int bar(x){...}
```


### 2. Automatic
Sono le variabili dentro una funzione, e hanno una vita limitata all'uso della funzione

### 3. External
Si tratta di variabili dichiarate in un altro file ma inizializzate nel fle dove sto lavorando. Ovviamente nell'altro file la mia variabile è dichiarata a livello globale

Es.

```bash
main.c
extern int variabileEsterna = 5;
```

```bash
altrofile.c
int variabileEsterna;
```

### Array
Per dichiarare un array

```bash
type array[size];
```
Posso omettere la dimensione se dichiaro anche il contenuto dell'array, in genere i compilatori se ne accorgono
```bash
int array[] = {5,3,6,9,2};
```
Posso anche dichiarare degli array multidimensionale utili per matrici o altro
```bash
type array[size1][size2]
```
Bisogna ricordarsi sempre che un array di caratteri, ovvero una stringa, l'ultimo elemento è "/0" quindi "ciao" sarà un array di 5 elementi dove l'ultimo è "/0".
Altro elemento di attenzione è che il C non supporta direttamente le stringhe, ma solo come array di char

### Puntatori

Per i puntatori rimando al README principale, ricordo solo che un array è già automaticamente un puntantore al primo elemento dell'array, quindi in caso volessi associare un array ad un altro puntaotre mi basterebbe fare

```bash
int x[] = {1,2,3,4}
p = x // questo a volte è ingannevole, fa pensare solo ad una variabile
p = &x // almeno questo ti fa capire che un puntatore
p = &x[0] // questo è ancora più esplicito
```

incrementando il puntatore posso scorrere gli elementi dell'array.

Se voglio deferenziare un array devo specificare il primo elemento, in questo modo

```bash
y = *p[0]
```

# Advanced C

## Structures
Una struttura può contenere ogni tipo di dato, facciamo subito un esempio

```bash
struct complex {
  float re; //parte reale del numero complesso
  float im; //parte immaginaria
} x,y; //ho dicharato due variabili x e y di tipo complex
```
posso anche dichiararle così
```bash
struct complex {
  float re; //parte reale del numero complesso
  float im; //parte immaginaria
};

struct complex x,y;
```

Posso accedere ai campi della struct con la . notation

```bash
struct complex {
  float re; //parte reale del numero complesso
  float im; //parte immaginaria
} x,y; //ho dicharato due variabili x e y di tipo complex

int main(void)  {
  x.re = 1.25;
  x.im = 2.52;
  y = x // assegno alla struttura y i valori della struttura x
  return 0;
}
```
Posso creare un tipo direttamente con la struttura con typedef, così è più rapido
```bash
typdef struct{
  float re;
  float im;
} complex

complex x = {1.25,2.50}; //così facendo ho anche assegnato già valori a re e im della struttura
complex y;
```

Molto utile creare struct di bit fields, posso assegnare il numero di bit ad ogni campo che mi interessa

```bash
typedef struct{
  int bit1: 1; // ho un solo bit quindi 1
  int bit2to4: 3; // qui mi servono 3 bit, i bit 2,3 e 4 quindi metto 3 bit
  int bit5: 1;
  int bit6to8: 3; // altri 3 bit quindi il massimo numero che posso dare è 7 (da 0 a 7 con 3 bits)
} byteBits;
```

## Unions
Le Unions sono come le struct con la differenza che gli elementi della union condividono lo stesso spazio di memoria e la memoria della union coincide ovviamente con l'elemento più grande. 
Le union tornano comode se ho valori che arrivano da diversi registri o input e poi li devo concatenare

## Puntatori a Struct e Union
Posso anche dichiarare puntatori a struct e union, per memorizzre un valore dentro una struct posso usare l'operatore -> mentre per accedere posso usare sempre il punto.
Es.

```bash
#include <stdio.h>

//definisco la struttura
typedef union {
  unsigned long longVariable;
  struct {
    unsigned char var1;
    unsigned char var2;
    unsigned char bitvar: 2;
    unsigned char var3;
  } member;
} NEW_TYPE;

//dichiaro una variabile del tipo dichiarato sopra
NEW_TYPE newType;

//dichiaro un puntatore alla struttura
NEW_TYPE *pnewType = &newType;


int main(int argc, char** argv) {
  
    pnewType->longVariable = 0xABCDECFF; // in questo modo assegno alla variabile puntata dal puntatore un valore, devo conoscere la struttura

  printf("dentro longvariable trovo: %lu \n",newType.longVariable); // in decimale
  printf("dentro var trovo: %d \n",newType.member.var1); // in decimale
  printf("dentro var trovo: %d \n",newType.member.var2); // in decimale
  printf("dentro var trovo: %d \n",newType.member.bitvar); // in decimale
  printf("dentro var trovo: %d \n",newType.member.var3); // in decimale
  printf("\n");

  printf("dentro longvariable trovo: %lx \n",newType.longVariable); // in esadecimale
  printf("dentro var trovo: %x \n",newType.member.var1); // in esadecimale
  printf("dentro var trovo: %x \n",newType.member.var2); // in esadecimale
  printf("dentro var trovo: %b \n",newType.member.bitvar); // in esadecimale, prendo solo i primi due bit di cd che convertito in binaro è appunto 11001101 quindi ha preso l'ultimo 1, io nella variabile ho messo solo due bit, se metto FF al posto di CD leggerò qui 11 e sopra 3 in decimale
  printf("dentro var trovo: %x \n",newType.member.var3); // in decimale
  return 0;
}
```
Posso anche creare strutture dentro strutture, ma in quel caso devo dichiarare le strutture interne alla struttura madre come volatile.

Ricordiamo che quando dichiaro un puntatore tutto quello a sinistra dell'asterisco * indica il tipo di dato indicato dal puntatore e tutto quello a destra dell'asterisco * è riferito al puntatore stesso.

Altra cosa importante è che a volte alcuni aspetti dipendono dal compilatore usato, ad esempio un compilatore potrebbe salvare di defaul le stringhe in flash invece che in RAM.

## Array di puntatori

Se scrivo questo:
```bash
char *const p[4] = {"a01", "b02", "c03", "d04"};
```
ho creato dei puntatori costanti (cioè gli indirizzi memorizzati nei puntatori sono salvati in flash) con il loro contenuto che è potenzialmente modificabile (ma attenzione sono in flash).

Se scrivo:
```bash
const char *q[4] = {"e01", "f02", "g03", "h04"};
```
Ho creato dei puntatori modificabili (cioè gli indirizzi salvati nei puntatori sono modificabili e salvati in RAM) mentre il loro contenuto sono costanti e salvati in flash, non sono modificabili.

Per vedere cosa contengono gli array è possibile fare questi cicli for
```bash
#include <stdio.h>

unsigned char i = 0, j = 0, y;
char *const p[4] = {"a01", "b02", "c03", "d04"};
const char *q[4] = {"e01", "f02", "g03", "h04"};


int main(int argc, char **argv) {
  //Step through p[ ] pointer       
        for(i = 0; i < 4; i++, j=0)
        {
           do{
               y = *(p[i] + j);
             printf("%c\n",y);
               j++;
           } while(y != '\0'); //esco da questo while quando incontro lo /0 di fine array, quindi la j mi server per andare avanti nella stringa presente in ogni elemento dell'array, se incontro /0 esco dal while e il for può passare a i=1 e rimettendo j=0 in modo tale da scandire la seconda stringa
        }

  //Step through q[ ] pointer      
        for(i = 0; i < 4; i++, j=0)
        {
           do{
               y = *(q[i] + j);
                printf("%c\n",y);
               j++;
           } while(y != '\0');
        }
}
```

## Array di struct e union

Posso mettere in un array anche struc e union, facciamo un esempio

```bash
#include <stdio.h>

typedef struct {
  float re;
  float im;
} complex;

complex a[3] ={{2.5,3},{4,1.5},{2,4.6}};
```
Per accedere agli elementi uso la solita dot notation

```bash
a[0].re = 1.4;
```
Ovviamente posso anche creare dei puntatori a queste strutture
```bash
typedef struct {
  float re;
  float im;
} complex;
complex a[2]; //dichiaro l'array
complex *p_a[2] = {&a[0],&a[1]}; //referenzio gli elementi nel puntatore
complex *singlePointer_a = &a[0]; //posso anche passare solo il primo elemento, ma poi devo ricordarmi di incrementare il valore del puntatore con ++ per accedere agli altri elementi, visto che non ho l'indice
```
Se volessi scrivere una funzione che prende in argomento questo puntatore e che magari gli assegna dei valori posso fare così

```bash
int functionName(complex *p_struct[]) {
  unsigned char j;
  for(j=0,j<2,j++) {
    p_struct[j]->re = 1.25;
    p_struct[j]->im = 2.50;
  }
}
```
Per chiamare la funzione posso fare:
```bash
functionName(&a[0]); //passo direttamente l'indirizzo dell'elemento dell'array
functionName(p_a[0]); //passo il puntatore con l'indice
functionName(singlePointer_a); //passo il single pointer, poi però per passare all'elemento dopo devo fare singlePointer_a++
```

## Function Pointers
I puntatori possono essere usati anche per puntare funzioni
la dichiaro così:

```bash
int (*fp)(int x);
```
ho dichiarato un puntaotre a funzione di nome fp, i puntatori a funzione possono restituire un solo valore ma possono avere più argomenti.

```bash
int (*fp)(int x); //dichiaro il puntatore
int foo(int x); // dichiaro la funzione
fp = &foo; // assegno la funzione al puntatore
```
Ecco un esempio concreto
```bash
int x,y;
int add(int a, int b);
int sub(int a, int b);

int foobar(int a, int b, int (*fp)(int,int)) {
return fp(a,b);
}

void main(void) {
  x = foobar(5,12,&add);
  y = foobar(5,12,&sub);
}
```
