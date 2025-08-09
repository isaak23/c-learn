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
Ecco un esempio concreto:
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
Ovviamente posso anche fare array di function pointers:
```bash
int  (*funPtr[3])(int a) {&function1,&function2,&function3}; //se voglio mettere tutto in RAM
int  (*const funPtr[3])(int a) {&function1,&function2,&function3}; //se voglio mettere tutto in FLASH
```

## State Machines
Prima di parlare di macchine a stati ricoridamo le enum:
```bash
//primo modo
enum typename {label0,label1,...,labelN} varname1, varname2 ;
enum weekday {monday, tuesday, wednesday, thursday, friday, saturnday, sunday}

//con typedef, sicuramente più comodo
typedef enum {monday, tuesday, wednesday, thursday, friday, saturnday, sunday} weekday;
weekday day;
```
nell'esempio monday sarà 0, tuesday 1 e così via.

Le macchine a stati si possono realizzare con gli switch case oppure con i puntatori a funzione, questa seconda opzione è più flessibile, ecco un esempio:

```bash

//creo una enum per tenere traccia degli stati
typedef enum
{
    STATE0 = 0,
    STATE1,
    STATE2
} SYSTEM_STATE;

SYSTEM_STATE gSystemState;

//creo le 3 funzioni per i 3 stati, verranno usate tramite putatori
unsigned int function1(unsigned int InputBits, SYSTEM_STATE *State)
{
   (*State)++;

   if(InputBits == 0 && *State > 1)
      return InputBits;
   else
      return 99;
}

unsigned int function2(unsigned int InputBits, SYSTEM_STATE *State)
{
   (*State)++;

   if(InputBits == 2 && *State > 1)
      return InputBits * InputBits;
   else
      return 88;
}


unsigned int function3(unsigned int InputBits, SYSTEM_STATE *State)
{
   (*State)++;

   if(InputBits == 0 && *State > 1)
      return InputBits * InputBits * InputBits;
   else
      return 77;
}

//creo un array i cui elementi sono le tre funzioni
unsigned int ( * pStateFunction[] ) ( unsigned int InputBits, SYSTEM_STATE *State ) =
{
    function1,
    function2,
    function3
};

//questa è la funzione invocata dal main per far giare la macchina a stati
unsigned int RunStateMachine( unsigned int InputBits )
{
    return (*pStateFunction[ gSystemState ])( InputBits, &gSystemState );
}

//questo è il main
void main(void)
{
   volatile unsigned int result1;
   volatile unsigned int result2;
   volatile unsigned int result3;

   
   while(1)
   {
       gSystemState = STATE0;
       result1 = RunStateMachine( 1 );

//gSystemState should be incremented by function
       result2 = RunStateMachine( 2 );

//gSystemState should be incremented by function
       result3 = RunStateMachine( 3 );
   }
}

```

## Code portability
Se voglio che il mio codoce sia portabile il più possibile, è meglio seguire alcune accortezze:
1. Puntatori a funzione sono definite dentro le strutture
2. Un array di puntatori a funzioni chiama le funzioni
3. Enum e struct sono usate per creare gli stessi puntatori a funzioni a Ram, periferiche ecc.

Esempio:

```bash
//Variable declarations
unsigned short u16buffer1[16];
unsigned short u16buffer2[16];
unsigned short u16dataBufferRead;


//Two 16-bit buffers will be accessed.  The names are BUFFER1 and BUFFER2.  There
// are three functions for each buffer.  The _Initialize function will load 16
// values into the buffer.  All values are the same and are defined by u16bufferFill.
// The second function will read one location of the buffer.  The third function will 
// write one location of the buffer.

//Write 16 integer values to BUFFER1 as defined by u16bufferFill
void BUFFER1_Initialize(unsigned short u16bufferFill)
{
   unsigned char i;
   
   for(i = 0; i <= 15; i++)
   {
      u16buffer1[i] = u16bufferFill;
   }   
} 


//Read one 16-bit value from BUFFER1 at the address specified by u8index
unsigned short BUFFER1_Read(unsigned char u8index)
{
   return u16buffer1[u8index];
}   


//Write one 16-bit value to BUFFER1 at the address specified by u8index
void BUFFER1_Write(unsigned char u8index, unsigned short u16value)
{
   u16buffer1[u8index] = u16value;
}   


//Write 16 integer values to BUFFER2 as defined by u16bufferFill
void BUFFER2_Initialize(unsigned short u16bufferFill)
{
   unsigned char i;
   
   for(i = 0; i <= 15; i++)
   {
      u16buffer2[i] = u16bufferFill;
   }   
} 


//Read one 16-bit value from BUFFER2 at the address specified by u8index
unsigned short BUFFER2_Read(unsigned char u8index)
{
   return u16buffer2[u8index];
}   


//Write one 16-bit value to BUFFER2 at the address specified by u8index
void BUFFER2_Write(unsigned char u8index, unsigned short u16value)
{
   u16buffer2[u8index] = u16value;
}   



//Enumeration for two different buffers.  This enumeration will be used to select 
// which buffer to access
enum { BUFFER1, BUFFER2} buffer_configurations_t;


//Create three function pointers within a typedef structure.  These three function pointers
// will initialize, read, and write the two buffers.  The *DataInit pointer performs
// the buffer initialization.  The *DataWrite pointer writes to the buffer.  The *DataRead
// pointer reads the buffer.
typedef struct { 
   void (*DataInit)(unsigned short bufferFill); 
   void (*DataWrite)(unsigned char index, unsigned short value); 
   unsigned short (*DataRead)(unsigned char index);
} buffer_functions_t;


//The buffer_access[ ] array contains the addresses for both of the buffer
// initialize, read and write functions.  This array is placed in flash but could
// be placed in RAM instead.  

// Line 1 accesses BUFFER1 and line 2 accesses BUFFER2.
// Each line has the addresses for each function (initialize, read, write).

//The BUFFER1_Initialize address corresponds to the *DataInit function pointer.
//The BUFFER1_WRITE address corresponds to the *DataWrite function pointer.
//The BUFFER1_READ address corresponds to the *DataRead function pointer.
const buffer_functions_t buffer_access[] = {   
    {BUFFER1_Initialize, BUFFER1_Write, BUFFER1_Read },
    {BUFFER2_Initialize, BUFFER2_Write, BUFFER2_Read }
};



//Main function
int main(void)
{
//Initialize both buffers    
   buffer_access[BUFFER1].DataInit(0x55);
   buffer_access[BUFFER2].DataInit(0xAA);

    while(1)
    {
//Access the functions for each buffer using the buffer_access[ ] array        
       buffer_access[BUFFER1].DataWrite(4, 0x1234);
       u16dataBufferRead = buffer_access[BUFFER1].DataRead(4);
       
       buffer_access[BUFFER2].DataWrite(8, 0x9876);
       u16dataBufferRead = buffer_access[BUFFER2].DataRead(8);
       
       while(1);

    }
}
```
## Double Pointers
Supponiamo di voler passare un puntatore di una variabile a una funzione, cosa succede se abbiamo un array di punyatori e volgiamo passare un punyatore all'array di puntatori a una funzione? Possiamo usare i puntatori a puntatori.

Esempio:

```bash
//Create an array of pointers and initialize 4 different strings.  These strings are programmed
// into flash during programming because the 'const' keyword is used to make the pointers point
// to flash memory.  Also, create some generic variables used for the loops.
const char *p[4] = {"ALARM", "FAULT", "SENSOR", "UNLOCK"};
const char **pp = &p[0];
unsigned char y;


//Function prototype
void string_access(const char **message_pointer);


int main(int argc, char** argv) 
{
    
//Step through the following code and watch the 'y' variable.  This code will separately access each
// string in the array.  This code will pass the pointer address to the strings to the function.  It will 
// increment the double pointer to point to the next string.  This method demonstrates how to pass the 
// pointer to the function.    
   while(1)
   {
//Access "ALARM"       
       pp = &p[0];
       string_access(&*pp);

//Access "FAULT"
       pp++;
       string_access(&*pp);

//Access "SENSOR"       
       pp++;
       string_access(&*pp);

//Access "UNLOCK"       
       pp++;
       string_access(&*pp);

      while(1);
   }
}


//This function receives the address of the array pointer to the text strings.  The
// double pointer allows us to pass the address of pointers to functions.  The function
// will access each character in the string until the NULL character is reached.
void string_access(const char **message_pointer)
{
    unsigned char i;
    
    i = 0;
    do{
        y = *(*message_pointer + i);
        i++;
    } while(y != '\0');
}
```
## Linked list
Le linked list sono nodi collegati da link, 3 tipi di linked list sono:

1. Simple linked list
2. Doubly linked list
3. Circular linked list

Ecco una semplice linked list:

```bash
struct Node {
  int data; // i dati contenuti nel nodo
  struct Node* next; //il puntatore al prossimo nodo
}
```
Il puntatore dell'ultimo nodo punta a NULL.
Nei doubly linked list ogni nodo ha due puntatori, uno al prossimo nodo e uno al precedente, il primo e l'ultimo nodo (non avendo nodo precedente e successivo) avranno un puntatore a NULL oltre a quello del nodo adiacente. La circular è come la doubly solo che il primo nodo punta anche all'ultimo e l'ultimo al primo (oltre che al nodo adiacente).

### Liste con Allocazione dinamica della memoria
Heap: è un'area di memoria pre riservata che un processo di un programma può usare per immagazzinare dati in una certa quantità che non è possibile conoscere finche il programma non gira.
Posso allocare memoria con la malloc

```bash
*malloc(size_t size); // alloca la memoria richiesta e restituisce un puntatore ad essa, la memoria è espressa in byte

newNode = (struct Node*)malloc(sizeof(struct Node)); // sto allocando memoria dinamicamente della dimensione di Node e chiamando il puntatore a quella locazione di memoria newNode

free(newNode); //per libearare la memoria devo usare free
```

Creaiamo una linked list, prima il la struttura del nodo e poi i puntatori

```bash
struct Node {
  int val;
  struct Node *nextPtr;
};

struct Node *currentPointer;
struct Node *previousPointer;

struct Node* headNode = NULL; //iniziamo con il puntatore del primo elemento
headNode = (struct Node*)malloc(sizeof(struct Node)); //allochiamo la memnoria per il primo elemento e salviamolo come valore "head"
```
Questo è il laboratorio associato:

```bash
#include <xc.h>
#include <stdio.h>
#include <stddef.h>

//Create the node structure for each element in the linked list
struct Node
{
    int val;
    struct Node *nextPtr;
};

//Create two pointers that will be used to search the linked list and add or delete nodes
struct Node *currentPointer;
struct Node *previousPointer;

//create a variable that will be used as a flag to denote that the search found a node that 
// we were looking for
uint8_t nodeFound;


void main(void) 
{
//Create structure pointer to four instanced of nodes in the linked list.  The only required 
// nodes to be created are "headNode" to signify the first node in the linked list and "newNode" 
// that will be used to manipulate the items in the list.  The "secondNode" and "thirdNode" 
// are created just for demonstration purposes to allow for some initial created nodes and make 
// it easier to understand the linked list concept.    
    struct Node* headNode = NULL; 
    struct Node* secondNode = NULL; 
    struct Node* thirdNode = NULL;   
    struct Node* newNode = NULL;

    
 //allocate 3 nodes in the heap 
    headNode = (struct Node*)malloc(sizeof(struct Node)); 
    secondNode = (struct Node*)malloc(sizeof(struct Node)); 
    thirdNode = (struct Node*)malloc(sizeof(struct Node)); 

    
//initialize all nodes
    headNode -> val = 2;
    headNode -> nextPtr = secondNode;
    secondNode -> val = 3;
    secondNode -> nextPtr = thirdNode;
    thirdNode -> val = 5;
    thirdNode -> nextPtr = NULL;

    
//create a new node with a value of 4.  It is not placed in the list yet.
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode -> val = 4;    

    
//add the node in numerical order in the linked list.  Initialize the node pointers.
    currentPointer = headNode;
    previousPointer = headNode;
    nodeFound = 0;


//step through the linked list and search for the position to place the newNode value of 4 
// so that the list stays in numerical order.

//the algorithm looks at the value in the location of the currentPointer and compares it 
// to the value in newNode.  If it is less than the value, the iteration of this search stops.  
// previousPointer is set equal to currentPointer and currentPointer is set equal to the 
// location pointed to by the nextPtr value in that location.  So this algorithm just steps 
// through the list.  If the currentPointer value is greater than the newNode value, then the
// newNode value will be placed before the currentPointer.  Since previousPointer points to the 
// location before the currentPointer, the nextPtr value of the previousPointer is set equal 
// to the newNode pointer.  The newNode pointer is set to point to the currentPointer location.
    
//For every iteration of the loop, the previousPointer is set equal to the currentPointer and 
// the currentPointer is incremented.  So there are pointers to the current node and previous 
// node at all times.    
    
//If the value to be placed is less than the first location in the list, the newNode pointer 
// is set to be the headPointer.  If the value to be placed is greater than the last location, 
// this search will fall through without placing the node in the list.  nodeFound is used to 
// signify that a node was placed.  If this value is 0, then the previousPointer is set to point 
// to the newNode and the newNode pointer is set to NULL.    
    while(previousPointer -> nextPtr != NULL)
    {
        if((currentPointer -> val) > (newNode -> val))
        {
            nodeFound = 1;
            newNode -> nextPtr = currentPointer;
            
            if(currentPointer != headNode)
                previousPointer -> nextPtr = newNode;
            
            else
                headNode = newNode;

            break;
        }

        previousPointer = currentPointer;        
        currentPointer = currentPointer -> nextPtr;
    } 

//Check if a node was found.  If not, put the value at the end of the list    
    if(!nodeFound)
    {
        previousPointer -> nextPtr = newNode;
        newNode -> nextPtr = NULL;        
        nodeFound = 0;
    }
    
    nodeFound = 0;
    
   
    
//Delete the node with a value of 3.
//This search is very similar to the previous search.  When the node value is found, the 
// previousPointer is set to point to the value pointed by currentPointer.  Then the free( ) 
// function call is used to deallocate the memory that currentPointer was pointing to.  If the 
// node to be deleted is the head node, then the headNode is set equal to the location pointed 
// to by the current head node.  If the location is pointing to NULL, then it must be the last 
// node, so the previousPointer is set to point to NULL since it will now be the last node.    
    currentPointer = headNode;
    previousPointer = headNode;
    
    while(previousPointer -> nextPtr != NULL)
    {
        if((currentPointer -> val) == 3)
        {
            if(currentPointer == headNode)
            {
                headNode = currentPointer -> nextPtr;
            }
            
            else if(currentPointer -> nextPtr == NULL)
            {
                previousPointer -> nextPtr = NULL;
            }
            
            else
            {
                previousPointer -> nextPtr = currentPointer -> nextPtr;
            }
            
            free(currentPointer);
            break;            
        }

        previousPointer = currentPointer;        
        currentPointer = currentPointer -> nextPtr;
    }     
    

    while(1);

}
```

### Liste senza Allocazione dinamica della memoria
Con questo sistema non uso la malloc per allocare la memoria a runtime ma dichiaro un array per allocare subito la memoria che mi serve, la struttura data viene dichiarata in maniera praticamente identica al caso precedente.

```bash
struct Node {
  uint8_t locationIsAvailable;
  uint32_t val;
  struct Node *nextPtr;
};

struct Node *currentPointer;
struct Node *previousPointer;
struct Node *newNode;
struct Node *headNode;

struct Node listReservedMemory[TOTAL_NODES]; //TOTAL_NODES costante con il numero di nodi da allocare

currentPointer = &listReservedMemory[0];
headNode = &listReservedMemory[0];
```
Questo il laboratorio associato:


```bash
#include <xc.h>
#include <stdio.h>

#define TOTAL_NODES 25

//Create the node structure for each element in the linked list
struct Node
{
    uint8_t locationIsAvailable;
    uint32_t __attribute__((packed))val;
    struct __attribute__((packed))Node *nextPtr;
};


//reserve memory for 25 nodes.  This array is only used for memory allocation.
struct Node listReservedMemory[TOTAL_NODES];

//Create two pointers that will be used to search the linked list and add or delete nodes
struct Node *currentPointer;
struct Node *previousPointer;

//create the newNode that will be used to place data within the list
struct Node *newNode;

//create node designation for the first node in the list
struct Node *headNode;

//create a variable that will be used as a flag to denote that the search found a node that 
// we were looking for
uint8_t nodeFound;




void main(void) 
{
    uint8_t i;
    
//after establishing the pointers in the array, the array will no longer be used for node placement or
// deletion.  Everything moving forward after the list setup is using linked list parameters. The only time
// that the array will be used is to set the start location for searches.
    
//establish the linked list search pointer   
    currentPointer = &listReservedMemory[0];

    
//initialize all list locations
    for(i = 0; i < TOTAL_NODES; i++)
    {
        currentPointer->locationIsAvailable = 1;
        currentPointer->val = 0;
        currentPointer->nextPtr = NULL;
        currentPointer++;
    }

    
//initialize some nodes to demonstrate the search
    currentPointer = &listReservedMemory[0]; 
    headNode = &listReservedMemory[0];    
    
    headNode -> val = 2;
    headNode -> locationIsAvailable = 0;
    headNode -> nextPtr = ++currentPointer;
    
    currentPointer -> val = 3;
    currentPointer -> locationIsAvailable = 0;
    currentPointer -> nextPtr = ++currentPointer;
    
    currentPointer -> val = 5;
    currentPointer -> locationIsAvailable = 0;
    currentPointer -> nextPtr = NULL;
    
    newNode = NULL;
    
    
//find the first unused location in the list to use as the newNode   
// Search through up to TOTAL_NODES of nodes and will always be located in the
// allocated array memory
    currentPointer = &listReservedMemory[0];   
    
    for(i = 0; i < TOTAL_NODES; i++)
    {
        if(currentPointer ->locationIsAvailable)
        {
            newNode = currentPointer;
            newNode -> locationIsAvailable = 0;
            break;
        }

        currentPointer++;            
    }    

    
//only place the newNode if a valid pointer was returned from the search    
    if(newNode != NULL)   
    {
//create a new node with a value of 4.  It is not placed in the list yet.
        newNode -> val = 4;    

    
//add the node in numerical order in the linked list.  Initialize the node pointers.
        currentPointer = headNode;
        previousPointer = headNode;
        nodeFound = 0;


//step through the linked list and search for the position to place the newNode value of 4 
// so that the list stays in numerical order.

//the algorithm looks at the value in the location of the currentPointer and compares it 
// to the value in newNode.  If it is less than the value, the iteration of this search stops.  
// previousPointer is set equal to currentPointer and currentPointer is set equal to the 
// location pointed to by the nextPtr value in that location.  So this algorithm just steps 
// through the list.  If the currentPointer value is greater than the newNode value, then the
// newNode value will be placed before the currentPointer.  Since previousPointer points to the 
// location before the currentPointer, the nextPtr value of the previousPointer is set equal 
// to the newNode pointer.  The newNode pointer is set to point to the currentPointer location.
    
//For every iteration of the loop, the previousPointer is set equal to the currentPointer and 
// the currentPointer is incremented.  So there are pointers to the current node and previous 
// node at all times.    
    
//If the value to be placed is less than the first location in the list, the newNode pointer 
// is set to be the headPointer.  If the value to be placed is greater than the last location, 
// this search will fall through without placing the node in the list.  nodeFound is used to 
// signify that a node was placed.  If this value is 0, then the previousPointer is set to point 
// to the newNode and the newNode pointer is set to NULL.    
        while(previousPointer -> nextPtr != NULL)
        {
            if((currentPointer -> val) > (newNode -> val))
            {
                nodeFound = 1;
                newNode -> nextPtr = currentPointer;
            
                if(currentPointer != headNode)
                    previousPointer -> nextPtr = newNode;
            
                else
                    headNode = newNode;

                break;
            }

            previousPointer = currentPointer;        
            currentPointer = currentPointer -> nextPtr;
        } 

//Check if a node was found.  If not, put the value at the end of the list    
        if(!nodeFound)
        {
            previousPointer -> nextPtr = newNode;
            newNode -> nextPtr = NULL;        
            nodeFound = 0;
        }
    
        nodeFound = 0;
    }
   
    
//Delete the node with a value of 3.
//This search is very similar to the previous search.  When the node value is found, the 
// previousPointer is set to point to the value pointed by currentPointer.  Then the node
// value is set to 0 and the locationIsAvailable is set to 1.    
// If the node to be deleted is the head node, then the headNode is set equal to the location 
// pointed to by the current head node.  If the location is pointing to NULL, then it must be 
// the last node, so the previousPointer is set to point to NULL since it will now be the last node.    
    currentPointer = headNode;
    previousPointer = headNode;
    
    while(previousPointer -> nextPtr != NULL)
    {
        if((currentPointer -> val) == 3)
        {
            if(currentPointer == headNode)
            {
                headNode = currentPointer -> nextPtr;
            }
            
            else if(currentPointer -> nextPtr == NULL)
            {
                previousPointer -> nextPtr = NULL;
            }
            
            else
            {
                previousPointer -> nextPtr = currentPointer -> nextPtr;
            }
            
            currentPointer -> locationIsAvailable = 1;
            currentPointer -> nextPtr = NULL;
            break;            
        }

        previousPointer = currentPointer;        
        currentPointer = currentPointer -> nextPtr;
    }     

    while(1);

}

```

### File Header
Per evitare che un file header venga incluso più volte oppure che ci siano duplicati è buona prassi usare la seguente accortezza

header.h
```bash
#ifndef HEADER_H
#define HEADER_H
//code...
#endif
```

### Floating point operation without FPU 
