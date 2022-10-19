

#include <stdint.h>
#include <stdio.h>

// 1) USART3 Nvıc IRQnumber daki pending biti pend olarak ayarlayip bekletecegiz
// -> Manually pend the pending bit for the USART3 IRQ number in NVIC
// 2) Enable the USART3 IRQ number in NVIC
// bunu ISER deki  interrupt set enable register ile yapacagiz

/* User manuelde ınterrupt pend sending regidsterda  8 register var
 * PR0 ila PR7 */

// USART3 icin IRQ numaramiz 39 (ırq39) oldugundan ISPR1 i kullanicagiz
// 39%32 = ISPR1 deki 7. bitle oynayacagiz

#define USART3_IRQNO 39
void USART3_IRQHandler(void);

int main(void)
{
	// -> Manually pend the pending bit for the USART3 IRQ number in NVIC
	uint32_t *pISPR1 = (uint32_t*) 0xE000E204; //NVIC_ISPR0 adresi
    *pISPR1 |= (1 << (USART3_IRQNO % 32));
    // 2) Enable the USART3 IRQ number in NVIC
    uint32_t *pISER1 = (uint32_t*) 0xE000E104;
    *pISER1 |= (1 << (USART3_IRQNO % 32));

	for(;;);
}

void USART3_IRQHandler(void){
	printf("in USART3 isr\n");
}
