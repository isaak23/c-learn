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

### 2.Automatic
Sono le variabili dentro una funzione, e hanno una vita limitata all'uso della funzione

### 3.External

