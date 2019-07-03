/*
 * Lab6-Timer_synchSMs.c
 *
 * Created: 7/2/2019 5:33:48 PM
 * Author : Taft
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <timer.h>

enum States{START, ONE, TWO, THREE} state;

volatile unsigned char TimerFlag = 0; 

unsigned long _avr_timer_M = 1; 
unsigned long _avr_timer_cntcurr = 0; 

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void TimerOn() {
	TCCR1B = 0x0B;	
	OCR1A = 125;	
	TIMSK1 = 0x02; 
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;	
}

void TimerOff() {
	TCCR1B 	= 0x00; 
}

void TimerISR() {
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect)
{	
	_avr_timer_cntcurr--; 			
	if (_avr_timer_cntcurr == 0) { 	
		TimerISR(); 				
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void Tick(){
	
	switch(state){
		case START:
			PORTB = 0x00;
		break;
		case ONE:
			PORTB = 0x01;
		break;
		case TWO:
			PORTB = 0x02;
		break;
		case THREE:
			PORTB = 0x04;
		break;
		default:
		break;
	}
	
	switch(state){
		case START:
		state = ONE;
		break;
		case ONE:
		state = TWO;
		break;
		case TWO:
		state = THREE;
		break;
		case THREE:
		state = START;
		break;
		default:break;
	}
}
int main(void)
{
	DDRB = 0xFF;
	PORTB = 0x00;
	
	TimerSet(1000);
	TimerOn();
	
	state = START;
	
	while(1){
		Tick();
		while(!TimerFlag){};
		TimerFlag = 0;
	}
	return 0;
}

