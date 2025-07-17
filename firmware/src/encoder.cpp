#include <AiEsp32RotaryEncoder.h>
#include <Arduino.h>

class Encoder : public AiEsp32RotaryEncoder {
public:
  char const *name;
  long lb;
  long ub;

  Encoder(uint8_t clk, uint8_t dt, uint8_t sw, long lb, long ub,
          char const *name)
      : AiEsp32RotaryEncoder(clk, dt, sw, -1, 2), name(name), lb(lb), ub(ub) {}

  void begin(void (*ISR_callback)()) {
    AiEsp32RotaryEncoder::begin();

    this->setup(ISR_callback);

    this->setAcceleration(0);

    this->setBoundaries(lb, ub, false);
  }
};
