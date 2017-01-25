/*
 * main.c
 */
#include <tm4c123gh6pm.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/cpu.h"
#include "driverlib/gpio.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "driverlib/PLL.h"

#define SYSCTL_RCC_R            (*((volatile uint32_t *)0x400FE060))
#define SYSCTL_RCC2_R           (*((volatile uint32_t *)0x400FE070))
#define SYSCTL_RCC2             0x400FE070  // Run-Mode Clock Configuration 2
#define SYSCTL_RCC2_DIV400      0x40000000  // Divide PLL as 400 MHz vs. 200
                                            // MHz
#define SYSCTL_RCC2_USERCC2     0x80000000  // Use RCC2
#define SYSCTL_RCC2_BYPASS2     0x00000800  // PLL Bypass 2

int main(void)
{

    	SYSCTL_PLLFREQ0_R = 0x32;
    	SYSCTL_PLLFREQ1_R = 1;

    	//Configura o sistema para utilizar o RCC2 para configurar o PLL para 400MHz
    	SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
    	//Inicializa o bypass PLL
    	SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;

	//Configuração do oscilador interno.
	SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;   	 // limpa XTAL
	SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;	// configura para 16 MHz o cristal
	SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;  // limpa o oscilador
	SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO; // configura o oscilador principal
	SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;	//Configura o sistema para utilizar a PLL 400MHz
	SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000)+(SYSDIV2 <<22);   //Utiliza o divisor para setar o clock para 80MHz
	SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;	//Desabilita o bypass da PLL
	clock = SysCtlClockGet();
}
