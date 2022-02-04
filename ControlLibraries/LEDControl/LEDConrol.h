/**
 * LEDControl.h
 * A library to work with LED's to be able to blink them automatically.
 * 
 * ------ Constructor ------
 * LEDControl led(uint8_t pin, float freq);
 * 
 * pin  -> The pin that the LED is plugged in to
 * freq -> The frequency that the LED will blink at (1 full on/off cycle)
 * 
 * ------ Usage ------ 
 * led.begin();
 *      - This will initialize the Teensy hardware for the LED
 * 
 * led.update();
 *      - This needs to be called at a frequency >> freq and will update
 *        the LED when the period has elapsed.
 */

#ifndef LEDCONTROL_H
#define LEDCONTROL_H

class LEDControl {
private:
    bool _state;
    uint8_t _pin;
    float _freq;
    uint32_t _period;
    uint32_t _last_updated;

public:

    LEDControl(uint8_t pin, float freq);

    void begin();
    void update();
};

#endif
