/***************Notlar**************/
/*Bit Banding Nedir ?
 * Bir bellek adresinin tek bir bitini adresleme yetenegidir
 *
 * ornegin 1kb memory adressimiz olsun her kutu 8 bit uzungunda
 * --------8bit------
 * |                | 0x2000_003
 * ------------------
 * |                |  0x2000_002
 * ------------------
 * |                | 0x2000_001
 * ------------------
 * |                | 0x200_0000
 * ------------------
 *
 * 0x200_0000 adresinde 8 bit var, ben 1 bit veya 4 bit 8bit nasil okurum -> bit adresleme
 * LDRB R0,[R1] 1 bit okur
 * LDRH 2 bie okur
 * LDR 8 bit okur
 *
 * adresteki biti nasil degistirecegiz
 * Normal Metot
 * LDRB R0,[R1] -> yukle
 * ORR (modife) -> degistir
 * STRB-R0,[R0]> sakla
 *  Bit Banding Metot
 *  LDRB R0,[alias  adresi]
 *  Sram ve peripheral icin bu yontem kullanilabilir
 *
 *  Calculate the bit band alias address for given bit band memory addreess and bit position
 *  7th bit position of the memory location 0x2000_020 using its alias address
 *
 *  Alias address = alias_base + (32*(bit_band_memory_addr-bit_band_base))+bit*4)
 *
 *  datasheetten sram'i incele -> 32mb bit band alias tabanındaki adres -> 0x22000000
 *  ve bit band region tabanindaki adres -> 0x20000000
 *
 *  alias address = 0x22000000+(32*0x2000_020 - 0x20000000)) + 7*4
 */

#include <stdint.h>
#include <stdio.h>
#define ALIAS_BASE 0x22000000U
#define BITBAND_BASE 0x20000000U



int main(void)
{


	uint8_t *ptr = (uint8_t*)0x20000200;  // 7.bit
	 *ptr = 0xff; // 7.bitteki saklanan deger

	 // normal metot

	 *ptr &= ~(1 << 7); // 7.bit reset

	 // bit bant methot
	 *ptr = 0xff;
	 uint8_t *alias_address = (uint8_t*)(ALIAS_BASE+(32*(0x20000200 - BITBAND_BASE)) + 7 * 4);

	 //uint8_t *alias_address = (uint8_t*) (BITBAND_BASE)+((ALIAS_BASE*32)+(7*4));


	 *alias_address = 0; // 7. bit reset

	 // bit degisimi gormek icin memory browserdan 0x20000200 (7. bit) takip edilmeli

	for(;;);
}
