#include <hardware/gpio.h>  // Native SDK header for GPIO functions
#include <hardware/pwm.h>   // Native SDK header for PWM functions
#include <pico/stdlib.h>    // Native SDK header for standard library functions
#include <Arduino.h>        // Arduino header for Arduino functions
#include "Motor.hpp"        // Include the Motor class header

// Test to be coducted
//#define fwd_bkwd_test
//#define speed_test
#define two_motor_test

// Motor to be tested
//#define motor1_test
//#define motor2_test

// Arduino header pin labels. The Nano RP2040 Connect maps these labels to
// RP2040 GPIOs through the board variant.
constexpr uint8_t in1Pin1 = D4;
constexpr uint8_t in2Pin1 = D5;

constexpr uint8_t in1Pin2 = D2;
constexpr uint8_t in2Pin2 = D3;

#if defined(motor1_test)
Motor motor(in1Pin1, in2Pin1); // Create a Motor object for the first motor
#elif defined(motor2_test)
Motor motor(in1Pin2, in2Pin2); // Create a Motor object for the second motor
#endif

#ifdef two_motor_test
Motor motor1(in1Pin1, in2Pin1); // Create a Motor object for the first motor
Motor motor2(in1Pin2, in2Pin2); // Create a Motor object for the second motor
#endif

void setup() {
    // Arduino-style initialization for the serial monitor
    Serial.begin(115200);

    // Native SDK-style initialization for the LED
    gpio_init(LED_BUILTIN);
    gpio_set_dir(LED_BUILTIN, GPIO_OUT);
}

void loop() {
    #ifdef fwd_bkwd_test
    Serial.println("Starting forward/backward test");|
    // Native SDK syntax to turn the LED on
    gpio_put(LED_BUILTIN, 1);
    motor.moveFwd(100.0f); // Move motor forward at full power
    Serial.println("Moving forward"); 
    sleep_ms(5000); // Native SDK delay

    motor.stop(); // Stop motor
    Serial.println("Motor stopped");
    sleep_ms(1000); // Native SDK delay

    gpio_put(LED_BUILTIN, 0);
    motor.moveBckwd(100.0f); // Move motor backward at full power
    Serial.println("Moving backward");
    sleep_ms(5000); // Native SDK delay

    motor.stop(); // Stop motor
    Serial.println("Motor stopped");
    sleep_ms(1000); // Native SDK delay
    #endif

    #ifdef speed_test
    Serial.println("Starting speed test");
    // Native SDK syntax to turn the LED on
    gpio_put(LED_BUILTIN, 1);
    Serial.println("Moving forward 100% power"); 
    motor.moveFwd(100.0f); // Move motor forward at full power
    sleep_ms(3000); // Native SDK delay
    Serial.println("Moving forward 80% power"); 
    motor.moveFwd(80.0f); // Move motor
    sleep_ms(3000); // Native SDK delay
    Serial.println("Moving forward 60% power");
    motor.moveFwd(60.0f); // Move motor
    sleep_ms(3000); // Native SDK delay
    Serial.println("Moving forward 40% power");
    motor.moveFwd(40.0f); // Move motor
    sleep_ms(3000); // Native SDK delay

    motor.stop(); // Stop motor
    Serial.println("Motor stopped");
    sleep_ms(1500); // Native SDK delay

    gpio_put(LED_BUILTIN, 0);
    Serial.println("Moving backward 100% power");
    motor.moveBckwd(100.0f); // Move motor backward at full power
    sleep_ms(3000); // Native SDK delay
    Serial.println("Moving backward 80% power");
    motor.moveBckwd(80.0f); // Move motor
    sleep_ms(3000); // Native SDK delay
    Serial.println("Moving backward 60% power");
    motor.moveBckwd(60.0f); // Move motor
    sleep_ms(3000); // Native SDK delay
    Serial.println("Moving backward 40% power");
    motor.moveBckwd(40.0f); // Move motor
    sleep_ms(3000); // Native SDK delay

    motor.stop(); // Stop motor
    Serial.println("Motor stopped");
    sleep_ms(1500); // Native SDK delay
    #endif

    #ifdef two_motor_test
    Serial.println("Starting 2 motor speed test");
    // Native SDK syntax to turn the LED on
    gpio_put(LED_BUILTIN, 1);
    Serial.println("Moving forward 100% power"); 
    motor1.moveFwd(100.0f); // Move motor forward at full power
    motor2.moveFwd(100.0f); // Move motor forward at full power
    sleep_ms(1500); // Native SDK delay
    Serial.println("Moving forward 80% power"); 
    motor1.moveFwd(80.0f); // Move motor
    motor2.moveFwd(80.0f); // Move motor
    sleep_ms(1500); // Native SDK delay
    Serial.println("Moving forward 60% power");
    motor1.moveFwd(60.0f); // Move motor
    motor2.moveFwd(60.0f); // Move motor
    sleep_ms(1500); // Native SDK delay
    Serial.println("Moving forward 40% power");
    motor1.moveFwd(40.0f); // Move motor
    motor2.moveFwd(40.0f); // Move motor
    sleep_ms(1500); // Native SDK delay

    motor1.stop(); // Stop motor
    motor2.stop(); // Stop motor
    Serial.println("Motor stopped");
    sleep_ms(1500); // Native SDK delay

    gpio_put(LED_BUILTIN, 0);
    Serial.println("Moving backward 100% power");
    motor1.moveBckwd(100.0f); // Move motor backward at full power
    motor2.moveBckwd(100.0f); // Move motor backward at full power
    sleep_ms(1500); // Native SDK delay
    Serial.println("Moving backward 80% power");
    motor1.moveBckwd(80.0f); // Move motor
    motor2.moveBckwd(80.0f); // Move motor
    sleep_ms(1500); // Native SDK delay
    Serial.println("Moving backward 60% power");
    motor1.moveBckwd(60.0f); // Move motor
    motor2.moveBckwd(60.0f); // Move motor
    sleep_ms(1500); // Native SDK delay
    Serial.println("Moving backward 40% power");
    motor1.moveBckwd(40.0f); // Move motor
    motor2.moveBckwd(40.0f); // Move motor
    sleep_ms(1500); // Native SDK delay

    motor1.stop(); // Stop motor
    motor2.stop(); // Stop motor
    Serial.println("Motor stopped");
    sleep_ms(1500); // Native SDK delay
    #endif
}
