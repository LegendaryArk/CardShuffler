#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include <stdio.h>

#define IN1_PIN 0
#define IN2_PIN 1

#define PWM_FREQ 1000

#define PWM_MAX 65535

#define MOTOR_SPEED (uint16_t) (PWM_MAX * 0.70f)

uint pwm_init_pin(uint pin) {
	gpio_set_function(pin, GPIO_FUNC_PWM);
	uint slice = pwm_gpio_to_slice_num(pin);

	pwm_set_clkdiv(slice, 1.9f);
	pwm_set_wrap(slice, PWM_MAX);
	pwm_set_enabled(slice, true);

	return slice;
}

void motor_forward(uint speed) {
	pwm_set_gpio_level(IN1_PIN, speed);
	pwm_set_gpio_level(IN2_PIN, 0);
}

void motor_reverse(uint speed) {
	pwm_set_gpio_level(IN1_PIN, 0);
	pwm_set_gpio_level(IN2_PIN, speed);
}

void motor_stop() {
	pwm_set_gpio_level(IN1_PIN, 0);
	pwm_set_gpio_level(IN2_PIN, 0);
}

int main() {
	stdio_init_all();

	pwm_init_pin(IN1_PIN);
	pwm_init_pin(IN2_PIN);

	motor_stop();
	sleep_ms(500);

	while (true) {
		printf("Motor: FORWARD\n");
		motor_forward(MOTOR_SPEED);
		sleep_ms(2000);

		printf("Motor: STOP\n");
		motor_stop();
		sleep_ms(1000);

		printf("Motor: REVERSE\n");
		motor_reverse(MOTOR_SPEED);
		sleep_ms(2000);

		printf("Motor: STOP\n");
		motor_stop();
		sleep_ms(1000);
	}

	return 0;
}