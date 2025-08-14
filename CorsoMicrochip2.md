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

### Callbacks e Hardware
I driver sono scritti per funzionalità hardware, nel codice dell'applicazione ci sono i puntatori a funzione per funzionalità hardware e funzionalità applicative, questo può permetterci di concentrarci sugli algoritmi del programma senza considerare troppo l'hardware. Vediamo subito un esempio pratico, bisogna considerare due file, quello della libreria e quello che la usa

1. Libreria
```bash
#include <xc.h> 

#define XPLAINED_LED            PORT_PB08
#define E54_LED_OUT             PORT_PC18

//Prototype for the function in the application program
void callback_execution(void(*fn)(void));

//initialize functionPointer pointer to point to callback_execution( ))
void (*functionPointer)(void(*fn)(void)) = &callback_execution;


/*******************************************************************************
* void callback_function(void)  
*
* FUNCTION:  Toggles the LED's and is called by the application program
* RETURNED VALUES: None 
* PARAMETERS: None
*******************************************************************************/
void callback_function(void) 
{
    PORT_REGS->GROUP[1].PORT_OUTTGL = XPLAINED_LED;
    PORT_REGS->GROUP[2].PORT_OUTTGL = E54_LED_OUT;            
}


/***********************************************************************************
void TC3_Handler(void)

FUNCTION:  Interrupt handler for the TC3 interrupt
				- Interrupt occurs every 10ms
***********************************************************************************/
void TC3_Handler()
{
//Check for a TC3 interrupt by looking at the OVF bit in the INTFLAG register.  If it
// is set, clear it by setting the bit. Then call the function pointed to by
// functionPointer. callback_execution( ) is pointed to by functionPointer and
// resides in the main application program.
    if(TC3_REGS->COUNT16.TC_INTFLAG & TC_INTFLAG_OVF(1))
    {
        TC3_REGS->COUNT16.TC_INTFLAG = TC_INTFLAG_OVF(1);
        
        functionPointer(&callback_function);
    }
}


```

2. Callback
```bash
// Config Source code for XC32 compiler.
// USER_WORD_0
#pragma config BOD33_DIS = SET
#pragma config BOD33USERLEVEL = 0x1C // Enter Hexadecimal value
#pragma config BOD33_ACTION = RESET
#pragma config BOD33_HYST = 0x2 // Enter Hexadecimal value
#pragma config NVMCTRL_BOOTPROT = 0xF

// USER_WORD_1
#pragma config NVMCTRL_SEESBLK = 0x0 // Enter Hexadecimal value
#pragma config NVMCTRL_SEEPSZ = 0x0 // Enter Hexadecimal value
#pragma config RAMECC_ECCDIS = SET
#pragma config WDT_ENABLE = CLEAR
#pragma config WDT_ALWAYSON = CLEAR
#pragma config WDT_PER = CYC16384
#pragma config WDT_WINDOW = CYC16384
#pragma config WDT_EWOFFSET = CYC16384
#pragma config WDT_WEN = CLEAR

// USER_WORD_2
#pragma config NVMCTRL_REGION_LOCKS = 0xFFFFFFFF // Enter Hexadecimal value


#include <xc.h> 
#include "main.h"
#include "constants.h"



/*******************************************************************************
* void callback_execution(unsigned char(*fn)(void)) 
*
* FUNCTION:  Callback execution function that is passed a function pointer and
*               returns the status of the switch position
* RETURNED VALUES: None
* PARAMETERS: Function pointer for the callback function 
*******************************************************************************/
void callback_execution(void(*fn)(void))
{	
//Check the switch level to see if it is pressed.  SW0 is a mask value that is declared
// in the "constants.h" file.  If it is low, the switch is pressed and the 'u16debounceCounter'
// variable is decremented once on each interrupt.  If the counter reaches 0, the switch is
// pressed and i is incremented.  If the switch is not pressed, the value in the
// counter is reaches the 'DEBOUNCE_HIGH_LIMIT' signifying a non-pressed switch.
    if(!(PORT_REGS->GROUP[1].PORT_IN & SW0))
    {
        if(--u16debounceCounter == 0)
		{
			u16debounceCounter = DEBOUNCE_START;
               
           	if(++i >= FULL_DEBOUNCE_COUNTS)
           	{
                i = 0;
                fn( );  
            }
    	}
	} 
    
	else
    {
        if(++u16debounceCounter >= DEBOUNCE_HIGH_LIMIT)
    	{
        	u16debounceCounter = DEBOUNCE_START;
        }    
    }
}


/*******************************************************************************
* int main(void) 
*
* FUNCTION:  Main routine that initializes the microcontroller and runs an empty
*               while(1) loop
* RETURNED VALUES: None
* PARAMETERS: None
*******************************************************************************/
int main(void)
{
//Initialize the SAM system
    systemInit();
	
//Enable interrupts
	enable_interrupts( );
	
//Initialize variables
	u16debounceCounter = DEBOUNCE_START;
    
    while (1) 
    {

    }
}
```

Il flusso è il seguente:
1. library_callback -> TC3_Handler interrupts scatta e chiama callback_execution
2. lab5_callback -> callback_execution debounce i switch pins e chiama callback_function se l'interruttore è premuto
3. library_callback -> callback_function fa il toggle dei led sulla scheda.

Ecco un altro esempio:

typedef.h
```bash
#include <xc.h>


//Timer status data type variables for all three timer modes (timer,
// compare, and capture)
typedef uint32_t TC_CAPTURE_STATUS;
typedef uint32_t TC_COMPARE_STATUS;
typedef uint32_t TC_TIMER_STATUS;


//Three callback function pointers - one for each of the timer modes (timer, compare, 
// capture)
typedef void (*TC_TIMER_CALLBACK) (TC_TIMER_STATUS status, uintptr_t context);
typedef void (*TC_COMPARE_CALLBACK) (TC_COMPARE_STATUS status, uintptr_t context);
typedef void (*TC_CAPTURE_CALLBACK) (TC_CAPTURE_STATUS status, uintptr_t context);


//Three callback structures - one for each of the timer modes
typedef struct
{
    TC_TIMER_CALLBACK callback;
    uintptr_t context;
} TC_TIMER_CALLBACK_OBJ;

typedef struct
{
    TC_COMPARE_CALLBACK callback;
    uintptr_t context;
}TC_COMPARE_CALLBACK_OBJ;

typedef struct
{
    TC_CAPTURE_CALLBACK callback;
    uintptr_t context;
}TC_CAPTURE_CALLBACK_OBJ;
```

constant.h

```bash
#ifndef CONSTANTS_H_
#define CONSTANTS_H_

//Use EXT1 on the Xplained Pro board to interface to the I/O Xplained board

//Pin names
#define XPLAINED_LED            PORT_PB08
#define SW0                     PORT_PB31
#define GCLK0_OUT               PORT_PB14
#define E54_LED_OUT             PORT_PC18


/*
Frequency of the system clock is 48MHZ.  The divider at TC3 is 256, so the frequency at TC3  
is 0.1875MHZ (5.333us).  The timer is set up as an 16-bit counter.  To get a 10ms interrupt, 
10ms/5.333us = 1875.  
*/
#define TC3_CC0					1875


/*
Switch is debounced each TC3 interrupt interval (10ms).  It starts from the DEBOUNCE_START value and
counts down if the switch is pressed.  If it reaches 0, the switch is pressed. 50 x 10ms is 500ms.
Variable i is incremented every interrupt and the comparison is made to FULL_DEBOUNCE_COUNTS. When
the number of FULL_DEBOUNCE_COUNTS is reached, the callback function is called. 500ms x 2 = 1s blink
interval.
*/
#define DEBOUNCE_START			50 
#define DEBOUNCE_HIGH_LIMIT     100
#define FULL_DEBOUNCE_COUNTS    2


// *****************************************************************************
/* Convenience macros for TC capture status */
// *****************************************************************************
#define TC_CAPTURE_STATUS_NONE              0U

/* Capture status overflow */
#define TC_CAPTURE_STATUS_OVERFLOW          TC_INTFLAG_OVF_Msk

/* Capture status error */
#define TC_CAPTURE_STATUS_ERROR             TC_INTFLAG_ERR_Msk

/* Capture status ready for channel 0 */
#define TC_CAPTURE_STATUS_CAPTURE0_READY    TC_INTFLAG_MC0_Msk

/* Capture status ready for channel 1 */
#define TC_CAPTURE_STATUS_CAPTURE1_READY    TC_INTFLAG_MC1_Msk

#define TC_CAPTURE_STATUS_MSK               (TC_CAPTURE_STATUS_OVERFLOW | TC_CAPTURE_STATUS_ERROR | TC_CAPTURE_STATUS_CAPTURE0_READY | TC_CAPTURE_STATUS_CAPTURE1_READY) 

/* Invalid compare status */
#define TC_CAPTURE_STATUS_INVALID           0xFFFFFFFFU


// *****************************************************************************
/* Convenience macros for TC compare status */
// *****************************************************************************
#define TC_COMPARE_STATUS_NONE          0U
/*  overflow */
#define TC_COMPARE_STATUS_OVERFLOW      TC_INTFLAG_OVF_Msk
/* match compare 0 */
#define TC_COMPARE_STATUS_MATCH0        TC_INTFLAG_MC0_Msk
/* match compare 1 */
#define TC_COMPARE_STATUS_MATCH1        TC_INTFLAG_MC1_Msk

#define TC_COMPARE_STATUS_MSK           (TC_COMPARE_STATUS_OVERFLOW | TC_COMPARE_STATUS_MATCH0 | TC_COMPARE_STATUS_MATCH1)

/* Invalid capture status */
#define TC_COMPARE_STATUS_INVALID       0xFFFFFFFFU


// *****************************************************************************
/* Convenience macros for TC timer status */
// *****************************************************************************

#define TC_TIMER_STATUS_NONE        0U
/*  overflow */
#define TC_TIMER_STATUS_OVERFLOW    TC_INTFLAG_OVF_Msk

/* match compare 1 */
#define TC_TIMER_STATUS_MATCH1      TC_INTFLAG_MC1_Msk

#define TC_TIMER_STATUS_MSK         (TC_TIMER_STATUS_OVERFLOW | TC_TIMER_STATUS_MATCH1)

/* Invalid timer status */
#define TC_TIMER_STATUS_INVALID     0xFFFFFFFFU



#endif /* CONSTANTS_H_ */

```


main.c
```bash
// Config Source code for XC32 compiler.
// USER_WORD_0
// #pragma serve per istruzioni specifiche del compilatore, non è C standard
#pragma config BOD33_DIS = SET
#pragma config BOD33USERLEVEL = 0x1C // Enter Hexadecimal value
#pragma config BOD33_ACTION = RESET
#pragma config BOD33_HYST = 0x2 // Enter Hexadecimal value
#pragma config NVMCTRL_BOOTPROT = 0xF

// USER_WORD_1
#pragma config NVMCTRL_SEESBLK = 0x0 // Enter Hexadecimal value
#pragma config NVMCTRL_SEEPSZ = 0x0 // Enter Hexadecimal value
#pragma config RAMECC_ECCDIS = SET
#pragma config WDT_ENABLE = CLEAR
#pragma config WDT_ALWAYSON = CLEAR
#pragma config WDT_PER = CYC16384
#pragma config WDT_WINDOW = CYC16384
#pragma config WDT_EWOFFSET = CYC16384
#pragma config WDT_WEN = CLEAR

// USER_WORD_2
#pragma config NVMCTRL_REGION_LOCKS = 0xFFFFFFFF // Enter Hexadecimal value


#include <xc.h> 
#include "constants.h"
#include "typedef.h"
#include "stddef.h"


//GLOBAL VARIABLES
volatile uint16_t u16debounceCounter;
volatile uint8_t i;
TC_TIMER_CALLBACK_OBJ TC3_CallbackObject;


//PROTOTYPES
void systemInit(void);
void enable_interrupts(void);


//callback is the routine that will be called for the callback registration.
// context can be used to add other parameters (variables, etc...) if they
// are required in the callback. It is not used in this example.
void TC3_TimerCallbackRegister( TC_TIMER_CALLBACK callback, uintptr_t context )
{
    TC3_CallbackObject.callback = callback;
    TC3_CallbackObject.context = context;
}


/*******************************************************************************
* void led_toggle_function(void)   
*
* FUNCTION:  Toggles the LED's
* RETURNED VALUES: None 
* PARAMETERS: None
*******************************************************************************/
void led_toggle_function(void) 
{
    PORT_REGS->GROUP[1].PORT_OUTTGL = XPLAINED_LED;
    PORT_REGS->GROUP[2].PORT_OUTTGL = E54_LED_OUT;            
}


/*******************************************************************************
* void callback_execution(TC_TIMER_STATUS status, uintptr_t context) 
*
* FUNCTION:  Callback execution function that is passed a function pointer and
*               calls the led_toggle function if the switch is pressed
* RETURNED VALUES: None
* PARAMETERS: TC_TIMER_STATUS status, uintptr_t context  
*******************************************************************************/
void callback_execution(TC_TIMER_STATUS status, uintptr_t context)
{
//We could check for specific TC3 functionality to perform different tasks for
// overflow, capture or compare. In this case, the timer overflow is chec
    if(status & TC_COMPARE_STATUS_MATCH0)
    {    
//Check the switch level to see if it is pressed.  SW0 is a mask value that is declared
// in the "constants.h" file.  If it is low, the switch is pressed and the 'u16debounceCounter'
// variable is decremented once on each interrupt.  If the counter reaches 0, the switch is
// pressed and i is incremented.  If the switch is not pressed, the value in the
// counter is reaches the 'DEBOUNCE_HIGH_LIMIT' signifying a non-pressed switch. The
// led_toggle_function is called if the switch is pressed.    
        if(!(PORT_REGS->GROUP[1].PORT_IN & SW0))
        {
            if(--u16debounceCounter == 0)
    		{
        		u16debounceCounter = DEBOUNCE_START;
               
               	if(++i >= FULL_DEBOUNCE_COUNTS)
                {
                    i = 0;
                    led_toggle_function( );  
                }
            }
    	} 
    
    	else
        {
            if(++u16debounceCounter >= DEBOUNCE_HIGH_LIMIT)
        	{
            	u16debounceCounter = DEBOUNCE_START;
            }    
        }
    }
}

/***********************************************************************************
void TC3_Handler(void)

FUNCTION:  Interrupt handler for the TC3 interrupt
        		- Interrupt occurs every 1ms
                - calls the debounce callback function using the registered 
                    callback
***********************************************************************************/
void TC3_Handler()
{
//Check for a TC3 interrupt by looking at the INTENSET register. Make sure that 
// an interrupt source is enabled.
    if(TC3_REGS->COUNT16.TC_INTENSET != 0)
    {
        TC_TIMER_STATUS status;

//save the interrupt flag register        
        status = (TC_TIMER_STATUS)TC3_REGS->COUNT16.TC_INTFLAG;
        
//clear TC3 interrupt flags (TC_INTFLAG_Msk is in tc.h)       
        TC3_REGS->COUNT16.TC_INTFLAG = (uint8_t)TC_INTFLAG_Msk;
        
//if interrupt flag is not empty or NULL, call the callback function
        if((status != TC_TIMER_STATUS_NONE) && (TC3_CallbackObject.callback != NULL))
        {
            TC3_CallbackObject.callback(status, TC3_CallbackObject.context);
        }
    }
}


/*******************************************************************************
* int main(void) 
*
* FUNCTION:  Main routine that initializes the microcontroller and runs an empty
*               while(1) loop
* RETURNED VALUES: None
* PARAMETERS: None
*******************************************************************************/
int main(void)
{
//Initialize the SAM system
    systemInit();
	
//Enable interrupts
	enable_interrupts( );
	
//Initialize switch debounce counter
	u16debounceCounter = DEBOUNCE_START;
    
//Register the callback    
    TC3_TimerCallbackRegister(callback_execution, 0);

//while( ) loop is empty since the interrupt handles the switch debounce and
// calling of the callback function    
    while (1) 
    {

    }
}
```
