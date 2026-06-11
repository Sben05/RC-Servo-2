#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define SERVO_PIN 15
#define WRAP 59999

// 50Hz: period = 20ms, wrap = 59999, each count = 20ms/60000 = 0.333us
// 0.5ms = 1500 counts, 2.5ms = 7500 counts
void set_angle(float angle) {
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN);
    float pulse_ms = 0.5f + (angle / 180.0f) * 2.0f;
    float counts_per_ms = (float)(WRAP + 1) / 20.0f;
    uint16_t level = (uint16_t)(pulse_ms * counts_per_ms);
    pwm_set_gpio_level(SERVO_PIN, level);
}

int main() {
    stdio_init_all();

    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN);

    // Set clock divider so wrap of 59999 gives 50Hz
    float clk_hz = (float)clock_get_hz(clk_sys);
    float divider = clk_hz / (50.0f * (WRAP + 1));
    pwm_set_clkdiv(slice, divider);
    pwm_set_wrap(slice, WRAP);
    pwm_set_enabled(slice, true);

    while (true) {
        for (int angle = 0; angle <= 180; angle++) {
            set_angle((float)angle);
            sleep_ms(10);
        }
        for (int angle = 180; angle >= 0; angle--) {
            set_angle((float)angle);
            sleep_ms(10);
        }
    }
}
