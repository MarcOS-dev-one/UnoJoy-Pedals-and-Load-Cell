#define USB_GAMEPAD_PRIVATE_INCLUDE

#include "usb_gamepad.h"
#include <string.h>  // Para memset

uint8_t usb_init(void) {
	HW_CONFIG();
	USB_FREEZE();
	PLL_CONFIG();
	unsigned long timeoutCounter = 0;
	while (!(PLLCSR & (1<<PLOCK))){
		_delay_ms(1);
		timeoutCounter++;
		if (timeoutCounter >= USB_TIMEOUT)
		return 1;
	}
	USB_CONFIG();
	UDCON = 0;
	usb_configuration = 0;
	UDIEN = (1<<EORSTE)|(1<<SOFE);
	sei();
	return 0;
}

uint8_t usb_configured(void) {
	return usb_configuration;
}

gamepad_state_t gamepad_state;

inline void usb_gamepad_reset_state(void) {
	memcpy_P(&gamepad_state, &gamepad_idle_state, sizeof(gamepad_state_t));
}

int8_t sendPS3Data(dataForController_t btnList){
	gamepad_state.l_x_axis = btnList.leftStickX;
	gamepad_state.l_y_axis = btnList.leftStickY;
	gamepad_state.r_x_axis = btnList.rightStickX;
	gamepad_state.r_y_axis = 0x80; // centralizado (eixo Z ausente)
	return usb_gamepad_send();
}

int8_t usb_gamepad_send(void) {
	uint8_t intr_state, timeout, i;
	if (!usb_configuration) return -1;
	intr_state = SREG;
	cli();
	UENUM = GAMEPAD_ENDPOINT;
	timeout = UDFNUML + 50;
	while (1) {
		if (UEINTX & (1<<RWAL)) break;
		SREG = intr_state;
		if (!usb_configuration) return -1;
		if (UDFNUML == timeout) return -1;
		intr_state = SREG;
		cli();
		UENUM = GAMEPAD_ENDPOINT;
	}
	for (i=0; i<sizeof(gamepad_state_t); i++) {
		UEDATX = ((uint8_t*)&gamepad_state)[i];
	}
	UEINTX = 0x3A;
	SREG = intr_state;
	return 0;
}