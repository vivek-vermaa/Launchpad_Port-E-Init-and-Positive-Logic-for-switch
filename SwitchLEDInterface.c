
// SwitchLEDInterface.c for Lab 8
// Runs on LM4F120/TM4C123
// Author - Vivek Verma 
// Date - 8th April 2020 
// Launchpad Port-E initialization 


// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"

// ***** 2. Global Declarations Section *****

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Port_E_Init(void);
void Delay1ms(unsigned long time);
// ***** 3. Subroutines Section *****

// PE0, PB0, or PA2 connected to positive logic momentary switch using 10k ohm pull down resistor
// PE1, PB1, or PA3 connected to positive logic LED through 470 ohm current limiting resistor
// To avoid damaging your hardware, ensure that your circuits match the schematic
// shown in Lab8_artist.sch (PCB Artist schematic file) or 
// Lab8_artist.pdf (compatible with many various readers like Adobe Acrobat).
int main(void)
{ 
//**********************************************************************
// The following version tests input on PE0 and output on PE1
//**********************************************************************
	unsigned int SW1;
  TExaS_Init(SW_PIN_PE0, LED_PIN_PE1, ScopeOn);  //  set system clock to 80 MHz                            
  EnableInterrupts();  
	Port_E_Init();
  while(1)
	{
		SW1 = GPIO_PORTE_DATA_R &0x01;
		if (SW1 != 0)  /*Positive Logic for Switch pressed*/
		{
			GPIO_PORTE_DATA_R ^= 0x02;
			Delay1ms(100);
		}
		else
		{
			GPIO_PORTE_DATA_R |= 0x02;
		}
    
  }
  
}

void Port_E_Init(void)
{
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x10;      			// 1) Enabling Port E clock
  delay = SYSCTL_RCGC2_R;            // delay to allow clock to stabilize     
  GPIO_PORTE_AMSEL_R &= ~0x10;        // 2) disable analog function
  GPIO_PORTE_PCTL_R &= 0x00000000;   // 3) GPIO clear bit PCTL  
  GPIO_PORTE_DIR_R &= ~0x01;         // 4.1) PE0 input,
  GPIO_PORTE_DIR_R |= 0x02;          // 4.2) PE1 output  
  GPIO_PORTE_AFSEL_R &= 0x00;        // 5) no alternate function
  GPIO_PORTE_PUR_R &= ~0x01;          // 6) enable pull down resistor on PE0       
  GPIO_PORTE_DEN_R |= 0x03;          // 7) enable digital pins PE1,PE0
}

void Delay1ms(unsigned long time)
{
  unsigned long i;
  while(time > 0){
    i = 13333;  // this number means 1ms
    while(i > 0){
      i = i - 1;
    }
    time = time - 1; // decrements every 1 ms
  }
}