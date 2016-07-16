/************************************************************* 
 This sketch makes the pin PB1 (digital pin 1) toggle every
 second (internal oscillator running at 9.6 MHz). It uses Timer0
 or Timer0B, and divide the clock frequncy by 1024.
 The divided frequencys period is multiplied with the
 number og counts Timer0/Timer0B can take before it overflows.
 The number is then multiplied by 61, and gives approximately
 1 second.  

 9.6MHz / 1024 = 9370 Hz        We divide the 9.6 MHz clock by 1024
 1/9370 = 0.0001067s            Period time
 256 * 0.0001067 = 0.027315    
 0.027315 * 37 = 1.01065 ≈ 1s   
 X = 1.01065 / 0.027315 where X is approximately 61
**************************************************************/ 


#include <avr/io.h>

unsigned int timeCount;


int main (void)
{
  DDRB |= 0x01; //Set PB1 as output, ignore the rest

  TCCR0B = 0x05; // clock frequency / 1024 
  OCR0B = 0x00;  // Output compare
  TCNT0 = 0; // Set counter 0 to zero
	TIMSK0 = 0x01; // Enable overflow interrupt
  
  sei(); //Enable global interrupts
  
  while(1); // Infinite loop    
}



ISR(TIM0_OVF_vect) //Timer 0 overflow vector - this run every time timer0 overflows
{
  timeCount++;
  if(timeCount == 37) //Timer overflown for the 61th time
  {
    PORTB ^= 0x01; //toggle PB5
    timeCount = 0;
  }
}
