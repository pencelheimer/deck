#include <AiEsp32RotaryEncoder.h>
#include <Arduino.h>

#include "encoder.cpp"

Encoder enc1 = Encoder(21, 22, 23, 0, 100, "1");
Encoder enc2 = Encoder(5, 18, 19, 0, 100, "2");

Encoder *encs[2] = {&enc1, &enc2};

void setup() {
  Serial.begin(115200);

  enc1.begin([]() IRAM_ATTR { enc1.readEncoder_ISR(); });
  enc2.begin([]() IRAM_ATTR { enc2.readEncoder_ISR(); });
}

void loop() {
  for (Encoder *enc : encs) {
    if (enc->encoderChanged()) {
      Serial.printf("%s:%ld\n", enc->name, enc->readEncoder());
    }

    if (enc->isEncoderButtonClicked()) {
      Serial.printf("%s:b\n", enc->name);
    }
  }

  delay(50);
}
