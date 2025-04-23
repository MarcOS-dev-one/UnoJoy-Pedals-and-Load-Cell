#ifndef UNOJOY_H
#define UNOJOY_H

#include <stdint.h>
#include <util/atomic.h>
#include <Arduino.h>

typedef struct {
	uint8_t Rx;
	uint8_t Ry;
	uint8_t Rz;
} dataForController_t;

volatile dataForController_t controllerDataBuffer;

void setControllerData(dataForController_t controllerData) {
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        controllerDataBuffer = controllerData;
    }
}

volatile int serialCheckInterval = 1;
int serialCheckCounter = 0;

void setupUnoJoy(void) {
    controllerDataBuffer.Rx = 128;
    controllerDataBuffer.Ry = 128;
    controllerDataBuffer.Rz = 128;

    Serial.begin(38400);
    OCR0A = 128;
    TIMSK0 |= (1 << OCIE0A);
}

void setupUnoJoy(int interval) {
    serialCheckInterval = interval;
    setupUnoJoy();
}

ISR(TIMER0_COMPA_vect) {
    serialCheckCounter++;
    if (serialCheckCounter >= serialCheckInterval) {
        serialCheckCounter = 0;
        while (Serial.available() > 0) {
            byte inByte = Serial.read();
            Serial.write(((uint8_t*)&controllerDataBuffer)[inByte]);
        }
    }
}

dataForController_t getBlankDataForController(void) {
    dataForController_t controllerData;
    controllerData.Rx = 128;
    controllerData.Ry = 128;
    controllerData.Rz = 128;
    return controllerData;
}

#endif
