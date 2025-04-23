#define USB_GAMEPAD_PRIVATE_INCLUDE
#include "usb_gamepad.h"

static volatile uint8_t usb_configuration = 0;

static const gamepad_state_t PROGMEM gamepad_idle_state = {
	.triangle_btn = 0, .square_btn = 0, .cross_btn = 0, .circle_btn = 0,
	.l1_btn = 0, .r1_btn = 0, .l2_btn = 0, .r2_btn = 0,
	.select_btn = 0, .start_btn = 0, .l3_btn = 0, .r3_btn = 0, .ps_btn = 0,
	.direction = 0x08,
	.l_x_axis = 0x80, .l_y_axis = 0x80, .r_x_axis = 0x80, .r_y_axis = 0x80,
	.up_axis = 0x00, .right_axis = 0x00, .down_axis = 0x00, .left_axis = 0x00,
	.circle_axis = 0x00, .cross_axis = 0x00, .square_axis = 0x00, .triangle_axis = 0x00,
	.l1_axis = 0x00, .r1_axis = 0x00, .l2_axis = 0x00, .r2_axis = 0x00
};

gamepad_state_t gamepad_state;

inline void usb_gamepad_reset_state(void) {
	memcpy_P(&gamepad_state, &gamepad_idle_state, sizeof(gamepad_state_t));
}
