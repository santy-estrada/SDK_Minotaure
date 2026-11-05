#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <hardware/gpio.h>
#include <hardware/pwm.h>
#include <pico/stdlib.h>
#include <Arduino.h>

class Motor {
public:
    static constexpr uint NO_ENA_PIN = 255;

    // 3-Pin Driver Constructor (ENA, IN1, IN2)
    Motor(uint ena_pin, uint in1_pin, uint in2_pin);

    // 2-Pin Driver Constructor (IN1 PWM, IN2 PWM)
    Motor(uint in1_pin, uint in2_pin);

    virtual ~Motor() = default;

    virtual void moveFwd(float power);
    virtual void moveBckwd(float power);
    virtual void stop();

    float getPwmPower() const;
    void setPwmPower(float power);
    void applyPwmPower();

protected:
    enum class Direction { STOPPED, FORWARD, BACKWARD };

    uint ENA_PIN;
    uint IN1_PIN;
    uint IN2_PIN;
    float PWM_POWER;
    bool is_two_pin;
    Direction current_direction;

    uint pwmSlice; // Used for ENA in 3-pin mode
};

#endif // MOTOR_H