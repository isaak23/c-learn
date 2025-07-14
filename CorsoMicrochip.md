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

## Operatori logici


```bash
```
