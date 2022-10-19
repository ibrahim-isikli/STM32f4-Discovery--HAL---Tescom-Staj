/*****************************************NOTLAR**********************************/


/*
 * NVIC (Nested Vector Interrupt Controller)
 *
 * NVIC, Cortex M processorun bir peripheralidir
 * 240 interrupti kontrol eder
 *  NVIC kullanarak interruptları enable\disable\pend olarak configre edebilirsin
 *  'NESTED' denmesinin sebebi oncelik siralamasi icermesinden
 *  yuksek oncelikli bir interrupt,dusuık oncelikliyi keser
 *
 */

/*========= ENABLE\ DISABLE \ PEND various interrupts using NVIC Register ==========*/
/*
 * 1) Cortex M processor 240 interruptı destelşer
 * 2) Bu interruptları NVIC yonetir, yapilandirir
 * bu 240 interruptı user manual -> vector table dan inceleyebilirsin
 * 4) STM32f407xx MCU bu interruptlardan 83 tanesini sunar
 */

#include <stdint.h>


int main(void)
{
    /* Loop forever */
	for(;;);
}
