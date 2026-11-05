#include "Motor.hpp"

// 3-Pin Constructor (Enable pin + 2 direction pins)
Motor::Motor(uint ena_pin, uint in1_pin, uint in2_pin)
    : ENA_PIN(ena_pin), IN1_PIN(in1_pin), IN2_PIN(in2_pin),
      PWM_POWER(0.0f), is_two_pin(false), current_direction(Direction::STOPPED) {
    
    // Direction pins configured as standard GPIO outputs
    gpio_init(IN1_PIN);
    gpio_init(IN2_PIN);
    gpio_set_dir(IN1_PIN, GPIO_OUT);
    gpio_set_dir(IN2_PIN, GPIO_OUT);
    
    // Speed pin configured for PWM
    gpio_set_function(ENA_PIN, GPIO_FUNC_PWM);
    pwmSlice = pwm_gpio_to_slice_num(ENA_PIN);
    pwm_set_wrap(pwmSlice, 12499); // 10kHz frequency
    pwm_set_gpio_level(ENA_PIN, 0);
    pwm_set_enabled(pwmSlice, true);
    
    stop();
}

// 2-Pin Constructor (Both pins are PWM driven)
Motor::Motor(uint in1_pin, uint in2_pin)
    : ENA_PIN(NO_ENA_PIN), IN1_PIN(in1_pin), IN2_PIN(in2_pin),
      PWM_POWER(0.0f), is_two_pin(true), current_direction(Direction::STOPPED) {
    
    // Configure IN1_PIN for PWM
    gpio_set_function(IN1_PIN, GPIO_FUNC_PWM);
    uint slice1 = pwm_gpio_to_slice_num(IN1_PIN);
    pwm_set_wrap(slice1, 12499);
    pwm_set_gpio_level(IN1_PIN, 0);
    pwm_set_enabled(slice1, true);

    // Configure IN2_PIN for PWM
    gpio_set_function(IN2_PIN, GPIO_FUNC_PWM);
    uint slice2 = pwm_gpio_to_slice_num(IN2_PIN);
    pwm_set_wrap(slice2, 12499);
    pwm_set_gpio_level(IN2_PIN, 0);
    pwm_set_enabled(slice2, true);

    stop();
}

void Motor::moveFwd(float power) {
    setPwmPower(power);
    current_direction = Direction::FORWARD;

    if (is_two_pin) {
        uint16_t pwm_level = (uint16_t)(PWM_POWER * 12499.0f / 100.0f);
        pwm_set_gpio_level(IN1_PIN, pwm_level);
        pwm_set_gpio_level(IN2_PIN, 0);
    } else {
        gpio_put(IN1_PIN, 1);
        gpio_put(IN2_PIN, 0);
        applyPwmPower();
    }
}

void Motor::moveBckwd(float power) {
    setPwmPower(power);
    current_direction = Direction::BACKWARD;

    if (is_two_pin) {
        uint16_t pwm_level = (uint16_t)(PWM_POWER * 12499.0f / 100.0f);
        pwm_set_gpio_level(IN1_PIN, 0);
        pwm_set_gpio_level(IN2_PIN, pwm_level);
    } else {
        gpio_put(IN1_PIN, 0);
        gpio_put(IN2_PIN, 1);
        applyPwmPower();
    }
}

void Motor::stop() {
    setPwmPower(0.0f);
    current_direction = Direction::STOPPED;

    if (is_two_pin) {
        pwm_set_gpio_level(IN1_PIN, 0);
        pwm_set_gpio_level(IN2_PIN, 0);
    } else {
        gpio_put(IN1_PIN, 0);
        gpio_put(IN2_PIN, 0);
        applyPwmPower();
    }
}

float Motor::getPwmPower() const {
    return PWM_POWER;
}

void Motor::setPwmPower(float power) {
    if (power < 0.0f) power = 0.0f;
    if (power > 100.0f) power = 100.0f;
    PWM_POWER = power;
}

void Motor::applyPwmPower() {
    uint16_t pwm_level = (uint16_t)(PWM_POWER * 12499.0f / 100.0f);

    if (is_two_pin) {
        if (current_direction == Direction::FORWARD) {
            pwm_set_gpio_level(IN1_PIN, pwm_level);
            pwm_set_gpio_level(IN2_PIN, 0);
        } else if (current_direction == Direction::BACKWARD) {
            pwm_set_gpio_level(IN1_PIN, 0);
            pwm_set_gpio_level(IN2_PIN, pwm_level);
        } else {
            pwm_set_gpio_level(IN1_PIN, 0);
            pwm_set_gpio_level(IN2_PIN, 0);
        }
    } else {
        pwm_set_gpio_level(ENA_PIN, pwm_level);
    }
}