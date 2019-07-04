#include <avr/io.h>
#include <avr/interrupt.h>
#include <timer.h>

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

enum States{START, ONE, TWO, THREE, PAUSE} state;
unsigned char tmpB;

void Tick(){
	switch(state){
		case START:
			tmpB = 0x00;
			break;
		case PAUSE:
			break;
		case ONE:
			tmpB = 0x01;
			break;
		case TWO:
			tmpB = 0x02;
			break;
		case THREE:
			tmpB = 0x04;
			break;
		default:
			break;
	}
	switch(state){
		case START:
			state = ONE;
			break;
		case PAUSE:
			if((~PINA & 0x01) == 0x01)
			{
				state = ONE;
			}
			else{
				state = PAUSE;
			}
			break;
		case ONE:
			if((~PINA & 0x01) == 0x01)
			{
				state = PAUSE;
			}
			else{
				state = TWO;
			}
			break;
		case TWO:
			if((~PINA & 0x01) == 0x01)
			{
				state = PAUSE;
			}
			else{
				state = THREE;
			}
			break;
		case THREE:
			if((~PINA & 0x01) == 0x01)
			{
				state = PAUSE;
			}
			else{
				state = START;
			}
			break;
		default:
			break;
	}
	PORTB = tmpB;
}

int main(void)
{	
	DDRA = 0x00;
	DDRB = 0xFF;
	PORTB = 0x00;
	
	TimerSet(38);
	TimerOn();
	
	state = START;
	
	while(1){
		Tick();
		while(!TimerFlag){};
		TimerFlag = 0;
	}
	return 0;
}