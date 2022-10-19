/*****NOTLAR*******/

/* ************************stack memory,****************************
 *
 * Stack Memory’deki değerler son giren ilk çıkar mantığına göre tutulur (LIFO)
 * Stack Memory, işlemcilerin register bilgilerinin tutulduğu yerdir.
 *  Burada programınızla ilgili bilgiler (örneğin; lokal değişkenler, referans değişkenler vs) yer almaktadır.
 *  Bu memory, geliştirici tarafından değil, compiler tarafından yönetilir.
 *  Stack’teki bilgiler kodunuzun derleme aşamasında, direk bellek içine yerleştirildiği için erişimi oldukça hızlıdır.
 *
 *  Biz geliştiriciler için çok önemli olmasa da, programımız işlemci üzerinde çalışabilmek için sürekli stack belleğini arar.
 *   Her lokal değişken ve çağrılan her fonksiyon buraya gider.
 *
 *  main memorynin( ınternal RAM veya external RAM) bir parcası
 * transient datalari depolar
 * function interruptlar sirasinda kullanilir
 *  stack, stack pointer ile izlenir stack pointer -> SP -> R13
 *
 *
 *
 *  stack memory kullanimi
 *
 *  temporary stoge -> register values, local variables of functions


 *  ***********************  RAM Bölümleri**************
 *
 *  		-----------------------SRAM(128KB)--------------------------
 *			|        GLOBAL DATA              |     HEAP     |   STACK |
 * 			------------------------------------------------------------
 *
 * Stack operation models:
 * Full ascending stack (FA) \ full descending stack (FD) \ Empty ascending stack EA \ Empty descanding stack ED \
 * ARM Cortex Mx processors use FD


 ******************* Banked Stack Pointers********
 *
 * Cortex M processer has 3 stack pointers
 * \SP(R13)\MSP\PSP
 * MSP:Main stack pointer
 * PSP: Process stack pointer
 *
 * 			 Processor restletnidkten sonra default olarak MSP gecerli stack pointer olarak secilecektir
 * 			 Bu SP nin MSP iceriğini kopyaladigi anlamina gelir
 *
 * 			 THREAD Modu stack pointiri  (Control registerin  SPSEL bitini ayarlar)
 * 			 THREAD MOODUnda -> CONTROL registerin SPSEL biti;
 * 			 0 ise gecerli stack pointer MSP
 * 			 1 ise gecerli stack pointer PSP
 * 			 ve her iki durumda da SP bunlardan kopyalar
 *
 * 			 Handler modeda gecerli stuck pointer hep MSP'dir
 * 			 Bu su anlama gelir Handle modda control registerin SPSEL bitini degistirtmek bir ifade etmez
 * 			 Handler mode ne olursa olsun  MSP'yi stack pointer olrak secer
 */


/* EXERCİSE*/

#include <stdint.h>
#include <stdio.h>

int fun_add(int a, int b, int c, int d){
	return a+b+c+d;
}


int main(void)
{

	int ret;

	ret = fun_add(1,4,5,6);
	printf("result = %d\n",ret);
	for(;;);
}



/* register -> sp registerini gozlemleyelim
 *
 * Name : sp
	Hex:0x2001fff0
	Decimal:537001968
	Octal:04000377760
	Binary:100000000000011111111111110000
	Default:0x2001fff0

	1ff0 -> sp ramin en yuksek bellek adrtesinden baslatilmis
	ayrica msp de bu degerdedir
 */


/* startup dosyasini inceleyelim column->129 g_pfnVectors
 * baslangicta .word estack var
 * vektor tablosunun ilk yıgın adresi stack olmalidir
 *
 * cunku islemci tarafindan yapilan ilk is vektor tablosunu okumatır
 * ilk girisi de MSP register yani .word estack
 *
 * processorın sıfırlandıgında yaptigi ilk is MSP registiri
 * o yüzden gecerli bir MSP adresi yerlestirmelisin
 */


/* stm32f407vgtx_flash.ld dosyasini inceledigimizde
 * column -> 40
 * _estack = ORIGIN(RAM) + LENGTH(RAM)
 * _Min_Heap_Size = 0x200;
 * _Min_Stack_Size = 0x400;
 * MEMORY
{
  CCMRAM    (xrw)    : ORIGIN = 0x10000000,   LENGTH = 64K
  RAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 128K
  FLASH    (rx)    : ORIGIN = 0x8000000,   LENGTH = 1024K
}


 Origin of RAM is this one , this address -> RAM    (xrw)    : ORIGIN = 0x20000000

 0x2000000 + (128*1024) -> 0x20020000
 Ramin kökeni\ 128 *1024 (kilobyte-> byte) -> iste o meshur SRAM in basladigi adres
 -> 0x20020000
 */




