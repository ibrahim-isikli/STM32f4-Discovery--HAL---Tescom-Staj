#include <stdint.h>
#include <stdio.h>

void waitForUserInput(void);
int adding( int a, int b, int c, int d);

int fun_add(int a, int b, int c, int d) //calle
{ 													// R0 R1 R2 R3 degerler variabllara kopyalanir

	int adding = a+b+c+d;
	return adding;									// return icin R0 kullanilir(eger result 64 bit ise 2 reg kullailir R0 ve R1)
}


int main(void) // caller
{
   int result;

   result = fun_add(1, 4, 5, 6);  // 2, 3, 4, 5, 8 -> bu degerler internal registarlara koyalanir
	 	 	 	 	 	 	 	 // R0 R1 R2 R3
   	   	   	   	   	   	   	   	   // eger daha fazla deger olursa 2 stack memory  devreye girer R4 ve R2 kesinlikle bu islev icin kullanilmaz

   waitForUserInput();
}


void waitForUserInput(void)
{
	printf("Please press the enter button for exit\n");
	while(getchar()!='\n'){

	}
	getchar();
}



/*******************NOTLAR************************/

/*dissambly ekranini incele
 *           fun_add:
080001e9:   push    {r7}
080001eb:   sub     sp, #28
080001ed:   add     r7, sp, #0
080001ef:   str     r0, [r7, #12]   =>   }
080001f1:   str     r1, [r7, #8]    =>	 } goruldugu uzere variable de str kaydetme islemleri fun_add kisminda
080001f3:   str     r2, [r7, #4]	=>   } r0 r1 r2 r3 registerlari tarafindan gerceklesmis
080001f5:   str     r3, [r7, #0]	=>   }
...adding
08000209:   mov     r0, r3     => r0 return
 */
