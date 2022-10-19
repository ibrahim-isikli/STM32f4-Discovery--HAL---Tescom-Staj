/**********************NOTLAR*****************************/
/*
 * Exception nedir ?
 * Programın çalışma zamanında senkron veya asenkron olarak araya girerek
 * işlemcinin modunu değiştiren olaya exception denir.
 *
 * ARM'da 2 tip exceptions vardir
 * 1) system exception
 * 2) interrupts
 *
 * system exceptions; islemcinin kendisi tarafindan olusturulr
 * interrupts; come from external world to the processor
 *
 *  => processor bir exception ile karsilasirsa THREAD MODE'dan HANDLER MODE'a gecer
 *
 *  CORTEX M processor 15 adet system exceptionu - 240 interruptu destekler
 *  yani totalde 255 exceptions var
 */


/* SYSTEM EXCEPTIONS
 * 15 adet var. birincisi -> Reset exception (system exception)
 * 9 adeti kullanimdi, 6 s, reserved
 * 16. exception -> interrupt 1  ( IRQ 1 )
 *
 * RESET,NMIİHardFault,MemManage,BusFAult,UsageFault,SVCall,PendSV,SysTickiInterrupt(IRQ)
 *
 * Reset
 *  enerjilendirme veya warm reset ile tetiklenir.
 *  Reset exception’u gerçekleştiği zaman işlemci o an hangi komutu işletiyorsa çalışmasını durdurur.
 *  Daha sonra vektör tablosunda Reset Handler kaydına bakarak
 *  o adresten priviliged seviyede ve Thread modunda çalışmaya başlar.
 *
 *  NMI
 *   bir çevrebiriminden veya yazılımdan tetiklenebilmektedir.
 *   Reset’den sonra en yüksek öncelikli exception’dur.
 *   NMI adından da anlaşıldığı üzere maskelenemez ve Reset dışında başka bir exception tarafından kesilemez.
 *
 *
 *   SVC
 *   SVC komutu ile tetiklenmektedir.
 *   İşletim sistemlerinde kullanıcı uygulamalarından çekirdek (kernel) fonksiyonlarına
 *   ve cihaz sürücülerine erişmek amacıyla çekirdek seviyesine çağrıda bulunmak için kullanılmaktadır.
 *
 *
 *   PendSV (Pendable Service)
*	 İşletim sistemlerinde eğer herhangi bir exception aktif durumda değil ise
*	 Context Switching işlemi için kullanılmaktadır.
*
*	 SysTick
*	Sistem zamanlayıcısı tarafından 0'a ulaştığında üretilen exception’dur.
*	Yazılım tarafından da bu exception’u üretmemiz mümkündür.
*	İşletim sistemlerinde işlemci bu exception’u sistem tick’i olarak kullanabilir.
*
*
 */

#include <stdint.h>


int main(void)
{
    /* Loop forever */
	for(;;);
}
