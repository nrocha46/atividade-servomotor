#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include <stdint.h>
#include <stdbool.h>

#define SERVO_PIN 22
#define LED_PIN 12
#define PWM_FREQ 50.0 // 50Hz para servomotor
#define LED_PWM_FREQ 1000.0 // 1kHz para LED
#define DELAY_MS 10   // Atraso para suavizar o movimento
#define STEP_US 5      // Incremento do ciclo ativo
#define PWM_DIVISER 64.0f // Divisor de clock para estabilidade

// Função para configurar o PWM
void config_pwm(uint32_t slice, uint32_t channel, float duty_us, uint32_t wrap) {
    pwm_set_wrap(slice, wrap);
    pwm_set_chan_level(slice, channel, (uint32_t)((duty_us * wrap) / 20000));
    pwm_set_enabled(slice, true);
}

int main() {
    stdio_init_all();
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    
    uint32_t servo_slice = pwm_gpio_to_slice_num(SERVO_PIN);
    uint32_t servo_channel = pwm_gpio_to_channel(SERVO_PIN);
    uint32_t led_slice = pwm_gpio_to_slice_num(LED_PIN);
    uint32_t led_channel = pwm_gpio_to_channel(LED_PIN);
    uint32_t clock_freq = clock_get_hz(clk_sys);
    uint32_t servo_wrap = (clock_freq / (PWM_DIVISER * PWM_FREQ)) - 1;
    uint32_t led_wrap = (clock_freq / (PWM_DIVISER * LED_PWM_FREQ)) - 1;
    
    // Configuração inicial do PWM
    pwm_set_clkdiv(servo_slice, PWM_DIVISER);
    pwm_set_wrap(servo_slice, servo_wrap);
    pwm_set_enabled(servo_slice, true);
    
    pwm_set_clkdiv(led_slice, PWM_DIVISER);
    pwm_set_wrap(led_slice, led_wrap);
    pwm_set_enabled(led_slice, true);
    
    // Posicionar o servo em 180 graus e LED no máximo
    config_pwm(servo_slice, servo_channel, 2400, servo_wrap);
    pwm_set_gpio_level(LED_PIN, led_wrap);
    sleep_ms(5000);
    
    // Posicionar o servo em 90 graus e LED no médio
    config_pwm(servo_slice, servo_channel, 1470, servo_wrap);
    pwm_set_gpio_level(LED_PIN, led_wrap / 2);
    sleep_ms(5000);
    
    // Posicionar o servo em 0 graus e LED no mínimo
    config_pwm(servo_slice, servo_channel, 500, servo_wrap);
    pwm_set_gpio_level(LED_PIN, 0);
    sleep_ms(5000);
    
    // Movimentação periódica suave entre 0 e 180 graus continuamente
    bool aumentando = true;
    uint32_t duty = 500;
    uint32_t led_duty = 0;
    
    while (true) {
        pwm_set_chan_level(servo_slice, servo_channel, (uint32_t)((duty * servo_wrap) / 20000));
        pwm_set_gpio_level(LED_PIN, led_duty);
        sleep_ms(DELAY_MS);
        
        if (aumentando) {
            duty += STEP_US;
            led_duty += (led_wrap / (2400 - 500)) * STEP_US; // Ajuste do LED proporcional ao servo
            if (duty >= 2400) aumentando = false;
        } else {
            duty -= STEP_US;
            led_duty -= (led_wrap / (2400 - 500)) * STEP_US;
            if (duty <= 500) aumentando = true;
        }
    }
}
