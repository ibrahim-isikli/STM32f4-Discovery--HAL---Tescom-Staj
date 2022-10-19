/******************* GOAL *********************/

/* SP'yi degistirmek icin kod yazalim
 *
 * | Thread Mode SP -> Control reg -> 1|0 -> PSP|MSP  |
 * | Handler Mode -> SP  -> only MSP |
 *
 * PSP degerine gecmek icin THREAD mode'da control registerina ulasmaliyiz
 *  control register , bir speacil register oldugundan asssembly kodlariyla ulasabiliriz
 *
 */

/*
            -----------------------SRAM(128KB)--------------------------
 			|        GLOBAL DATA              |     HEAP     |   STACK |
  			------------------------------------------------------------
  			v                                                v
  		20000000									 STACK_START(SRAM_END)

*/
/*  ------------stack space-------------
 * |                                  |   -> STACK_MSP_START      (SRAM_END)
 * |                                  |
 * |                                  |   512 byte MSP (HANDLER MODE)
 * 1                                  |
 * K                                  |
 * B  -----       ------   ---------- |  -> STACK_MSP_END = STACK_PSP_START
 * |                                  |
 * |                                  |
 * |                                  |	 512 byte PSP (THREAD MODE)
 * |                                  |
 * |                                  |  -> STACK_PSP_END
 * ------------------------------------
 */

/************************** assembly hatirlatma ***********************/
/*
 *  MSR -> Move Special reg -> reg
 *
 */

#include <stdint.h>
#include <stdio.h>

#if 0

// sRAM i ayarla
#define SRAM_START 0x20000000U
#define SRAM_SIZE  (128*1024)
#define SRAM_END  ( (SRAM_START) + (SRAM_SIZE) )
#define STACK_START SRAM_END

// STACK'ı ayarla yarisi handler modeda MSP, yarisi thread modeda SPS olacak
#define STACK_MSP_START  STACK_START
#define STACK_MSP_END    (STACK_MSP_START - 512)
#define STACK_PSP_START  STACK_MSP_END

#endif


int fun_add(uint32_t a, uint32_t b, uint32_t c, uint32_t d){
	return a+b+c+d;
}

/*This attribute tells the compiler that the function is an embedded assembly function
 *You can write the body of the function entirely in assembly code using __asm statements.*/
   __attribute__((naked)) void change_sp_to_psp(void){

	   __asm volatile(".equ SRAM_END, ((0x20000000)+(128*1024))"); // .equ assemblyde makro olusturur
	   __asm volatile(".equ PSP_START, (SRAM_END-512)");
	  __asm volatile("LDR R0, =PSP_START"); 	    // R0 =  PSP_START
	  __asm volatile("MSR PSP,R0");					// PSP = PSP_START  -> PSP=> SRAM_END-512'den basla
	  __asm volatile ("MOV R0, #0x02");				// control regin SPEL biti 1 olsun ki SPS'e gecsin
	  	  	  	  	  	  	  	  	  	  	  	  	// R0 = 0x00000002 = 0010
	  __asm volatile ("MSR CONTROL,R0");			// CONTROL = R0 -> SPSEL 1 -> PSP Enable
	  __asm volatile("BX LR");						// LR -> return address


 }

   void generate_exception(void){

	   //  SuperVisor Call (SVC) instruction, with that the user can trigger an exception -> passing THREAD MODE
	   __asm volatile("SVC  #0x2");
   }

int main(void)
{
	change_sp_to_psp();

	 int ret;
	ret=fun_add(1, 4, 5, 6);
	printf("result = %d\n",ret);

	generate_exception();

	for(;;);
}

void SVC_Handler(void){
	printf("in SVC_Handler\n");
}
