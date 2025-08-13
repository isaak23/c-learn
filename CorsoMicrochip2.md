# Corso C Microchip - Seconda Parte

## Callbacks

Callback functionality is an important concept in embedded programming. Callbacks allow you to create more flexible and modular functions and enable you to separate hardware and software operations. They also allow for multiple programmers to work on a project and provide code to be combined with the main application program. You can use different callback implementations to reduce your code execution bandwidth and enable faster and more flexible response to any microcontroller pin or peripheral condition. In this course, you will be able to explain the components of a callback. You will be able to use callbacks in both polled and interrupt environments. You will learn how to create library and object files that can be incorporated into your application program with the use of callbacks. You will be able to construct very flexible callback structures. Callbacks are a powerful application of pointers that access functions, so you do need to have a good understanding of function pointers and the C programming language.

Una callback è una funzione che è chiamata usando un puntatore a funzione.

### Componenti di una callback
Una callback ha 3 componenti:

1. la funzione di callback
2. la registrazione della callback
3. l'esecuzione della callback

quindi iniziamo a creare la funzione:

```bash
void callback_function(void) {} //posso comunque avere tipo di ritorno e parametri
```

creo il puntatore alla funzione

```bash
void (*functionPointer)(void) = &callback_function; //posso comunque avere tipo di ritorno e parametri
```

l'esecuzione invece è
```bash
void callback_execution(void(*fn)(void)) {} //callback execution è una funzione a cui viene passato un puntatore a funzione che punta la funzione di callback, questa è una firma, quando poi la uso al posto di *fn devo mettere la mia funzione di callback (callback_function(functionPointer))
```
la callback execution controllerà un parametro che dico io (la temperatura di un  sensore ecc), poi se la condizione si verifica invoco la funzione di callback

```bash
void callback_execution(void(*fn)(void)) {
  if (i++==5) {
    fn(); //chiama la callback
  }
}

void main(void) {
  while(1) {
  callback_execution(functionPointer);
}
}
```
### Callbacks e interrupt
Posso usare le callback anche dentro le ISR ma devo fare attenzione che la la callback duri meno del tempo di interrupt
