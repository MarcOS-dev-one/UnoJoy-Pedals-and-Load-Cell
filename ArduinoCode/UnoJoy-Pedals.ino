#include <HX711.h>
#include "UnoJoy.h"

#define HX711_DOUT  3  // DT da célula de carga
#define HX711_SCK   2  // SCK da célula de carga

HX711 scale;

#define CALIBRATION_FACTOR -640.0
#define MAX_BRAKE_FORCE    2000.0  // Força total no pedal
#define SMOOTHING_FACTOR   0.2    // Suavização da leitura

float smoothedBrake = 0;

void setup() {
  setupUnoJoy();

  scale.begin(HX711_DOUT, HX711_SCK);
  scale.set_scale(CALIBRATION_FACTOR);
  scale.tare();

  analogReference(DEFAULT); // Usa referência padrão de 5V
}

void loop() {
  dataForController_t controllerData = getBlankDataForController();

  // ---------- FREIO ----------
  float rawBrake = scale.get_units();
  if (rawBrake < 0) rawBrake = 0;
  if (rawBrake > MAX_BRAKE_FORCE) rawBrake = MAX_BRAKE_FORCE;

  smoothedBrake = smoothedBrake + SMOOTHING_FACTOR * (rawBrake - smoothedBrake);
  controllerData.Rz = map(smoothedBrake, 0, MAX_BRAKE_FORCE, 0, 255);

  // ---------- ACELERADOR ----------
  int accelRaw = analogRead(A0);
  controllerData.Rx = accelRaw >> 2;  // 10 bits → 8 bits

  // ---------- EMBREAGEM ----------
  int clutchRaw = analogRead(A1);
  controllerData.Ry = clutchRaw >> 2;

  setControllerData(controllerData);
  delay(5);
}
