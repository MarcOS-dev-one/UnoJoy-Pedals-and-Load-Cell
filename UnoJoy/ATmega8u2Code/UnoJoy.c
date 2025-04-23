#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include "dataForController_t.h"
#include "usb_gamepad.h"

#define RXLED 4
#define TXLED 5

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))

void USART_Init(uint16_t baudSetting) {
	UBRR1 = baudSetting;
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);
	UCSR1C = (1 << UCSZ10) | (1 << UCSZ11);
}

unsigned char serialRead(uint16_t timeout) {
	while (!(UCSR1A & (1 << RXC1))) {
		_delay_ms(1);
		if (--timeout == 0)
		return 0;
	}
	return UDR1;
}

void serialWrite(unsigned char data) {
	while (!(UCSR1A & (1 << UDRE1)));
	UDR1 = data;
}

void flushSerialRead() {
	unsigned char dummy;
	while (UCSR1A & (1 << RXC1))
	dummy = UDR1;
}

void LEDon(char ledNumber) {
	DDRD |= 1 << ledNumber;
	PORTD &= ~(1 << ledNumber);
}

void LEDoff(char ledNumber) {
	DDRD &= ~(1 << ledNumber);
	PORTD |= 1 << ledNumber;
}

int main(void) {
	wdt_reset();
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	USART_Init(25);
	CPU_PRESCALE(0);

	usb_init();
	while (!usb_configured()) {
		LEDon(TXLED);
		_delay_ms(50);
		LEDoff(TXLED);
		_delay_ms(50);
	}

	_delay_ms(500);
	dataForController_t dataToSend;

	while (1) {
		_delay_ms(10);
		flushSerialRead();

		serialWrite(0);
		dataToSend.leftStickX = serialRead(25);

		serialWrite(1);
		dataToSend.leftStickY = serialRead(25);

		serialWrite(2);
		dataToSend.rightStickX = serialRead(25);

		sendPS3Data(dataToSend);
	}
}