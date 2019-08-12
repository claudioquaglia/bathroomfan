#include "PIRController.h"

#include <Particle.h>

#define PIR_PIN D4
#define LED_PIN D7
#define HUMAIN_DURATION ((unsigned long)(1000 * 60 * 5))

PIRController::PIRController() :
    _pir(false),
    _lastHumainDate(0) {
}

PIRController::~PIRController() {
}

void PIRController::begin() {
  _lastHumainDate = millis();  
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Particle.variable("pir", _pir);
  Particle.variable("lasthumain", _lastHumainDate);
}

void PIRController::loop() {
  _pir = digitalRead(PIR_PIN);
  if (_pir) {
    _lastHumainDate = millis();
    digitalWrite(D7, HIGH);
  } else {
    digitalWrite(D7, LOW);
  }
}

bool PIRController::isHumanPresent() const {
  return getLastHumainDuration() < HUMAIN_DURATION;
}

unsigned long PIRController::getLastHumainDuration() const {
  return millis() - _lastHumainDate;
};