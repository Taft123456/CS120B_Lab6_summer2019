#include <avr/io.h>
#include <avr/interrupt.h>
#include <timer.h>

enum States{BD, PAUSE, ONE, TWO, THREE} state, prev, next;
unsigned char button, pressed;

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
		case BD:
		if (pressed){}
		else {button = !button}
		break;
		case PAUSE:
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
		case BD:
		if (pressed){}
		else {state = next;}
		break;
		case PAUSE:
		if(button) state = ONE;
		break;
		case ONE:
		prev = ONE;
		if(button) state = PAUSE;
		else state = TWO;
		break;
		case TWO:
		if( prev == ONE ){
			state = THREE;
			next = THREE;
		}
		else {
			state = ONE;
			next = ONE;
		}
		prev = TWO;
		break;
		case THREE:
		if(button) state = PAUSE;
		else prev = THREE;
		state = TWO;
		break;
		default:
		break;
	}
}

int main(void)
{
	DDRA = 0x00;
	DDRB = 0xFF;
	DDRC = 0x00;
	DDRD = 0x00;
	
	PORTB = 0x00;
	
	TimerSet(300);
	TimerOn();
	
	button = 0;
	state = ONE;
	prev = ONE;
	
	while(1){
		Tick();
		while(!TimerFlag){pressed = PINA;};
		TimerFlag = 0;
	}
	return 0;
}